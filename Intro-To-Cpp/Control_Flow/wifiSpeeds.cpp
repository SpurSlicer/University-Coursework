#include <iostream>

int main() {
    double speed1 = 0, speed2 = 0, speed3 = 0;
    std::cout << "Enter wifi speeds over the last 3 classes:" << std::endl;
    std::cin >> speed1 >> speed2 >> speed3;
    //Makes sure all values are valid
    if ((speed1 < 0) || (speed2 < 0) || (speed3 < 0)) {
        std::cout << "Please enter a valid input." << std::endl;
        return 0;
    }
    //Tests if speed is dec, then inc, then other
    if ((speed1 > speed2) && (speed2 > speed3)) {
        std::cout << "The wifi is getting slower!" << std::endl;
        return 0;
    } else if ((speed1 < speed2) && (speed2 < speed3)) {
        std::cout << "The wifi is getting faster!" << std::endl;
        return 0;
    } else {
        std::cout << "The wifi speed is changing unpredictably." << std::endl;
        return 0;
    }
}