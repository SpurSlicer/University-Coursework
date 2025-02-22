#include <iostream>

int main() {
    char transpo;
    double budget = 0;
    std::cout << "What is your budget?" << std::endl;
    std::cin >> budget;
    //Tests to see if input is valid
    if (budget < 0) {
        std::cout << "Please enter a valid input." << std::endl;
        return 0;
    }
    //switches through various scenarios that could play out for the problem
    std::cout << "What mode of transportation would you like to take (B, T, or A)?" << std::endl;
    std::cin >> transpo;
    switch(transpo) {
        case 'B' : //Bus tests
            if (budget >= 175.25) {
                std::cout << "Yes, this vacation is within your budget!" << std::endl;
            } else {
                std::cout << "Sorry, this vacation is outside your budget." << std::endl;
            }
            break;
        case 'T' : //Train tests
            if (budget >= 240.66) {
                std::cout << "Yes, this vacation is within your budget!" << std::endl;
            } else {
                std::cout << "Sorry, this vacation is outside your budget." << std::endl;
            }
            break;
        case 'A' : //Airplane tests
            if (budget >= 350.93) {
                std::cout << "Yes, this vacation is within your budget!" << std::endl;
            } else {
                std::cout << "Sorry, this vacation is outside your budget." << std::endl;
            }
            break;
        default : //Makes sure a valid char was entered
            std::cout << "Please enter a valid input." << std::endl;
            break;
    }
    return 0;
}