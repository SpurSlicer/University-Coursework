const test = document.querySelector(`h1`);
const html = document.querySelector(`html`);
const dart_board = document.querySelector(`#dart-board`);
let dart_board_img = new Image(500, 500);
dart_board_img.src = `../_Images/dart_board.png`;
const ctx = dart_board.getContext(`2d`);
const volume_bar = document.querySelector(`#volume-bar`);
const volume_amt = document.querySelector(`#volume-amt`);
let volume = Math.floor((Math.random() * 101));

dart_board_img.onload = () => {
    ctx.drawImage(dart_board_img, 0, 0, 500, 500);
    volume_bar.style.width = `${(volume/100)*60}vw`;
    volume_amt.textContent = volume;
}
function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}  
const rect = dart_board.getBoundingClientRect();

class Bar {
    constructor(h) {
        this.h = h;
        this.element = document.querySelector(`#slider-bar`);
        this.flag = 0;
    }
    setHeight() {this.element.style.height = `${this.h}vh`;}
    resetHeight() {this.element.style.height = `60vh`; this.flag = 0;}
    setFlag() {
        if (this.h === 0) this.flag = 1;
        else if (this.h === 60) this.flag = 0;
    }
}
class Dart {
    constructor(x, y, state) {
      this.x = x;
      this.y = y;
      this.z = 0;
      this.element = document.querySelector(`#dart`);
      this.state = state;
      this.bar = new Bar(
        60
      );
    }
    setStyle() {this.element.style.scale = 1;}
    fly() {
        if (this.z == 5) { this.z = 0; this.bar.h = 60; return true };
        this.z += 0.25;
        this.y = this.y - ((9+this.bar.h/5)*this.z) + (4.5*(this.z**2));
        this.frame += 1;
        return false;
    }
}
let dart = new Dart(
    -1000,
    1000,
    0
);
dart.bar.setHeight();
dart.setStyle();
const interval = setInterval(update, 15);
function update() {
    switch (dart.state) {
        case 0:
            dart.element.style.scale = 1;
            dart.bar.resetHeight();
            const d_rect = dart_board.getBoundingClientRect();
            const d_you = dart.element.getBoundingClientRect();
            //if (((d_you.left <= d_rect.right) && (d_you.left >= d_rect.left)) && ((d_you.top >= d_rect.top) && (d_you.top <= d_rect.bottom)))
            //    test.textContent = `You: ${Math.floor(d_you.top-d_rect.top)}, ${Math.floor(d_you.left-d_rect.left)}`;
            //else test.textContent = `Dart out of range!`;
            dart.element.style.left = `${dart.x-25}px`;
            dart.element.style.top = `${dart.y-25}px`;
            break;
        case 1:
            //test.textContent = `(${dart.bar.h})`;
            if (dart.bar.flag === 0) dart.bar.h -= 1;
            else dart.bar.h += 1;
            dart.bar.setHeight();
            dart.bar.setFlag();
            break;
        case 2:
            //test.textContent = `(${dart.element.style.left}, ${dart.element.style.top}, ${dart.z})`;
            if (!dart.fly()) {
                dart.element.style.left = `${dart.x-25}px`;
                dart.element.style.top = `${dart.y-25}px`;
                dart.element.style.scale -= 0.02;
            } else dart.state = 3;
            break;
        case 3:
            const rect = dart_board.getBoundingClientRect();
            const you = dart.element.getBoundingClientRect();
            let r = `ff`, g = `ff`, b = `ff`;
            if (((you.left <= rect.right) && (you.left >= rect.left)) && ((you.top >= rect.top) && (you.top <= rect.bottom))) {
                const color_buffer = ctx.getImageData(you.left-rect.left, you.top-rect.top, 1, 1);
                r = color_buffer.data[0].toString(16);
                g = color_buffer.data[1].toString(16);
                b = color_buffer.data[2].toString(16);
            }
            //test.textContent = `#${r}${g}${b}`;
            const color = `#${r}${g}${b}`;
            switch(color) {
                case `#ff9494`: //red
                    volume += 7;
                    if (volume < 0) volume = 0;
                    else if (volume > 100) volume = 100;
                    break;
                case `#ffb694`: //orange
                    volume -= 12;
                    if (volume < 0) volume = 0;
                    else if (volume > 100) volume = 100;
                    break;
                case `#eeff94`: //yellow
                    volume += 5;
                    if (volume < 0) volume = 0;
                    else if (volume > 100) volume = 100;
                    break;
                case `#9fff94`: //green
                    volume -= 2;
                    if (volume < 0) volume = 0;
                    else if (volume > 100) volume = 100;
                    break;
                case `#94f9ff`: //cyan
                    volume += 6;
                    if (volume < 0) volume = 0;
                    else if (volume > 100) volume = 100;
                    break;
                case `#9494ff`: //blue
                    volume -= 7;
                    if (volume < 0) volume = 0;
                    else if (volume > 100) volume = 100;
                    break;
                case `#c194ff`: //purple
                    volume += 12;
                    if (volume < 0) volume = 0;
                    else if (volume > 100) volume = 100;
                    break;
                case `#ff94ee`: //magenta
                    volume += 2;
                    if (volume < 0) volume = 0;
                    else if (volume > 100) volume = 100;
                    break;
                case `#cacaca`: //light gray
                    volume *= 2;
                    if (volume < 0) volume = 0;
                    else if (volume > 100) volume = 100;
                    break;
                case `#909090`: //gray
                    volume /= 2;
                    volume = Math.floor(volume);
                    if (volume < 0) volume = 0;
                    else if (volume > 100) volume = 100;
                    break;
                case `#4f4f4f`: //dark gray
                    volume = 100;
                    break;
                case `#000`: //black 
                    volume = 0;
                    break;
                default: //white et. al
                    break;
            }
            volume_bar.style.width = `${(volume/100)*60}vw`;
            volume_amt.textContent = volume;       
            dart.state = 4;
            break;
        default:
            //console.log("I should not be here");
            break;
    }
}

document.addEventListener(`mousemove`, (event) => {
    if (dart.state == 0) {
        dart.x = event.clientX;
        dart.y = event.clientY;
    }
});

document.addEventListener(`mousedown`, (event) => {
    if (dart.state === 0) dart.state = 1;
    else if (dart.state === 4) {
        dart.state = 0;
        dart.x = event.clientX;
        dart.y = event.clientY;
    }
});

document.addEventListener(`mouseup`, (event) => {
    if (dart.state === 1) dart.state = 2;
});