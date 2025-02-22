#include <iostream>
#include <string>

int main() {
    std::string sequence;
    std::string substr;
    int sequenceLen;
    int substrLen;
    int occurances;

    std::cout << "Enter the DNA Sequence:" << std::endl;
    std::cin >> sequence;
    sequenceLen = sequence.length();

    //tests if the sequence is valid
    for (int i = 0; i < sequenceLen; i++) {
        if (((sequence[i]!= 'A') && (sequence[i]!= 'C')) && ((sequence[i]!= 'G') && (sequence[i]!= 'T'))) {
            std::cout << "This is not a valid DNA sequence." << std::endl;
            return 0;
        } 
    }


    std::cout << "Enter the DNA fragment to be searched:" << std::endl;
    std::cin >> substr;
    substrLen = substr.length();

    //tests if the substr is valid
    for (int i = 0; i < substrLen; i++) {
        if (((substr[i]!= 'A') && (substr[i]!= 'C')) && ((substr[i]!= 'G') && (substr[i]!= 'T'))) {
            std::cout << "This is not a valid DNA sequence" << std::endl;
            return 0;
        } 
    }
    //checks each substring of sequence
    for (int i = 0;  i <= (sequenceLen - substrLen); i++) {
        std::string temp = sequence.substr(i,(substrLen));
        //std::cout << temp << std::endl; (debug)
        if (temp == substr) {
            ++occurances;
        }
    }
    //gives solution 
    std::cout << "Number of occurrences: " << occurances << std::endl;
    return 0;

}