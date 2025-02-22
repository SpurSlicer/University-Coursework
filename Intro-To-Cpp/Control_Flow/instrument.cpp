#include <iostream>

int main() {
    int category = 0, instrument = 0, price = 0;
    std::cout << "Select a category: (1)Brass (2)Woodwind (3)Percussion" << std::endl;
    std::cin >> category;
    switch (category) {
        case 1 : //tests all instruments for category 1
            std::cout << "Select an instrument: (1)Trumpet (2)Trombone" << std::endl;
            std::cin >> instrument;
            switch (instrument) {
                case 1 :
                    std::cout << "Your instrument will be $350." << std::endl;
                    break;
                case 2 :
                    std::cout << "Your instrument will be $400." << std::endl;
                    break;
                default :
                    std::cout << "Please enter a valid input." << std::endl;
                    break;
            }
            break;
        case 2 : //tests all instruments for category 2
            std::cout << "Select an instrument: (1)Flute (2)Saxophone" << std::endl;
            std::cin >> instrument;
            switch (instrument) {
                case 1 :
                    std::cout << "Your instrument will be $325." << std::endl;
                    break;
                case 2 :
                    std::cout << "Your instrument will be $425." << std::endl;
                    break;
                default :
                    std::cout << "Please enter a valid input." << std::endl;
                    break;
            }
            break;
        case 3 : //tests all instruments for category 3
            std::cout << "Select an instrument: (1)Snare Drum (2)Cymbals" << std::endl;
            std::cin >> instrument;
            switch (instrument) {
                case 1 :
                    std::cout << "Your instrument will be $275." << std::endl;
                    break;
                case 2 :
                    std::cout << "Your instrument will be $200." << std::endl;
                    break;
                default :
                    std::cout << "Please enter a valid input." << std::endl;
                    break;
            }
            break;
        default : //handles category number errors
            std::cout << "Please enter a valid input." << std::endl;
            break;

    }
}