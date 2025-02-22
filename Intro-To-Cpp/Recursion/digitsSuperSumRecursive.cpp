#include <iostream>
#include <cassert>
using namespace std;
/*
ADD: this recursive function adds each digit of a number until there are
no more digits remaining. It then returns this sum.
*/
int add(int n) {
    if (n == 0) {
        return 0;
    } else {
        return ((n % 10) + add(n / 10));
    }
}
/*
DIGITSSUPERSUMRECURSIVE: this recursive function calls add until it's input
is less than 10. It then returns that sum.
*/
int digitsSuperSumRecursive(int n) {
    n = add(n);
    if (n > 9) {
        return digitsSuperSumRecursive(n);
    } else {
        return n;
    }
}

int main() {
    //test case for 1 digit number
    assert(digitsSuperSumRecursive(1) == 1);
    //test case for basic 2 digit number 
    assert(digitsSuperSumRecursive(12) == 3);
    //test case for recursion repeated more than once
    assert(digitsSuperSumRecursive(123456789) == 9);
    //test case for recursion repeated edge case
    assert(digitsSuperSumRecursive(999999999) == 9);
    //test case for 0s
    assert(digitsSuperSumRecursive(10010010) == 3);
    //test case for 0s with recursion
    assert(digitsSuperSumRecursive(900900) == 9);
    //testing 0
    assert(digitsSuperSumRecursive(0) == 0);
    return 0;
}