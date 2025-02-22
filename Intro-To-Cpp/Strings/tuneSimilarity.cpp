#include <iostream>
#include <string>
#include <cassert>

using namespace std;

/* Algorithm
* initializes correct notes, 
correct notes and pitches, and different of both
* cycles through every tune
* increments each vairable accordingly
* executes a formula to calculate the tune similarity
* returns said similarity
*/
double tuneSimilarity(string y, string z) {
    int n = 0;
    int p = 0;
    int d = 0;
    double ans = 0;
    if (y.size() != z.size()) {
        return 0;
    }
    for (int i = 0; i < y.size(); i += 2) {
        if (y.substr(i,1) == z.substr(i,1)) {
            ++n;
            if (y.substr(i+1,1) == z.substr(i+1,1)) {
            ++p;
            }
        } else if (y.substr(i+1,1) != z.substr(i+1,1)) {
            ++d;
        }
    }
    ans = ((n / (y.size()/2.0)) + p) - d;
    return ans;
}

int main() {
    //test case 1 for tuneSimilarity
    assert(tuneSimilarity("G5E6", "E5G5") == -1);
    //test case 2 for tuneSimilarity
    assert(tuneSimilarity("A1B2C3", "D4E5G6") == -3);
    //test case 3 for tuneSimilarity
    assert(tuneSimilarity("D5G2", "F7D1E4G4") == 0);
    return 0;
}