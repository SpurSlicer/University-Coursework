#include <iostream>
#include <iomanip> // std::setprecision

int main()
{
    double sqBase = 0;
    double height = 0;
    double ansOunces = 0;
    std::cout << "What is the side length of the base of the carton in inches?" << std::endl;
    std::cin >> sqBase;
    std::cout << "What is the height of the carton in inches? " << std::endl;
    std::cin >> height;
    ansOunces = (sqBase * sqBase * height * 0.55); //calculates volume and converts it to ounces

    std::cout << "The carton has a volume of " 
        << std::fixed
        << std::setprecision(1) 
        << ansOunces 
        << " ounces."
        << std::endl;
    return 0;
}