#include "Aquarium.h"
/* ALGORITHM
* This is just my simple split function.
* It operates how it has this entire semester. 
*/
int split(std::string input_string, char separator, std::string arr[], int arr_size) {
    std::string temp = "";
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

/* ALGORITHM
* Get's a given string
* Initializes a temporary string
* Goes through every character of the inputted string and assigns the character to lower
* It then adds this onto the temporary string
* It then returns this string
*/
std::string to_lower(std::string s) {
    std::string temp = "";
    for (int i = 0; i < s.length(); ++i) {
        temp += std::tolower(s[i]);
    }
    return temp;
}

/* ALGORITHM
* Checks if the gallons used is less than or equal to the tank size
*   returns true if this is the case
* Returns false if otherwise
*/
bool Aquarium::checker(int n) {
    if ((gallons_used + n) <= tank_size_gallons) {
        return true;
    }
    return false;
}

/* PARAMETERIZED CONSTRUCTOR
* Just initializes the aquarist name and gallons used for the Aquarium object class
*/
Aquarium::Aquarium(std::string n) {
    aquarist_name = n;
    gallons_used = 0;
}

//Just returns the data member of auqarist name
std::string Aquarium::getAquaristName() {
    return aquarist_name;
}

//Returns the gallons used
int Aquarium::getGallonsUsed() {
    return gallons_used;
}

/* ALGORITHM
* Starts by creating a reading file stream object and scoped array
* It then attempts to open the file
* If the file opens, then it continues
* If not, it returns false
* It then repeats the following until the end of the file is reached
*   It then gets each sequential line from the file.
*   It splits it, creates a fish, and assigns objects to each fish part
* It then adds this to the fish vector, closes the file, and returns true
*/
bool Aquarium::loadFish(std::string s) {
    std::ifstream file;
    std::string arr[2];
    file.open(s);
    if (!file.fail()) {
        while (!file.eof()) {
            std::string line = "";
            std::getline(file, line);
            if (line != "") {
                split(line,  ',', arr, 2);
                Fish f;
                f.name = arr[0];
                f.gallons_required = stoi(arr[1]);
                available_fish.push_back(f);
            }
        }
        file.close();
        return true;
    }
    return false;
}

/* ALGORITHM
* While the avail fish vector is empty, print out a message
* If it isn't empty, cout the fish in the avail aquarium
*/
void Aquarium::displayAvailableFish() {
    if (available_fish.empty()) {
        std::cout << "There are no fish available." << std::endl;
    } else {
        std::cout << "Fish available to add to aquarium:" << std::endl;
        for (int i = 0; i < available_fish.size(); ++i) { //cycles through and prints each fish
            std::cout << available_fish.at(i).name << " - " << available_fish.at(i).gallons_required << std::endl;
        }
    }
    return;
}

/* ALGORITHM
* Begins a loop to cycle through the avail fish vector
*   Checks if there are any differences between the input string and the fish name at vector slot i
*    If so: Check if the tank has space
*        If it does, then add the fish to the selected vector, add the gallons required, and remove the fish from the avail vector
*        Return 1
*    If not: return 0
*   Return 1
*/
int Aquarium::addFish(std::string s) {
    for (int i = 0; i < available_fish.size(); ++i) {
        if (to_lower(available_fish.at(i).name).std::string::compare(to_lower(s)) == 0) {
            if (checker(available_fish.at(i).gallons_required)) {
                selected_fish.push_back(available_fish.at(i));
                gallons_used += available_fish.at(i).gallons_required;
                available_fish.erase(available_fish.begin() + i);
                return 1;
            } else {
                return 0;
            }
        }
    }
    return -1;
}
/* ALGORITHM
* Same as the addFish function but the oposite
* Returns true if successful
* Returns false if not
*/
bool Aquarium::removeFish(std::string s) {
    for (int i = 0; i < selected_fish.size(); ++i) {
        if (to_lower(selected_fish.at(i).name).compare(to_lower(s)) == 0) {
            available_fish.push_back(selected_fish.at(i));
            selected_fish.erase(selected_fish.begin() + i);
            gallons_used = 0;
            for (int i = 0; i < selected_fish.size(); ++i) {
                gallons_used += selected_fish.at(i).gallons_required;
            }
            return true;
        }
    }
    return false;
}

/* ALGORITHM
* Opens the file
* While the file is open, check if selected fish vector is empty
*   If the vector is empty, say something
* Else, then print out the aquarist and aquarium name and add the fishes to a file
* It then resets the selected_fish vector and the gallons_used attribute
*/
bool Aquarium::writeAquariumContents(std::string s) {
    std::ofstream file;
    file.open(s);
    if (!file.fail()) {
        if (selected_fish.empty()) {
            file << "There are no fish in " << aquarist_name << "'s Aquarium." << std::endl;
        } else {
            file << aquarist_name << "'s Aquarium (" << gallons_used << " of 12 gallons of water used):" << std::endl;
            for (int i = 0; i < selected_fish.size(); ++i) {
                file << selected_fish.at(i).name << " - " << std::to_string(selected_fish.at(i).gallons_required) << std::endl;
            }
        }
        selected_fish.erase(selected_fish.begin(), selected_fish.end());
        gallons_used = 0;
        return true;
    } else {
        return false;
    }
}