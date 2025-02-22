#include <iostream>

int main() {
    int department = 0, _class = 0, section = 0;
    std::cout << "Select a department: (1)Computer Science (2)Math (3)Science" << std::endl;
    std::cin >> department;
    switch (department) { //tests all possible departments (1-3)
        case 1 : //tests all possible classes for department 1
            std::cout << "Select a class: (1)Starting Computing (2)Data Structures (3)Algorithms" << std::endl;
            std::cin >> _class;

            switch (_class) { 
                case 1 : //tests class possibilities for department 1
                    std::cout << "Select a section: (1)Section 100 (2)Section 200" << std::endl;
                    std::cin >> section;

                    switch (section) { 
                        case 1 : //tests sections for class 1 deparmtent 1
                            std::cout << "You've been enrolled in Section 100 of Starting Computing!" << std::endl; 
                            break;
                        case 2 :
                            std::cout << "You've been enrolled in Section 200 of Starting Computing!" << std::endl; 
                            break;
                        default :
                            std::cout << "Please enter a valid input." << std::endl;
                            break;
                    }
                    break;
                case 2 : //tests sections for class 2 department 1
                    std::cout << "Select a section: (1)Section 101 (2)Section 201" << std::endl;
                    std::cin >> section;

                    switch (section) {
                        case 1 :
                            std::cout << "You've been enrolled in Section 101 of Data Structures!" << std::endl; 
                            break;
                        case 2 :
                            std::cout << "You've been enrolled in Section 201 of Data Structures!" << std::endl; 
                            break;
                        default :
                            std::cout << "Please enter a valid input." << std::endl;
                            break;
                    }
                    break;
                case 3 : //tests sections for class 3 department 1
                    std::cout << "Select a section: (1)Section 102 (2)Section 202" << std::endl;
                    std::cin >> section;

                    switch (section) {
                        case 1 :
                            std::cout << "You've been enrolled in Section 102 of Algorithms!" << std::endl; 
                            break;
                        case 2 :
                            std::cout << "You've been enrolled in Section 202 of Algorithms!" << std::endl; 
                            break;
                        default :
                            std::cout << "Please enter a valid input." << std::endl;
                            break;
                    }
                    break;
                default :
                    std::cout << "Please enter a valid input." << std::endl;
                    break;
            }
            break;
        case 2 : //tests all possible classes for department 2
            std::cout << "Select a class: (1)Calculus 1 (2)Calculus 2 (3)Linear Algebra" << std::endl;
            std::cin >> _class;

            switch (_class) {
                case 1 : //tests sections for class 1 department 2
                    std::cout << "Select a section: (1)Section 400 (2)Section 500" << std::endl;
                    std::cin >> section;

                    switch (section) {
                        case 1 :
                            std::cout << "You've been enrolled in Section 400 of Calculus 1!" << std::endl; 
                            break;
                        case 2 :
                            std::cout << "You've been enrolled in Section 500 of Calculus 1!" << std::endl; 
                            break;
                        default :
                            std::cout << "Please enter a valid input." << std::endl;
                            break;
                    }
                    break;
                case 2 : //tests sections for class 2 department 2
                    std::cout << "Select a section: (1)Section 401 (2)Section 501" << std::endl;
                    std::cin >> section;

                    switch (section) {
                        case 1 :
                            std::cout << "You've been enrolled in Section 401 of Calculus 2!" << std::endl; 
                            break;
                        case 2 :
                            std::cout << "You've been enrolled in Section 501 of Calculus 2!" << std::endl; 
                            break;
                        default :
                            std::cout << "Please enter a valid input." << std::endl;
                            break;
                    }
                    break;
                case 3 : //tests sections for class 3 department 2
                    std::cout << "Select a section: (1)Section 402 (2)Section 502" << std::endl;
                    std::cin >> section;

                    switch (section) {
                        case 1 :
                            std::cout << "You've been enrolled in Section 402 of Linear Algebra!" << std::endl; 
                            break;
                        case 2 :
                            std::cout << "You've been enrolled in Section 502 of Linear Algebra!" << std::endl; 
                            break;
                        default :
                            std::cout << "Please enter a valid input." << std::endl;
                            break;
                    }
                    break;
                default :
                    std::cout << "Please enter a valid input." << std::endl;
                    break;
            }
            break;
        case 3 : //tests all classes for department 3
            std::cout << "Select a class: (1)General Chemistry 1 (2)Physics 1 " << std::endl;
            std::cin >> _class;

            switch (_class) {
                case 1 : //tests sections for class 1 department 3
                    std::cout << "Select a section: (1)Section 700 (2)Section 800" << std::endl;
                    std::cin >> section;

                    switch (section) {
                        case 1 :
                            std::cout << "You've been enrolled in Section 700 of General Chemistry 1!" << std::endl; 
                            break;
                        case 2 :
                            std::cout << "You've been enrolled in Section 800 of General Chemistry 1!" << std::endl; 
                            break;
                        default :
                            std::cout << "Please enter a valid input." << std::endl;
                            break;
                    }
                    break;
                case 2 : //tests sections for class 2 department 3
                    std::cout << "Select a section: (1)Section 701 (2)Section 801" << std::endl;
                    std::cin >> section;

                    switch (section) {
                        case 1 :
                            std::cout << "You've been enrolled in Section 701 of Physics 1!" << std::endl; 
                            break;
                        case 2 :
                            std::cout << "You've been enrolled in Section 801 of Physics 1!" << std::endl; 
                            break;
                        default :
                            std::cout << "Please enter a valid input." << std::endl;
                            break;
                    }
                    break;
                default : //handles class number errors
                    std::cout << "Please enter a valid input." << std::endl;
                    break;
            }
            break;
        default : //handles department number errors
            std::cout << "Please enter a valid input." << std::endl;
            break;
    }
    return 0;
}