#include <iostream>
#include <string>
#include <cassert>

using namespace std;
/* Algorithm
* begins by creating an initializing a temporary string to use later on without scoping issues.
* creates a counter now to prevent scoping problems
* checks to make sure the input isn't empty
* begins to loop through the input string
* if the separator is present, do not add it to the temp string and push the current temp string into the array
* else if the end of the string has been reached, push what's in the temp string into the array
* else, add the char to temp string like normal
* makes sure that the counter is smaller than the array size.
*/
int split(string input_string, char separator, string arr[], int arr_size) {
    string temp = "";
    int counter = 0;
    if (input_string == temp) {
        return 0;
    }
    for (int i = 0; i < input_string.length(); ++i) {
        if (input_string[i] == separator) {
            arr[counter] = temp;
            ++counter;
            temp = "";
        } else if (i == input_string.length() - 1) {
            temp += input_string[i];
            arr[counter] = temp;
            ++counter;
        } else {
            temp += input_string[i];
        }
    }
    if (counter > arr_size) {
        return -1;
    }
    return counter;
}

int main() {
    string istest1 = "hello my friend";
    char septest1 = ' ';
    string atest1[3];
    int sztest1 = 3;
    assert(split(istest1, septest1, atest1, sztest1) == 3);
    for (int i = 0; i < 3; ++i) {
        cout << atest1[i] << endl;
    }
    //should return 3 and make atest1 hold {"hello","my","friend"}
    string istest2 = "hello my friend";
    char septest2 = ' ';
    string atest2[3];
    int sztest2 = 2;
    assert(split(istest2, septest2, atest2, sztest2) == -1);
    for (int i = 0; i < 3; ++i) {
        cout << atest1[i] << endl;
    }
    //should return -1 and make atest2 hold {"hello","my", "friend"}

}