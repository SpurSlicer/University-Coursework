#include <iostream>
#include <string>
#include <cassert>

using namespace std;
/* Algorithm
* Makes sure the string size is 2
* Cycles through all possible first letters of the note
* Cycles through all possible numbers of the note
* Returns false if the previous two tests failed.
*/
bool isValidNote(string y) {
    if ((y.size() > 2) || (y.size() < 2)) {

    } else if (((((y[0] == 'A') || (y[0] == 'B')) || (y[0] == 'C')) || (y[0] == 'D')) || ((y[0] == 'E') || ((y[0] == 'F') || (y[0] == 'G')))) {
        if ((((((((((y[1] == '0')||(y[1] == '1'))||(y[1] == '2'))||(y[1] == '3'))||(y[1] == '4'))||(y[1] == '5'))||(y[1] == '6'))||(y[1] == '7'))||(y[1] == '8'))||(y[1] == '9')) {
            return true;
        }
    }
    return false;
}
int main() {
    //test 1 for isValidNote
    assert(isValidNote("B2") == true);
    //test 2 for isValidNote
    assert(isValidNote("2B") == false);
    //test 3 for isValidnote
    assert(isValidNote("") == false);
    return 0;
}