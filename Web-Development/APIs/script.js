const btn = document.querySelector(`#js-new-quote`);
const btnAnswer = document.querySelector(`#js-investigate-author`);
const textboxContent = document.querySelector(`#js-quote-text`);
const textboxAuthor = document.querySelector(`#js-answer-text`);

let author = ``;
const apiURL = `https://api.quotable.io/random`;
async function getAndDisplayQuote() {
    await fetch(apiURL)
        .then(async (res) => {
             await res.json()
                .then((json) => {
                    //console.log(`Quote found: ${json.question}`);
                    author = json.author;
                    textboxContent.textContent = (`"` + json.content + `"`);
                    textboxAuthor.textContent = (`- ` + author);
                    console.log(`${json.content} ${json.author}`);
                })
                .catch(() => {
                    console.log(`Quote not found`);
                });
        })
        .catch((err) => {
            console.log(`Error occured ${err}`);
            alert(`Error occured ${err}`);
        });
    return;
}

btn.addEventListener('click', () => {
    textboxContent.textContent = ``;
    textboxAuthor.textContent = ``;
    getAndDisplayQuote();
    return;
});

btnAnswer.addEventListener('click', () => {
    const formattedString = author.replace(` `, `_`);
    console.log(`Formatted string is ${formattedString}`);
    window.open(
        (`https://en.wikipedia.org/wiki/` + formattedString),
        `_blank` // <- This is what makes it open in a new window.
    );
    return;
});

window.onload = () => {
    getAndDisplayQuote();
    return;
}