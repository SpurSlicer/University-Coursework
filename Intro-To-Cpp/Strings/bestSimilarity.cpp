#include <iostream>
#include <string>
#include <cassert>

using namespace std;

/* Algorithm
* ensures the strings are of the same length
* initializes correct notes, 
correct notes and pitches, and different of both
* cycles through every tune
* increments each vairable accordingly
* executes a formula to calculate the tune similarity
* returns said similarity
*/
double tuneSimilarity(string y, string z) {
    if (y.length() != z.length()) {
        return 0;
    }
    int n = 0;
    int p = 0;
    int d = 0;
    double ans = 0;
    for (int i = 0; i < y.length(); i += 2) {
        if (y.substr(i,1) == z.substr(i,1)) {
            ++n;
            if (y.substr(i+1,1) == z.substr(i+1,1)) {
            ++p;
            }
        } else if (y.substr(i+1,1) != z.substr(i+1,1)) {
            ++d;
        }
    }
    ans = ((n / (y.length()/2.0)) + p) - d;
    return ans;
}

/* Algorithm
* makes sure that the initial tune is greater than the target
* establishes the size
* loops through each input tune and compares it with the target tune
* increments the score accordingly
* returns the score as an int
*/
double bestSimilarity(string itune, string ttune) {
    double score = 0;
    if (itune.size() < ttune.size()) {
        return 0;
    }
    int size = (itune.size() - ttune.size());
    for (int i = 0; i <= size; i += 2) {
        string temp = itune.substr(i,ttune.size());
        double tempScore = tuneSimilarity(temp, ttune);
        if(i == 0) {
            score = tempScore;
        } else if (tempScore > score) {
            score = tempScore;
        }
    }
    return score;
}

int main() {
    //tuneSimilarity has already been tested
    //test case 1 for bestSimilarity
    assert(bestSimilarity("A2G7", "E9D2C4F1") == 0);
    //test case 2 for bestSimilarity
    assert(bestSimilarity("A2", "A2") == 2);
    return 0;
}