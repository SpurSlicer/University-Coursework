#include "array_double.hpp"
#include <sstream>
#define MAX_INT 2147483647
void parseFile(ifstream& input,string queryParams[], CovidCase *&cases, int &arrCapacity,  int &recordIdx, int &doublingCounter){
    if (input.is_open()) {
        int line_num = 1, ss_iter = 0;
        string line = "", buffer = "";
        stringstream ss;
        while(!input.eof()){
            getline(input, line);
            ss << line;
            CovidCase buffer_cc;
            while (getline(ss, buffer, ',')) {
                switch (ss_iter) {
                    case 0:
                        buffer_cc.name = buffer;
                        break;
                    case 1:
                        buffer_cc.variant = buffer;
                        break;
                    case 2:
                        buffer_cc.location = buffer;
                        break;
                    case 3:
                        buffer_cc.age = stoi(buffer);
                        break;
                    default:
                        cout << "something went wrong :sobbies:" << endl;
                        exit(0);
                }
                if (ss_iter == 3) {
                    break;
                } else {
                    ++ss_iter;
                }
            }
            if (isCaseQueried(buffer_cc, queryParams[0], queryParams[1], stoi(queryParams[2]), stoi(queryParams[3]))) {
                if (recordIdx == arrCapacity) {
                    int* arrSizePtr = &arrCapacity;
                    resizeArr(cases, arrSizePtr);
                    ++doublingCounter;
                }
                *(cases+recordIdx) = buffer_cc;
                ++recordIdx;
            }
            ss.clear();
            line = "";
            buffer = "";
            ss_iter = 0;
            ++line_num;
        }
    } else {
        cout << "something went wrong :sobbies:" << endl;
    }  
    sortCases(cases, recordIdx);
    return;
}

bool isCaseQueried(CovidCase covidCase, string queryLocation, string queryVariant, int startAge, int endAge) {
    if (covidCase.location == queryLocation) {
        if (covidCase.variant == queryVariant) {
            if ((covidCase.age <= endAge) && (covidCase.age >= startAge)) {
                return true;
            }
        }
    }
    return false;
}

void resizeArr(CovidCase *&cases, int *arraySize) {
    int tempCap = *arraySize * 2;
    CovidCase* arr_buff = new CovidCase[tempCap];
    for (int i = 0; i < *arraySize; ++i) {
        *(arr_buff+i) = *(cases+i); 
    }
    *arraySize = tempCap;
    delete[] cases;
    cases = arr_buff;
    return;
}

void addCase(CovidCase *&cases, CovidCase covidCase, int &arrCapacity, int &recordIdx, int &doublingCounter) {
    //remember to implement isCaseQueried somehow
    if (arrCapacity == recordIdx) {
        int* arrSizePtr = &arrCapacity;
        resizeArr(cases, arrSizePtr);
        ++doublingCounter;
    }
    *(cases + recordIdx) = covidCase;
    ++recordIdx;
    return;
}

bool containedIn(CovidCase testingCase, CovidCase testingArr[], const int arrLen) {        
    for (int i = 0; i < arrLen; ++i) {
        if(testingCase.age == testingArr[i].age) {
            if(testingCase.location == testingArr[i].location) {
                if(testingCase.name == testingArr[i].name) {
                    if(testingCase.variant == testingArr[i].variant) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
CovidCase firstChar(CovidCase CC1, CovidCase CC2) {
    int i = 0;
    while (true && (i <= CC1.name.length()) && (i <= CC2.name.length())) {
        char char1 = CC1.name[i], char2 = CC2.name[i];
        if (char1 < char2) {
            return CC1;
        } else if (char1 > char2) {
            return CC2;
        }
        ++i;
    }
    cout << "Something bad happened OwO" << endl;
    exit(0);
}
void sortCases(CovidCase* cases, int length) {
    const int arrLen = length;
    CovidCase arrBuffer[arrLen];
    int iter = 0;
    while (length >= 0) {
        CovidCase leastAge;
        leastAge.age = MAX_INT;
        for (int i = 0; i < arrLen; ++i) {
            if (((cases+i)->age < leastAge.age) && (!containedIn(*(cases+i), arrBuffer, arrLen))) {
                arrBuffer[iter] = *(cases+i);
                leastAge = *(cases+i);
            } else if (((cases+i)->age == leastAge.age) && (!containedIn(*(cases+i), arrBuffer, arrLen))) {
                arrBuffer[iter] = firstChar(*(cases+i), leastAge);
                leastAge = firstChar(*(cases+i), leastAge);
            }
        }
        ++iter;
        --length;
    }
    for (int i = 0; i < arrLen; ++i) {
        *(cases+i) = arrBuffer[i];
    }
    return;
}

void printQueriedCases(CovidCase* cases, int numOfRecords) {
    cout << "Queried Cases\n---------------------------------------" << endl;
    for (int i = 0; i < numOfRecords; ++i) {
        cout << (cases+i)->name << " " << (cases+i)->age << endl;
    }
    return;
}