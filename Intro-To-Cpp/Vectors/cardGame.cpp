#include <iostream>
#include <vector>
using namespace std;
/* HELPER FUNCTION
If input is less than 1 or greater than 14, return false
If not, return true, meaning it is valid
*/
bool valid(int input) {
    if ((input < 1) || (input > 14)) {
        return false;
    } else {
        return true;
    }
}
/* HELPER FUNCTION
Pushes 1 (the input) onto the vector heap
Get's the new size
It then attepmts to erase the beginning two elements
It increases the counter and updates the vector through pass by reference
It also updates the size in case only 1 element is stored in the vector
It then returns flow control
*/
void remove_one(vector<int> &vec, int &val, int input) {
    vec.push_back(input);
    int size = vec.size();
    for (int i = 0; i < 2; ++i) {
        if (size > 0) {
            vec.erase(vec.begin());
            ++val;
            size = static_cast<int>(vec.size());
        } 
    }
    return;
}
/* HELPER FUNCTION
Get's the new size
Since the pushed value will always be popped off, it does not include it.
If the size isn't zero, it then pops off the other element and updates the valueto indicate a success.
If not, it increase the count to show that the drawn card was popped off. 
It updates the vector and count through pass by reference
It then returns flow control
*/
void remove_two(vector<int> &vec, int &val) {
    int size = static_cast<int>(vec.size());
    if (size > 0) {
        vec.pop_back();
        val += 2;
    } else {
        ++val;
    }
    return;
}
/* HELPER FUNCTION
Returns all of the remaining cards stored in the vector
It then returns the count to show how many cards the player with the deck has left
If count of cards is greater than the size, the player with the deck wins (us)
If count of cards is less than the size, the player drawing the cards wins (them)
If the values are equal, it is a tie.
Returns flow control.
*/
void winnings(vector<int> vec, int count) {
    cout << "Your remaining cards are: ";
    int size = vec.size();
    for (int i = 0; i < size; ++i) {
        cout << vec.at(i) << " ";
        //++count;
    }
    cout << "\nI have " << count << " card(s)." << endl;
    if (count > size) {
        cout << "I win!";
    } else if (count < size) {
        cout << "You win!";
    } else {
        cout << "Tie!";
    }
    return;
} 

int main() {
    vector<int> deck;
    int count = 0;
    int input = 0;
    //Loops through card drawing and calls helper functions as needed.
    do {
        cout << "Please enter a number:" << endl;
        cin >> input;
        if (!valid(input)) {
            cout << "The number should be an integer between 1 and 14." << endl;
        } else if (input == 1) {
            remove_one(deck, count, input);
        } else if ((input == 11) || (input == 12) || (input == 13)) {
            remove_two(deck, count);
        } else if (input == 14) {
            break;
        } else {
            deck.push_back(input);
        }
    } while (true);
    //Get's the winner
    winnings(deck, count);
    //terminates program
    return 0;
}
    