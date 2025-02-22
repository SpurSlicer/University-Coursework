#include <iostream>
#include <string>
#include <cassert>

using namespace std;
/* algorithm
* makes sure that the string given doesn't have half a note
* cycles through each letter for even indices
* cycles through each number for odd indices
* returns true if all tests are passed
*/
bool isValidTune(string y) {
    if (y.size() == 0) {
        return false;
    }
    if ((y.size() % 2) != 0) {
        return false;
    }
    for (int i = 0; i < y.size(); ++i) {
        if ((i % 2 )== 0) {
            if (((((y[i] == 'A') || (y[i] == 'B')) || (y[i] == 'C')) || (y[i] == 'D')) || ((y[i] == 'E') || ((y[i] == 'F') || (y[i] == 'G')))) {
            } else {
                return false;
            }
        } else {
            if ((((((((((y[i] == '0')||(y[i] == '1'))||(y[i] == '2'))||(y[i] == '3'))||(y[i] == '4'))||(y[i] == '5'))||(y[i] == '6'))||(y[i] == '7'))||(y[i] == '8'))||(y[i] == '9')) {
            } else {
                return false;
            }
        }
    }
    return true;
}

int main() {
    //test 1 for isValidTune
    assert(isValidTune("HELLO World!") == false);
    //test 2 for isValidTune
    assert(isValidTune("A1B2C3D4E5") == true);
    //test 3 for isValidTest
    assert(isValidTune("") == false);
    return 0;
}