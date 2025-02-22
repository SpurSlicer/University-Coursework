/* Compilation Command:
g++ -std=c++11 driver.cpp MovieHashTable.cpp DirectorSkipList.cpp -o movie-db
./movie-db IMDB-Movie-Data.csv 2000 2000
valgrind --leak-check=full --track-origins=yes ./movie-db IMDB-Movie-Data.csv 2000 2000
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "MovieHashTable.hpp"
#include "DirectorSkipList.hpp"

using namespace std;

/**
* Declares function prototypes
*/
MovieNode* parseMovieLine(string line);
void readMovieCSV(string filename,  MovieHashTable &movieTable, DirectorSkipList &directorList);
void display_menu();


/**
* Begins by checking if the number of arguments entered is 4. If it isn't, it displays what the correct arguments look like.
* It then uses the args provided to create a movie hash table and a director skip list.
* Then it calles readMovieCSV (see that function descrpition for details)
* Assuming the file was able to be read and parsed, the input character and temporary string are created for repeated use.
* The number of collisions are then displayed
* Then, the menu is displayed and the user is free to choose which option they'd like to do.
*   1. Displays the director of a certain movie.
*   2. Displays the number of movies produced by a certain director
*   3. Returns general information of a certain movie (i.e., description, genre, year, etc.)
*   4. Shows all movies produced by a certain director
*   5. Quits the program
*   Default: if an unrecognized input is entered, a saterical comment is displayed.
* That is the end of the main function!
* @param int, char**
* @return int
*/
int main(int argc, char** argv) {
    if (argc != 4) {
        cout << "Invalid number of arguments." << endl << "Usage: ./<program name> <csv file> <hashTable size> <skipList size>" << endl;
        return -1;
    }
    //---
    MovieHashTable movieTable(stoi(argv[2]));
    DirectorSkipList directorList(stoi(argv[3]), 10);
    readMovieCSV(argv[1], movieTable, directorList);
    //---
    char input = '\0'; //This is used to choose options
    string str_input = ""; //This is used in the switch statement as an istream reciever from cin
    cout << "Number of collisions: " << movieTable.getCollisions() << endl;
    while (true) {
        display_menu();
        input = getchar();
        switch (input) {
            case '1': //Find director of a movie
                cout << "Enter movie name: ";
                cin.ignore();
                getline(cin,str_input);
                if (movieTable.search(str_input)) {
                    cout << "The director of " 
                        << str_input
                        << " is "
                        << movieTable.search(str_input)->director << endl;
                } else {
                    cout << "Movie not found" << endl;
                }
                break;
            case '2': //Find number of movies by a director
                cout << "Enter director name: ";
                cin.ignore();
                getline(cin,str_input);
                if  (directorList.search(str_input) != nullptr) {
                    cout << str_input 
                        << " has directed "
                        << directorList.search(str_input)->movies.size()
                        << " movies" << endl;
                } else {
                    cout << "Director not found" << endl;
                }
                break;  
            case '3': //Find the description of a movie
                cout << "Enter movie name: ";
                cin.ignore();
                getline(cin,str_input);
                if (movieTable.search(str_input)) {
                    cout << str_input
                        << " is a "
                        << movieTable.search(str_input)->year
                        << " ("
                        << movieTable.search(str_input)->genre
                        << " ) film featuring "
                        << movieTable.search(str_input)->actors
                        << "." << endl << "Plot: "
                        << movieTable.search(str_input)->description
                        << "." << endl;
                } else {
                    cout << "Movie not found" << endl;
                }
                break;
            case '4': //List the movies by a director
                cout << "Enter director name: ";
                cin.ignore();
                getline(cin,str_input);
                if (directorList.search(str_input)) {
                    cout << str_input
                        << " directed the following movies:" << endl;
                    for (int i = 0; i < static_cast<int>(directorList.search(str_input)->movies.size()); ++i) {
                        cout << i << ": " << directorList.search(str_input)->movies[i] << endl;
                    }
                } else {
                    cout << "Director not found" << endl;
                }
                break;
            case '5': //Quit
                cout << "Thanks for using me!" << endl;
                movieTable.~MovieHashTable();
                directorList.~DirectorSkipList();
                return 0;
                break;
            default:
                cout << "idk what that means 💀💀💀" << endl;
        }
        str_input.clear();
        input = '\0';
    }
    return 0;
}

/**
* Parses through a given line to create a movie node.
* If the string length does not match or is empty, nullptr will be returned.
* Else, then the complete movie node will be returned.
* @param string
* @return MovieNode*
*/
MovieNode* parseMovieLine(string line) {
    stringstream ss(line);
    vector<string> fields;
    string field;

    // Loop through the characters in the line
    bool in_quotes = false;
    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];
        if (c == '\"') {
            in_quotes = !in_quotes;
        } else if (c == ',' && !in_quotes) {
            // add field to vector and reset for next field
            fields.push_back(field);
            field.clear();
        } else {
            field += c;
            // handle double quotes inside a quoted field
            if (in_quotes && c == '\"' && i < line.length() - 1 && line[i+1] == '\"') {
                field += '\"'; // add the second double quote and skip it
                ++i;
            }
        }
    }
    fields.push_back(field);

    if (fields.size() != 12) {
        cerr << "Error: Invalid movie line format" << line << endl;
        return nullptr;
    }

    int rank = stoi(fields[0]);
    string title = fields[1];
    string genre = fields[2];
    string description = fields[3];
    string director = fields[4];
    string actors = fields[5];
    int year = stoi(fields[6]);
    int runtime = stoi(fields[7]);
    float rating = stof(fields[8]);
    int votes = stoi(fields[9]);
    float revenue = stof(fields[10]);
    int metascore = stoi(fields[11]);

    // Create a new MovieNode object with the parsed fields
    MovieNode* movie = new MovieNode(rank, title, genre, description, director, actors, year, runtime, rating, votes, revenue, metascore);
    return movie;
}

/**
* Attempts to open a file contianing all of the movies.
* If succeeded, then it will parse the file and store it accordingly in each list.
* @param string, MovieHashTable, DirectorSkipList
* @return void
*/
void readMovieCSV(string filename,  MovieHashTable &movieTable, DirectorSkipList &directorList) {
    ifstream file(filename);
    bool flag = true;
    if (file.is_open()) {
        string temp;
        getline(file, temp);
        while (!file.eof()) {
            temp.clear();
            getline(file, temp);
            MovieNode* temp_node = parseMovieLine(temp);
            if (temp_node) {
                movieTable.insert(temp_node->title, temp_node);
                directorList.insert(temp_node->director, temp_node);
            }
        }
    } else cout << "File not found :(" << endl;
    return;
}

/**
* Just displays the menu selection.
* @param void
* @return void
*/
void display_menu() {
    cout << "Please select an option:\n"
        << "1. Find the director of a movie\n"
        << "2. Find the number of movies by a director\n"
        << "3. Find the description of a movie\n"
        << "4. List the movies by a director\n"
        << "5. Quit\n\n"
        << "Enter an Option: ";
        return;
}
