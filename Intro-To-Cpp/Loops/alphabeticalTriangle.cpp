#include <iostream>
#include <string>

int main() {
    int height;
    int a = 'a'; //Char kept overflowing, so I used an int instead
    //Testing whether the input is valid


    std::cout << "Enter the height:" << std::endl;
    std::cin >> height;
    if (height <= 0) {
        std::cout << "Invalid input." << std::endl;
        return 0;
    }

    //Prints the triangle
    for (int i = 1; i <= height; i++) {
        int tempLen = (2 * i) - 1;
        for (int j = 0; j < tempLen; j++) {
            int tempChar = a + j;
            while (tempChar > 122) {
                tempChar -= 26;
            }
            std::cout << static_cast<char>(tempChar); //converts to and prints char
        }
        a += tempLen;
        std::cout << std::endl;
    }
    return 0;
}