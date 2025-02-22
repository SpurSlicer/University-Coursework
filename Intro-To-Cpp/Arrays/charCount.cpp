#include <iostream>
#include <string>

using namespace std;
/* Algorithm
* this starts by getting a just-before ascii character and two ints which we will use later
* it then starts a loop and iterates 53 times (not including the 53rd)
this checks every possible alphabetical letter
* it then works through some conditionals to either increment or jump to the next set of alphabetical letters
* it then checks each letter inside of the given string to see if it matches the one in the parent loop
* if the counter for these letters is ever not 0 aftwards, it prints out the character and the count.
* the global counter also increases; it represents number of unique characters
* it then ends by returning the number of unique variables (counter_global)
*/
int charCount(string input_text) {
    char ascii = '@';
    int counter = 0;
    int counter_global = 0;
    for (int i = 0; i < 53; ++i) {
        if(i == 27) {
            ascii = 'a';
        } else {
            ++ascii;
        }
        for (int j = 0; j < input_text.length(); ++j) {
            if (input_text[j] == ascii) {
                ++counter;
            }
        }
        if (counter != 0) {
            cout << (char) ascii << ": " << counter << endl;
            counter = 0;
            ++counter_global;
        }  
    }
    return counter_global;
}

int main() {
    string test = "Hello";
    charCount(test);
    //this should print out H: 1; e: 1; l: 2; o: 1 and return 4
    string test2 = "";
    charCount(test2);
    //this should print out nothing and return 0
    string test3 = "12345!@#$%";
    charCount(test3);
    //this should print out nothing and return 0
    return 0;
}