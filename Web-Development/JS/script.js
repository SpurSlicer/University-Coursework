// PART 1
const customName = document.getElementById('customname');
const randomize = document.querySelector('.randomize');
const story = document.querySelector('.story');

function randomValueFromArray(array){
  const random = Math.floor(Math.random()*array.length);
  return array[random];
}

// PART 2
const insertX = [`The Marshmallow Man`, `Spongebob`, `Paddle Pop`];
const insertY = [`a tree house`, `the backrooms`, `a mirror`];
const insertZ = [`spontaneously combusted`, `turn[ed] into a black hole`, `start[ed] photosynthesizing`];

// PART 3
randomize.addEventListener('click', result);

function result() {
  const xItem = randomValueFromArray(insertX);
  const yItem = randomValueFromArray(insertY);
  const zItem = randomValueFromArray(insertZ);
  let name = `Sam`;
  let weight = 250, weightNotation = `Pounds`;
  let degrees = 64, degreeNotation = `Fahrenheit`;

  if(customName.value !== '') {
    name = customName.value;
  }

  if(document.getElementById("uk").checked) {
    weight = Math.round(weight/2.2046);
    weightNotation = `Kilograms`;
    degrees =  Math.round((degrees - 32) * (5/9));
    degreeNotation = `Celsius`;
  }
  const newStory = `It was ${degrees} ${degreeNotation}--quite the lovely day--and ${xItem} decided to go explore the nearby forest. During the expedition, they encountered ${yItem}, thus causing them to ${zItem} in utter shock. ${name}, a local hermit, whitnessed the ghastly site. ${xItem} ran away and noticed that ${name} weighed around ${weight} ${weightNotation}. Quite the odd observation, but stress does crazy things to people. When ${xItem} returned home, they immediately ${zItem} once more.`;
  story.textContent = newStory;
  story.style.visibility = 'visible';
}