#include <iostream>

int main() {
    char size;
    int toppingsNum = 0;
    double price = 0;
    int &num = toppingsNum; //Used a ref here because toppingsNum is a long var name
    std::cout << "What size pizza would you like to order?" << std::endl;
    std::cin >> size;
    //Makes sure size is valid
    if ((size != 'S') && (size != 'M') && (size != 'L')) {
        std::cout << "Please enter a valid input." << std::endl;
        return 0;
    }
    std::cout << "How many toppings do you want?" << std::endl;
    std::cin >> num;
    //Makes sure toppings is valid
    if (num < 0) {
        std::cout << "Please enter a valid input." << std::endl;
        return 0;
    }
    //Tests pizza cases
    switch (size) {
        case 'S' : //small test
            price += 4.99;
            price += (num * 0.75);
            std::cout << "Your total is $" << price << std::endl;
            break;
        case 'M' : //medium test
            price += 5.99;
            price += (num * 1.50);
            std::cout << "Your total is $" << price << std::endl;
            break;
        case 'L' : //large test
            price += 6.99;
            price += (num * 2.25);
            std::cout << "Your total is $" << price << std::endl;
            break;
    }
    return 0;
}