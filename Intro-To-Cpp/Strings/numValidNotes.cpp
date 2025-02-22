#include <iostream>
#include <string>
#include <cassert>

using namespace std;

/* Algorithm
* Makes sure the string isn't empty
* Tests every tune and increases a function scope counter when a note is valid
* returns num of valid notes
*/
int numValidNotes(string y) {
    int c = 0;
    if (y.size() == 0) {
        return c;
    }
    for (int i = 0; i < y.size() - 1; ++i) {
        if (((((y[i] == 'A') || (y[i] == 'B')) || (y[i] == 'C')) || (y[i] == 'D')) || ((y[i] == 'E') || ((y[i] == 'F') || (y[i] == 'G')))) {
            if ((((((((((y[i+1] == '0')||(y[i+1] == '1'))||(y[i+1] == '2'))||(y[i+1] == '3'))||(y[i+1] == '4'))||(y[i+1] == '5'))||(y[i+1] == '6'))||(y[i+1] == '7'))||(y[i+1] == '8'))||(y[i+1] == '9')) {
                ++c;
            }
        }
    }
    return c;
}

int main() {
    //test case 1 for numValidNotes
    assert(numValidNotes("A1B2C3D4E5") == 5);
    //test case 2 for numValidNotes
    assert(numValidNotes("A11AB11B") == 2);
    //test case 3 for numValidNotes
    assert(numValidNotes("") == 0);
    return 0;
}