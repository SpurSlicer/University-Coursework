#include <iostream>
#include <cassert>

using namespace std;
/* Algorithm
* Starts with a for loop that iterates through the arrays of arrays
* creates a loop that iterates through the elements of each sub array with length 4
* if the waitlist is above 0 and if there is an open seat, the seat will be filled and 
the waitlist will be decremented
* It then prints everything and returns the remaining students (waitlist)
*/
int fullClass(bool classroom[][4], int rows, int waitlist) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < 4; ++j) {
            if ((classroom[i][j] == 0) && (waitlist > 0)) {
                classroom[i][j] = 1;
                --waitlist;
            }
            cout << classroom[i][j];
        }
        cout << "\n";
    }
    cout << "Remaining Students: " << waitlist << endl;
    return waitlist;
}

int main() {
    bool test1[1][4] = {{0,1,0,1}};
    int wtest1 = 2;
    assert(fullClass(test1,1,wtest1) == 0);
    //should return 0 students left on the waitlist and return 1,1,1,1 as the classroom
    bool test2[2][4] = {{0,1,0,1}, {0,0,0,0}};
    int wtest2 = 4;
    assert(fullClass(test2,2,wtest2) == 0);
    //should return 0 students left on the waitlist and return 1,1,1,1; 1,1,0,0 as the classroom
    bool test3[3][4] = {{1,1,1,1}, {1,1,1,1}, {1,1,1,0}};
    int wtest3 = 4;
    assert(fullClass(test3,3,wtest3) == 3);
    //should return 3 students left on waitlist and return 12 1s
}
