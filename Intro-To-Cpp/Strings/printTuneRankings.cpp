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

/* Algorithm
* computes the best similarity of each tune with that of the target
* Compares the 6 possible instances with equal to included
* returns the given instance and ends the function.
*/
void printTuneRankings(string tune1, string tune2, string tune3, string targetTune) {
    double rank1 = bestSimilarity(tune1, targetTune);
    double rank2 = bestSimilarity(tune2, targetTune);
    double rank3 = bestSimilarity(tune3, targetTune);
    if ((rank1 >= rank2) && (rank1 >= rank3)) {
        if (rank2 >= rank3) {
            cout << "1) Tune 1, 2) Tune 2, 3) Tune 3" << endl;
        } else {
            cout << "1) Tune 1, 2) Tune 3, 3) Tune 2" << endl;
        }
    } else if ((rank2 >= rank1) && (rank2 >= rank3)) {
        if (rank1 >= rank3) {
            cout << "1) Tune 2, 2) Tune 1, 3) Tune 3" << endl;
        } else {
            cout << "1) Tune 2, 2) Tune 3, 3) Tune 1" << endl;
        }
    } else if ((rank3 >= rank2) && (rank3 >= rank1)) {
        if (rank1 >= rank2) {
            cout << "1) Tune 3, 2) Tune 1, 3) Tune 2" << endl;
        } else {
            cout << "1) Tune 3, 2) Tune 2, 3) Tune 1" << endl;
        }
    }
    return;
}

int main() {
    //the first two functions listed have been tested, so their test cases will not be included
    //* tuneSimilarity has already been tested
    //* bestSimilarity has already been tested
    //test case 1 for printTuneRankings
    //expected output: "1) Tune 2, 2) Tune 3, 3) Tune 1"
    printTuneRankings("C2E7", "D4B3", "A4D1", "A4B7");
    //test case 1 for printTuneRankings
    //expected output: "1) Tune 2, 2) Tune 1, 3) Tune 3"
    printTuneRankings("B8", "C8", "A7", "C8");
    return 0;
}