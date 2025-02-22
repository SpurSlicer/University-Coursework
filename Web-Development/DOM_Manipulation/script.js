const displayedImage = document.querySelector('.displayed-img');
const thumbBar = document.querySelector('.thumb-bar');

const btn = document.querySelector('button');
const overlay = document.querySelector('.overlay');

/* Declaring the array of image filenames */
const filenames = ['pic1.jpg', 'pic2.jpg', 'pic3.jpg', 'pic4.jpg', 'pic5.jpg'];

/* Declaring the alternative text for each image file */
const altnames = {
    'pic1.jpg': 'open eye',
    'pic2.jpg': 'abstract art',
    'pic3.jpg': 'purple and white flowers',
    'pic4.jpg': 'egyption scripture',
    'pic5.jpg': 'moth creature'
}

/* Looping through images */
const filepath = '../_Images/';
filenames.forEach(filename => {
    const newImage = document.createElement('img');
    newImage.setAttribute('src', filepath+filename);
    newImage.setAttribute('alt', altnames[filename]);
    thumbBar.appendChild(newImage);
    newImage.addEventListener('click', () => {
        displayedImage.setAttribute('src', filepath+filename);
        displayedImage.setAttribute('alt', altnames[filename]);
    });
});

/* Wiring up the Darken/Lighten button */
btn.addEventListener('click', () => {
    const button_current_class = btn.getAttribute('class');
    if (button_current_class === 'dark') {
        btn.setAttribute('class', 'light');
        btn.textContent = 'Lighten';
        overlay.style.backgroundColor = 'rgb(0 0 0 / 50%)';
    } else if (button_current_class === 'light') {
        btn.setAttribute('class', 'dark');
        btn.textContent = 'Darken';
        overlay.style.backgroundColor = 'rgb(0 0 0 / 0%)';
    } else console.log("Error occurred");
});