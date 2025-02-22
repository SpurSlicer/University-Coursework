#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <cctype>

using namespace std;

/*
begins by creating an initializing a temporary string to use later on without scoping issues.
creates a counter now to prevent scoping problems
checks to make sure the input isn't empty
begins to loop through the input string
if the separator is present, do not add it to the temp string and push the current temp string into the array
else if the end of the string has been reached, push what's in the temp string into the array
else, add the char to temp string like normal
makes sure that the counter is smaller than the array size.
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
/*
Begins by initializing function-scoped variables to use throughout the program
Attempts to open the file
If the file doesn't open, inform the user and switch flow control back ot main
Else, meaning if the file is open, start running stuff if the end of the file has not been reached
Get the first line of the file and make sure that it isn't empty
Split the line into an array of size 2 and assign them to their variables if this is the first instance
     Remember that stoi converts the string type holding numbers into an int
If it isn't the first instance, test whether the value is greater or smaller than the previous values
If it is either or, then assign it accordingly
Print the results and return flow control
*/
void printMountainStats(string filename) {
    ifstream myFile;
    string line;
    string gmount;
    string lmount;
    string arr[2] = {};
    int line_num = 0;
    int gheight = 0;
    int lheight = 0;
    myFile.open(filename);
    if (myFile.fail()) {
        cout << "Could not open file." << endl;
        return;
    } else {
        while (!myFile.eof()) {
            getline(myFile, line);
            if (line != "") {
                line_num += 1;
            }
            split(line, '|', arr, 2);
            if (line_num <= 1) {
                gmount = arr[0];
                lmount = arr[0];
                gheight = stoi(arr[1]);
                lheight = stoi(arr[1]);
            } else if (((stoi(arr[1])) > gheight)) {
                gmount = arr[0];
                gheight = stoi(arr[1]);
            } else if (((stoi(arr[1])) < lheight)) {
                lmount = arr[0];
                lheight = stoi(arr[1]);
            }
        }
    }
    cout << "Number of lines read: " << line_num << "."
        << "\nTallest Mountain: " << gmount << " at " << gheight << " feet."
        << "\nShortest mountain: " <<  lmount << " at " << lheight << " feet." << endl;
    return;
}

int main() {
    printMountainStats("mountain_data.txt");
    /*
    Should print: 
    Number of lines read: 3.
    Tallest Mountain: Pikes Peak at 14114 feet.
    Shortest mountain: Vermilion Peak at 13894 feet.
    */
    printMountainStats("mountain_data_with_empty.txt");
    /*
    Should print: 
    Number of lines read: 3.
    Tallest Mountain: Pikes Peak at 14114 feet.
    Shortest mountain: Vermilion Peak at 13894 feet.
    */
    return 0;
}