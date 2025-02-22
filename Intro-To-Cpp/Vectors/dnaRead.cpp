#include <iostream>
#include <string>
#include <vector>
using namespace std;
/* ALGORITHM 
Starts by getting the size and by creating a string that will be used.
It also creates a flag that will be activated once the start codon is recognized
It then searches the vector for any invalid sequences.
If the sequences are all valid, it then starts to loop through each sequence
It only will start adding sequences to the return once the start codon is found
If the start codon is found, the flag is activated to show the program that it is time to start recording
It then records each following codon until a stop codon is recognized or until the end of the vector is reached
Depending on the outcome, it will return the string initialized in the beginning
*/
string dnaRead(vector<string> vec) {
    int size = vec.size();
    string str = "";
    bool flag = false;
    //searches for invalid sequences
    for (int i = 0; i < size; ++i) {
        string temp = vec.at(i);
        if (temp.length() != 3) {
            return "Invalid sequence.";
        }
        for (int j = 0; j < 3; ++j) {
            if((temp[j] != 65) && (temp[j] != 67) && (temp[j] != 71) && (temp[j] != 84)){
                return "Invalid sequence.";
            }
        }
    }
    //Iterates through the vector
    for (int i = 0; i < size; ++i) {
        if ((vec.at(i) == "ATG") || (flag)) {
            if (!flag) {
                flag = true;
            } else {
                string temp = vec.at(i);
                if ((temp == "TAA") || (temp == "TAG") || (temp == "TGA")) {
                    return str;
                } else if (i == (size-1)) {
                    str += temp;
                    return str;
                } else {
                    str += temp;
                } 
            }
        }
    }
    return str;
}
int main() {
    vector<string> empty;
    vector<string> valid{"ATG", "CAT", "ACT", "GAC", "TAA", "ACT", "TAC"};
    vector<string> weird_but_valid{"CAT", "ATG", "CAT", "ACT", "GAC", "TAA", "ACT", "TAC"};
    vector<string> valid_but_no_end{"CAT", "ATG", "CAT", "ACT", "GAC", "GGG"};
    vector<string> invalid{"REEE", "ACT", "HEEEIEWIOEJAF"};
    // TEST 1: recognizing empty vector
    cout << dnaRead(empty) << endl; // should print nothing
    // TEST 2: printing a valid vector
    cout << dnaRead(valid) << endl;  // should print CATACTGAC 
    // TEST 3: printing a valid vector with delayed start codon
    cout << dnaRead(weird_but_valid) << endl; // should print CATACTGAC
    // TEST 4: printing a valid vector with no end codon
    cout << dnaRead(valid_but_no_end) << endl; // should print CATACTGACGGG
    // TEST 5: recognizing invalid vectors
    cout << dnaRead(invalid) << endl;  // should print Invalid sequence.
    return 0;
}