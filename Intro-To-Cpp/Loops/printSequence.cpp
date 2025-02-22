#include <iostream>
#include <cmath>

int main() {
    int iterator = 0;
    int iterator2 = 0;
    int num;
    while (iterator == 0) {
        std::cout << "Enter a value between 1 and 1000:" << std::endl;
        std::cin >> num;
        if ((num <= 1) || (num >= 1000)) {
            std::cout << "Invalid input." << std::endl;
        } else {
            std::cout << num << std::endl;
            ++iterator;
        }
    }
    while (iterator2 == 0) {
        if (num == 1) {
            //std::cout << num << std::endl;
            ++iterator2;
        } else if ((num % 2) == 0) {
            num /= 2;
            std::cout << num << std::endl;
        } else {
            num = (int) ((3 * num) + 1);
            std::cout << num << std::endl;
        }
    }
    return 0;
}