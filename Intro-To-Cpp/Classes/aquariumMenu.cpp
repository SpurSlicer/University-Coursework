#include "Aquarium.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using std::cin;
using std::cout;
using std::getline;
using std::endl;
using std::string;
int main() {
    string name = "";
    cout << "Welcome to the aquarium manager. Please enter the aquarist's name:" << endl;
    getline(cin, name);
    Aquarium aqua = Aquarium(name);
    int input = 0;
    bool flag = false;
    cout << "--Aquarium Manager--" << endl
        << "1. Load fish" << endl
        << "2. Display available fish" << endl
        << "3. Add a fish" << endl
        << "4. Remove a fish" << endl
        << "5. Save aquarium contents" << endl
        << "6. Exit" << endl;
    while (cin >> input) {
        string name_file = "", name_fish = "";
        if (input == 1) {
            cout << "Please enter a filepath:" << endl;
            cin >> name_file;
            if (aqua.loadFish(name_file)) {
                cout << "Fish loaded successfully." << endl;
            } else {
                cout << "Could not open file. No fish loaded." << endl;
            }
        } if (input == 2) {
            aqua.displayAvailableFish();
        } if (input == 3) {
            cout << "Which fish would you like to add?" << endl;
            getline(cin, name_fish);
            if (aqua.addFish(name_fish) == -1) {
                cout << "Could not find fish: " << name_fish << endl;
            } else if (aqua.addFish(name_fish) == 0) {
                cout << "The aquarium is already at " << aqua.getGallonsUsed() << " gallons and this fish cannot be added." << endl;
            } else {
                cout << "Fish added successfully." << endl;
            }
        } if (input == 4) {
            cout << "Which fish would you like to remove?" << endl;
            getline(cin, name_fish);
            if (aqua.removeFish(name_fish)) {
                cout << "Fish removed successfully." << endl;
            } else {
                cout << name_fish << " not found." << endl;
            }
        } if (input == 5) {
            cout << "Where would you like to save your aquarium?" << endl;
            cin >> name_file;
            if (aqua.writeAquariumContents(name_file)) {
                cout << "Aquarium saved successfully." << endl;
            } else {
                cout << "Could not open file. Aquarium was not saved." << endl;
            }
        } if (input == 6) {
            cout << "Goodbye!" << endl;
            return 0;
        } if ((input < 1) && (input > 6)) {
            cout << "Invalid input. Please enter a number between 1 and 6." << endl;
        }
        cout << "--Aquarium Manager--" << endl
            << "1. Load fish" << endl
            << "2. Display available fish" << endl
            << "3. Add a fish" << endl
            << "4. Remove a fish" << endl
            << "5. Save aquarium contents" << endl
            << "6. Exit" << endl;
    }
}