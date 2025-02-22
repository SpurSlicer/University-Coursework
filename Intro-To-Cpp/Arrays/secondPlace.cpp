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
/*Algorithm
* checks to make sure that the number of insertions will fit inside of the array
* returns the number of elements if this happens
* travles through the array
* if the string is equal to the string to find, then do an insertion
* return the new number of elements
*/
int secondPlace(string input_strings[], string string_to_insert, string string_to_find, int num_elements, int arr_size, int count) {
    if ((count + num_elements) > arr_size) {
        return num_elements;
    }
    for (int i = 0; i < arr_size; ++i) {
        if (input_strings[i] == string_to_find) {
            insertAfter(input_strings, num_elements, arr_size, i, string_to_insert);
        }
    }
    return num_elements + count;
}

int main() {
    int size = 13;
    string inputStrings[13] = {"chansey", "meowth", "chansey", "chansey", "chansey", "raichu", "ponyta", "chansey"};
    int numElements = 8;
    string stringToInsert = "gyarados";
    string stringToFind = "chansey";
    int count = 5;
    assert(secondPlace(inputStrings, stringToInsert, stringToFind, numElements, size, count) == 13);
    cout << "Function returned value: " << numElements << endl;
    for (int i = 0; i < size; ++i) {
        cout << inputStrings[i] << endl;
    }
    //should return 13 and the following list:
    /*
    chansey
    gyarados
    meowth
    chansey
    gyarados
    chansey
    gyarados
    chansey
    gyarados
    raichu
    ponyta
    chansey
    gyarados
    */
}