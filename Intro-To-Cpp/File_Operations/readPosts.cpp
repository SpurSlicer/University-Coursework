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
Starts by initializing variables under the correct scope as well as the file
Opens the file
If the file doesn't open, return with -1
If the file is open, go about a while statement that makes sure that the file hasn't reached the end of the file
Create an initialized array under the while loop scope
     This is so it resets after every instance
Get the line and split it into 3 indices within an array
This for loop ensures that no elements in the array are empty
If all elements in this line pass, then increment the line number
return the line number 
*/
int readPosts(string filename) {
    ifstream myFile;
    string line;
    int line_num = 0;
    myFile.open(filename);
    if (myFile.fail()) {
        return -1;
    } else {
        while (!myFile.eof()) {
            string arr[3] = {"","",""};
            getline(myFile, line);
            split(line, ',', arr, 3);
            int temp = 0;
            for (int i = 0; i < 3; ++i) {
                if (arr[i] != "") {
                    ++temp;
                }
            }
            if (temp == 3) {
                ++line_num;
            }
        }
    return line_num;
    }
}

int main() {
    string filename = "posts.txt";
    int num_posts = readPosts(filename);
    if (num_posts == -1) {
        cout << "Could not open file." << endl;
    } else {
        cout << "Read " << num_posts << " posts." << endl;
    }
    //should return: Read 28 posts.
    string filename2 = "empty.txt";
    int num_posts2 = readPosts(filename2);
    if (num_posts2 == -1) {
        cout << "Could not open file." << endl;
    } else {
        cout << "Read " << num_posts2 << " posts." << endl;
    }
    //should return: Read 0 posts.
    string filename3 = "posts_bad.txt";
    int num_posts3 = readPosts(filename3);
    if (num_posts3 == -1) {
        cout << "Could not open file." << endl;
    } else {
        cout << "Read " << num_posts3 << " posts." << endl;
    }
    //should return: Read 24 posts.

}