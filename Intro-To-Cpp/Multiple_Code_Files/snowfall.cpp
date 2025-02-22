#include <iostream>

int main() 
{
    int days = 0;
    std::cout << "How many days in the future would you like a prediction for?" << std::endl;
    std::cin >> days;
    if (days < 0) //checks to make sure days is positive
    {
        std::cout << "Please enter a positive number!" << std::endl;
        return 0;
    }
    std::cout << "Breckenridge will have "
        << ((days * 10)-(days * 5) + 25) << " inches, Vail will have "
        << ((days * 14)-(days * 2) + 28) << " inches, and Copper Mountain will have "
        << ((days * 5)-(days * 3) + 40) << " inches." << std::endl;
    return 0;
}