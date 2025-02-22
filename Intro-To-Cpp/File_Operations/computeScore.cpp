#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <cctype>
#include <iomanip>

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
Starts by creating variables at this larger scope and by creating the file
Opens the file
If the file does not open, then return -1
If the file is open, do stuff while the file hasn't ended and the line number is smaller than the given size
Create a large array to encompass excess data
Get the line of text and attempt to split it
If splitting it yields a value other than 4, do not proceed and skip the line
If the array number is valid and the restaurant index exists, proceed
Loop through the ratings-part of the original array and adds the stoi versions it to the new ratings 2d array
It then adds the restaurant from the entry and places it in the restaurant array
Returns the number of lines that have been successfully counted.
*/
int readRestaurantData(string filename, string restaurants[], int ratings[][3], int arrSize) {
    ifstream myFile;
    string line;
    int line_num = 0;
    myFile.open(filename);
    if (myFile.fail()) {
        return -1;
    } else {
        while ((!myFile.eof()) && (line_num < arrSize)) {
                string arr[10] = {"","0","0","0"};
                getline(myFile, line);
                if (split(line, '~', arr, 4) == 4) {
                    if ((arr[0] != "")) {
                        for (int j = 1; j < 4; j++) {
                            ratings[line_num][j-1] = stoi(arr[j]);
                        }
                        restaurants[line_num] = arr[0];
                        ++line_num;
                    }
                }
            }
        }
    return line_num;
}

/*
NOTE: Uses passed by reference data from the readRestaurantData function
Loops through the restaurants array and prints each score using the values from the ratings 2d array
Uses the following formula: score = (6.3 * Food Quality Rating) + (4.3 * Cleanliness Rating) + (3.4 * (5 - Wait Time Rating))
Returns flow control
*/
void calcOverallScore(string restaurants[], int ratings[][3], int num_restaurants) {
    for (int i = 0; i < num_restaurants; ++i) {
        cout << restaurants[i] << " overall score: " << fixed << setprecision(1)
            << ((ratings[i][0] * 6.3) + ( ratings[i][1] * 4.3) + (3.4 * (5 - (ratings[i][2])))) << endl;
    }
}

/*
NOTE: Uses passed by reference data from the readRestaurantData function
Loops through the restaurants array and prints each one
Returns flow control
*/
void printNames(string restaurants[], int num_lines) {
    for (int i = 0; i < num_lines; ++i) {
        cout << "names[" << i << "] = " << restaurants[i] << endl;
    }
    return;
}

/*
NOTE: Uses passed by reference data from the readRestaurantData function
Loops through the ratings 2d array and prints each one for each restaurant
Returns flow control
*/
void printRatings(int ratings[][3], int num_lines) {
    for (int i = 0; i < num_lines; ++i) {
        cout << "food quality: " << ratings[i][1] << "/ 10, cleanliness: " << ratings[i][2] << "/ 5, wait time: " << ratings[i][3] << " / 5" << endl;
    }
}

int main() {
    string filename = "restaurant_samples.txt";

    // max number of restaurants to read
    int num_restaurants = 5;

    // make arrays to store data
    string restaurants[num_restaurants];
    int ratings[num_restaurants][3];

    // call read data function
    int num_lines = readRestaurantData(filename, restaurants, ratings, num_restaurants);

    if (num_lines == -1) {
        cout << "Could not open file." << endl;
    } else {
        calcOverallScore(restaurants, ratings, num_lines);
    }
    /*Tests pretty much everything. Should print:
    Wendys overall score: 60.9
    Chick-fil-a overall score: 78.2
    Snarfburger overall score: 87.0
    Cosmo's Pizza overall score: 67.2
    McDonalds overall score: 31.4
    */
}
