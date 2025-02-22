#include <iostream>

int i = 1;
int qn = 0;

int main() {
    while(i ==  1) {
    std::cout << "Please enter in a question number: ";
    std::cin >> qn;
        switch (qn) {
            case 1: {
                int s = 0, h = 0;
                std::cout << "What is the length of the base of the carton in inches? ";
                std::cin >> s;
                std::cout << "What is the hieght of the carton in inches? ";
                std::cin >> h;
                double a = h * s;
                std::cout << "The carton has a volume of " << a * 0.55 << " ounces.";
                --i;
                break;
            }
            case 2: {   
                int d = 0;
                std::cout << "How many days in the future would you like a prediction for? ";
                std::cin >> d;
                std::cout << "Breckenridge will have " 
                    << (10 * d) - (5 * d) + 25
                    << " inches, Vail will have "
                    << (14 * d) - (2 * d) + 28
                    << " inches, and Copper Mountain will have "  
                    << (5 * d) - (3 * d) + 40
                    << " inches." << std::endl;
                    --i;
                    break;
                }
            case 3: {
                int min = 0;
                int pet = 0;
                int pay = 0;
                std::cout << "What is the minimum square footage you'd like? ";
                std::cin >> min;
                std::cout << "How many pets do you have?";
                std::cin >> pet;
                std::cout << "What is the maximum monthly rent you'd pay?";
                std::cin >> pay;
                if (min == 600) {
                    if (pet >= 1 || pay == 1400) {
                        std::cout << "Then you'll love Appartment A!";
                    } 
                } else if (min == 800) {
                    if (pet == 0 || pay == 1600) {
                        std::cout << "Then you'll love Appartment B!";
                    }
                } else if (min == 1000) {
                    if (pet >= 1 || pay == 1800) {
                        std::cout << "then you'll love Appartment C!";
                    }
                } else {
                    std::cout << "No matches, sorry!";
                }
                --i;
                break;
            }
            //this case is broken
            //this case isn't accounting for the question 4B
            case 4: { 
                int ammt = 0;
                std::cout << "How much did you invest?";
                std::cin >> ammt;
                int ammtHalf = ammt / 2;
                std::cout << "It will take you "
                    << ammtHalf / 100
                    << " months and "
                    << ammtHalf % 100 
                    << " days to lose half of your money";
                --i;
                break;
            }
            case 5: {
                std::cout << "The two compile times here are the enl and the missing "
                    << "semi colon in line 5. \n"
                    << "If Punith wants to fix this, they should use this instead:\n\n"
                    << "#include <iostream>\nusing namespace std;\n"
                    << "int main() {\n"
                    << "\tcout << \"hello 1300\" << endl;\n"
                    << "\treturn 0;\n"
                    << "}" << std::endl;
                --i;
                break;
            }    
            default:
                std::cout << "Invalid number! \n";
        }
    }
    return 0;
}