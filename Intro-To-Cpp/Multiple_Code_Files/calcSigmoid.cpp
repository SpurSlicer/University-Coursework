#include <iostream>
#include <cmath>

int main()
{ 
    double x = 0;
    double sigmoid = 0;
    std::cout << "Enter a value for x:" << std::endl;
    std::cin >> x;
    sigmoid = (1 / (1 + exp(-x))); //calculates the sigmoid of x
    std::cout << "The sigmoid for x=" << x << " is " << sigmoid << std::endl;
    return 0;
}