#include <vector>
#include <iostream>
using namespace std;
/* ALGORITHM
It starts by getting a vector, starting index, and ending index
It then checks to make sure the indices are valid. If they are, it returns -1
It then checks to make sure that the indices are valid for the given size. If not, it returns -2.
If every test passes, then it adds every element in the vector for all indices given.
Finally, it returns the sum.
*/
int sumElements(vector<int> vec, int start_index, int end_index) {
    int sum = 0, size = vec.size();
    if (start_index >= end_index) {
        return -1;
    } else if ((end_index > size) || (start_index < 0) || (end_index - start_index >= size)) {
        return -2;
    }
    while (start_index <= end_index) {
        sum += vec.at(start_index);
        ++start_index;
    }
    return sum;
}
int main() {
    vector<int> empty;
    vector<int> valid = {1,2,3,-1,-2,-3,6};
    //TEST 1: empty size vector
    cout << sumElements(empty, 0, 0) << endl; //should return -1
    //TEST 2: Invalid indices
    cout << sumElements(valid, 0, 7) << endl; // should return -2
    //TEST 3: valid indices w/ edge cases
    cout << sumElements(valid, 0, 6); // should return 6
    //Test 4: valid indices
    cout << sumElements(valid, 1, 3); // should return 4
    return 0;
}
