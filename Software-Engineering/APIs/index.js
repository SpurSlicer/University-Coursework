// *****************************************************
// <!-- Section 1 : Import Dependencies -->
// *****************************************************

const express = require('express'); // To build an application server or API
const app = express();
const handlebars = require('express-handlebars');
const Handlebars = require('handlebars');
const path = require('path');
const pgp = require('pg-promise')(); // To connect to the Postgres DB from the node server
const bodyParser = require('body-parser');
const session = require('express-session'); // To set the session object. To store or access session data, use the `req.session`, which is (generally) serialized as JSON by the store.
const bcrypt = require('bcrypt'); //  To hash passwords
const axios = require('axios'); // To make HTTP requests from our server. We'll learn more about it in Part C.

// *****************************************************
// <!-- Section 2 : Connect to DB -->
// *****************************************************

// create `ExpressHandlebars` instance and configure the layouts and partials dir.
const hbs = handlebars.create({
  extname: 'hbs',
  layoutsDir: __dirname + '/views/layouts',
  partialsDir: __dirname + '/views/partials',
});

// database configuration
const dbConfig = {
  host: 'db', // the database server
  port: 5432, // the database port
  database: process.env.POSTGRES_DB, // the database name
  user: process.env.POSTGRES_USER, // the user account to connect with
  password: process.env.POSTGRES_PASSWORD, // the password of the user account
};

const db = pgp(dbConfig);

// test your database
db.connect()
  .then(obj => {
    console.log('Database connection successful'); // you can view this message in the docker compose logs
    obj.done(); // success, release the connection;
  })
  .catch(error => {
    console.log('ERROR:', error.message || error);
  });

// *****************************************************
// <!-- Section 3 : App Settings -->
// *****************************************************

// Register `hbs` as our view engine using its bound `engine()` function.
app.engine('hbs', hbs.engine);
app.set('view engine', 'hbs');
app.set('views', path.join(__dirname, 'views'));
app.use(bodyParser.json()); // specify the usage of JSON for parsing request body.

// initialize session variables
app.use(
  session({
    secret: process.env.SESSION_SECRET,
    saveUninitialized: false,
    resave: false,
  })
);

app.use(
  bodyParser.urlencoded({
    extended: true,
  })
);

// *****************************************************
// <!-- Section 4 : API Routes -->
// *****************************************************

app.get('/', (req, res) => {
    res.redirect('/login'); 
});

app.get('/register', (req, res) => {
    res.render('./pages/register.hbs'); 
});

app.post('/register', async (req, res) => {
    const hash = await bcrypt.hash(req.body.password, 10);
    const query = `INSERT INTO users (username, password) VALUES ($1, $2);`;
    db.any(query, [req.body.username, hash])
    .then(data => {
      res.redirect('/login');
      return console.log(`Added ${req.body.username} and hash ${hash} to db`);
    })
    .catch(function (err) {
      res.render('./pages/register.hbs', {
        message: `This username is taken! please enter in something different.`
      });
      return console.log(err);
    });
});

app.get('/login', (req, res) => {
    res.render('./pages/login.hbs');
});

app.post('/login', async (req, res) => {
    const query = `SELECT password FROM users WHERE $1 = username;`;
    db.tx(async user => {
      const {password} = await user.one(query, [req.body.username]);
      console.log(`Password entered is ${password}`);
      const match = await bcrypt.compare(req.body.password, password);
      console.log(`match is ${match}`);
      if (!match) {
        throw new Error('test error');
      } else {
        console.log(`saving credentials`);
        req.session.user = req.body.username;
        req.session.save();
      }
      return;
    })
    .then(user => {
      res.redirect('/discover');
      return console.log(`Successfully logged in!`);
    })
    .catch(function (err) {
      res.render('./pages/login.hbs', {
        message: `Incorrect login information entered! Please try again.`
      });
      console.log(`User ${req.body.username} entered incorrect password.`);
      return;
    });

    return;
});

// Authentication Middleware.
const auth = (req, res, next) => {
    if (!req.session.user) {
      // Default to login page.
      return res.redirect('/login');
    }
    next();
  };

app.get('/discover', (req, res) => {
  axios({
    url: `https://app.ticketmaster.com/discovery/v2/events.json`,
    method: 'GET',
    dataType: 'json',
    headers: {
      'Accept-Encoding': 'application/json',
    },
    params: {
      apikey: process.env.API_KEY,
      keyword: 'Chris', //you can choose any artist/event here
      size: 10 // you can choose the number of events you would like to return
    },
  })
    .then(results => {
      res.render('./pages/discover.hbs', {
        events: results.data._embedded.events
      });
      console.log((results.data._embedded.events.length)); // the results will be displayed on the terminal if the docker containers are running // Send some parameters
    })
    .catch(err => {
      res.render('./pages/discover.hbs', {
        events: [],
        message: `no results found`
      });
      console.log(err);
      // Handle errors
  });
  
});

app.get('/logout', (req, res) => {
  req.session.destroy();
  res.render('./pages/logout');
})
  // Authentication Required
  app.use(auth);

// *****************************************************
// <!-- Section 5 : Start Server-->
// *****************************************************
// starting the server and keeping the connection open to listen for more requests
app.listen(3000);
console.log('Server is listening on port 3000');