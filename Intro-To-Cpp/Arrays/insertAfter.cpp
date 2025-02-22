#include <iostream>
#include <string>

using namespace std;
/*Algorithm
* makes sure that the index is valid and that the input_strings array isn't empty at that index
* travels through the through the array and inserts an element at the specified index
* it then pushes back all of th eother elements
* completes the pushback process
* returns true when finished
*/
bool insertAfter(string input_strings[], int num_elements, int arr_size, int index, string string_to_insert) {
    if (((index >= arr_size - 1) || (input_strings[index]) == "")) {
        return false;
    }
    for(int i = arr_size - 1; i > index; --i) {
        input_strings[i] = input_strings[i-1]; 
    }
    input_strings[index+1] = string_to_insert;
    return true;
}

int main() {
    int size = 5;
    string input_strings[size] = {"caterpie", "eevee"};
    int num_elements = 2;
    int index = 0;
    string string_to_insert = "bulbasaur";
    bool result = insertAfter(input_strings, num_elements, size, index, string_to_insert);
    cout << "Function returned value: "<< result << endl;
    for(int i = 0; i < size; i++)
    {
        cout << input_strings[i] << endl;
    }
    //should return 1 and the following list:
    /*
    caterpie
    bulbasaur
    eevee
    */
}