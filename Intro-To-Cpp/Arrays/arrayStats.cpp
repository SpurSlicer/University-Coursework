#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
/*Algorithm
* creates the original variable as the first item in the array
* iterates through the array and compares each element
* returns the smallest element found in the conditional
*/
double min(double a[], int a_size) {
    double ans = a[0];
    for (int i = 1; i < a_size; ++i) {
        if (ans > a[i]) {
            ans = a[i];
        }
    }
    return ans;
}
/*Algorithm
* creates the original variable as the first item in the array
* iterates through the array and adds each element
* returns the sum store in the ans variable
*/
double sum(double a[], int a_size) {
    double ans = 0;
    for (int i = 0; i < a_size; ++i) {
        ans += a[i];
    }
    return ans;
}
/*Algorithm
* creates an original variable as the answer
* adds every element in the array to the answer variable
* returns the answer variable divided by the array size. Since the array size is an int, it is casted as a double
*/
double average(double a[], int a_size) {
    double ans = 0;
    for (int i = 0; i < a_size; ++i) {
        ans += a[i];
    }
    return (double) ans / a_size;
}

int main() {
    double arr[] = {1.24, 5.68, 3.456};
    int arr_size = 3;
    cout << "Min: " << fixed << setprecision(3)<< min(arr, arr_size) << endl;
    //tests the minimum value. Should return 1.240
    cout << "Sum: " << fixed << setprecision(3) << sum(arr, arr_size) << endl;
    //tests the sum value. It should return 10.376
    cout << "Avg: " << fixed << setprecision(3) << average(arr, arr_size) << endl;
    //tests the average value. It should return 3.459
}
