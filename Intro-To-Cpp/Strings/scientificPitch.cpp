#include <iostream>
#include <string>
#include <iomanip>

using namespace std;
/* algorithm
* makes sure that the string given doesn't have half a note
* cycles through each letter for even indices
* cycles through each number for odd indices
* returns true if all tests are passed
*/
bool isValidTune(string y) {
    if ((y.length() % 2) != 0) {
        return false;
    }
    for (int i = 0; i < y.length(); ++i) {
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
    if (itune.length() < ttune.length()) {
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
* makes sure that the initial tune is greater than the target
* establishes the size
* loops through each input tune and compares it with the target tune
* increments the score accordingly
* returns the score as an int
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
//return point from switch statement
begin :
    int choice = 0;
    string tune1;
    string tune2;
    string tune3;
    string targetTune;
    do {
        cout << "--- Menu ---\n"
            << "1. Calculate similarity between two tunes.\n"
            << "2. Calculate best similarity between two tunes of potentially different lengths.\n"
            << "3. Print three input tunes in order from most to least similar to the target tune.\n"
            << "4. Exit.\n"
            << "Please enter your choice (1 - 4):" << endl;
        cin >> choice;
            if (!((choice > 0) && (choice < 5))) {
                cout << "Invalid Input." << endl;
            }
    } while(!((choice > 0) && (choice < 5)));
        switch (choice) {
/* case 1*/ case 1 : 
                cout << "Please enter the first tune:" << endl;
                cin >> tune1;
                while ((isValidTune(tune1)) == false) {
                    cout << "Invalid input. Please enter a tune in valid SPN:" << endl;
                    cin >> tune1;
                }
                cout << "Please enter the second tune:" << endl;
                cin >> tune2;
                while ((isValidTune(tune2)) == false) {
                    cout << "Invalid input. Please enter a tune in valid SPN:" << endl;
                    cin >> tune2;
                }
                cout << "The similarity score is " << fixed << setprecision(2) << tuneSimilarity(tune1, tune2) << endl;
                goto begin;
/* case 2*/ case 2 : 
                cout << "Please enter the input tune:" << endl;
                cin >> tune1;
                while ((isValidTune(tune1)) == false) {
                    cout << "Invalid input. Please enter a tune in valid SPN:" << endl;
                    cin >> tune1;
                }
                cout << "Please enter the target tune:" << endl;
                cin >> tune2;
                while ((isValidTune(tune2)) == false) {
                    cout << "Invalid input. Please enter a tune in valid SPN:" << endl;
                    cin >> tune2;
                }
                cout << "The best similarity score is: " << fixed << setprecision(2) << bestSimilarity(tune1, tune2) << endl;
                goto begin;
/* case 3*/ case 3 : 
                cout << "Please enter the first tune:" << endl;
                cin >> tune1;
                while ((isValidTune(tune1)) == false) {
                    cout << "Invalid input. Please enter a tune in valid SPN:" << endl;
                    cin >> tune1;
                }
                cout << "Please enter the second tune:" << endl;
                cin >> tune2;
                while ((isValidTune(tune2)) == false) {
                    cout << "Invalid input. Please enter a tune in valid SPN:" << endl;
                    cin >> tune2;
                }
                cout << "Please enter the third tune:" << endl;
                cin >> tune3;
                while ((isValidTune(tune3)) == false) {
                    cout << "Invalid input. Please enter a tune in valid SPN:" << endl;
                    cin >> tune3;
                }
                cout << "Please enter the target tune:" << endl;
                cin >> targetTune;
                while ((isValidTune(targetTune)) == false) {
                    cout << "Invalid input. Please enter a tune in valid SPN:" << endl;
                    cin >> targetTune;
                }
                printTuneRankings(tune1, tune2, tune3, targetTune);
                goto begin;
/* case 4*/ case 4 : 
                cout << "Goodbye!" << endl;
                return 0;
/*default*/ default : 
                cout << "An error has occurred." << endl;
                return -1;
        }    
}