#include <iostream>
#include <cmath>

int main() {
    //vars for ingredients
    int honeycomb = 0;
    int dandelions = 0;
    int coal = 0;
    int toadstools = 0;
    int mmanap = 0;
    int mhealthp = 0;
    //choice things
    int choice = 0;
    //iteration
    int iter = 0;
    int iter2 = 0;
    int iterh = 0;
    int iterd = 0;
    int iterc = 0;
    int itert = 0;
    while (iter == 0) {
        std::cout << "Select a potion crafting priority:\n" 
            << "1. Minor Mana\n"
            << "2. Minor Healing\n";
        std::cin >> choice;
        if ((choice != 1) && (choice != 2)) {
            std::cout << "Invalid input.\n";
        } else {
            ++iter;
        }
    }
    //honeycomb
    while (iterh == 0) {
        std::cout << "How many Honeycombs do you have?" << std::endl;
        std::cin >> honeycomb;
        if (honeycomb < 0) {
            std::cout << "Invalid input. ";
        } else {
            ++iterh;
        }
    }
    //dandelions
    while (iterd == 0) {
        std::cout << "How many Dandelions do you have?" << std::endl;
        std::cin >> dandelions;
        if (dandelions < 0) {
            std::cout << "Invalid input. ";
        } else {
            ++iterd;
        }
    }
    //coal
    while (iterc == 0) {
        std::cout << "How many Coal do you have?" << std::endl;
        std::cin >> coal;
        if (coal < 0) {
            std::cout << "Invalid input. ";
        } else {
            ++iterc;
        }
    }
    //toadstools
    while (itert == 0) {
        std::cout << "How many Toadstools do you have?" << std::endl;
        std::cin >> toadstools;
        if (toadstools < 0) {
            std::cout << "Invalid input. ";
        } else {
            ++itert;
        }
    }
    //calculates potion amounts
    if (choice == 1) { //if mana is prioritized
        while (iter2 == 0){
            if (((honeycomb >= 5) && (dandelions >= 3)) && (coal >= 1)) {
                honeycomb -= 5;
                dandelions -= 3;
                coal -= 1;
                ++mmanap;
            } else if (((honeycomb >= 5) && (coal >= 2)) && (toadstools >= 3)) {
                honeycomb -= 5;
                coal -= 2;
                toadstools -= 3;
                ++mhealthp;
            } else {
                ++iter2;
            }
        }
    } else { //if health is prioritized
        while (iter2 == 0) {
            if (((honeycomb >= 5) && (coal >= 2)) && (toadstools >= 3)) {
                honeycomb -= 5;
                coal -= 2;
                toadstools -= 3;
                ++mhealthp;
            } else if (((honeycomb >= 5) && (dandelions >= 3)) && (coal >= 1)) {
                honeycomb -= 5;
                dandelions -= 3;
                coal -= 1;
                ++mmanap;
            } else {
                ++iter2;
            }
        }
    }
    if (choice == 1) {
        std::cout << "You can make " << mmanap 
            << " Mana potion(s) and " << mhealthp
            << " Healing potion(s)." << std::endl;
    } else {
        std::cout << "You can make " << mhealthp 
            << " Healing potion(s) and " << mmanap
            << " Mana potion(s)." << std::endl;
    }
    return 0; 
}
