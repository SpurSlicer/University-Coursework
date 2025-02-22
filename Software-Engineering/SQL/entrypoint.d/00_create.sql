-- TODO: Add your `CREATE` statements to this file.
CREATE TABLE IF NOT EXISTS movies (
    id INT PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    duration SMALLINT NOT NULL,
    year_of_release SMALLINT NOT NULL,
    gross_revenue DECIMAL NOT NULL,
    country VARCHAR(30) NOT NULL,
    language VARCHAR(100) NOT NULL,
    imdb_rating DECIMAL NOT NULL,
    platform_id INT NOT NULL
);
CREATE TABLE IF NOT EXISTS actors (
    id INT PRIMARY KEY NOT NULL,
    name VARCHAR(100) NOT NULL,
    agency VARCHAR(100) NOT NULL,
    active_since INT NOT NULL,
    location VARCHAR(100)
);
CREATE TABLE IF NOT EXISTS platforms (
    id INT PRIMARY KEY NOT NULL,
    name VARCHAR(100) NOT NULL,
    viewership_cost DECIMAL NOT NULL
);
CREATE TABLE IF NOT EXISTS genres (
    id INT PRIMARY KEY NOT NULL,
    name VARCHAR(100) NOT NULL
);
CREATE TABLE IF NOT EXISTS movies_to_actors (
    movie_id INT NOT NULL,
    actor_id INT NOT NULL
);
CREATE TABLE IF NOT EXISTS movies_to_genres (
    movie_id INT NOT NULL,
    genre_id INT NOT NULL
);

/*
CREATE TABLE
CREATE TABLE
CREATE TABLE
CREATE TABLE
CREATE TABLE
CREATE TABLE
*/