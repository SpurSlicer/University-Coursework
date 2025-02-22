#include <iostream>
#include <string>

using namespace std;

int main() {
    int distance[10];
    string cities[5] = {"Boulder", "NYC", "LA", "Chicago", "Houston"};
    int sequence [100];
    char letters[55];
    //creates and prints everyting in array 1
    for (int i = 0; i < 10; ++i) {
        distance[i] = i+5;
        cout << distance[i] << endl;
    }
    //prints everything in array 2
    for (int i = 0; i < 5; ++i) {
        cout << cities[i] << endl;
    }
    //creates and prints everything in array 3
    for (int i = 0; i < 100; ++i) {
        sequence[i] = 6 * (i+1);
        cout << sequence[i] << endl;
    }
    //creates and prints every letter in the alphabet using ascii numbers in/for array 4
    for (int i = 0; i < 26; ++i) {
            letters[i] = i + 65;
            cout << letters[i] << endl;
            letters[(2*i)-1] = i + 97;
            cout << letters[(2*i)-1] << endl;
    }

}