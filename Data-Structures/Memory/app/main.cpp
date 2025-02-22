#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "../code/array_double.hpp"

using namespace std;
/* 
1.  The name of the txt file to be read and analyzed (e.g., cases.txt)
2.  The location (e.g., Boulder)
3.  The variant of the virus (e.g., Delta)
4.  The lower limit (included) of the age group (e.g., 20)
5.  The upper limit (included) of the age group (e.g., 40)
*/

int main(int argc, char* argv[])
{
    if (argc != 6) {
        cout << "Usage: ./run_app <inputfilename> <Query_Location> <Query_Variant> <Query_Start_Age> <Query_End_Age>" << endl;
        exit(0);
    } 
    //---------------------------------------
    /*Organizes Parameters*/
    string args[4] = {argv[2], argv[3], argv[4], argv[5]};
    /*---*/

    /*Creates file objects for later use*/
    ifstream file_in(argv[1]);
    /*---*/

    /*Creating the DAA*/
    int size = 10;
    int recordIndx = 1;
    int doublingCounter = 0;
    struct CovidCase* arr1 = new struct CovidCase[size];
    /*---*/
    //---------------------------------------
    parseFile(file_in, args, arr1, size, recordIndx, doublingCounter);
    cout << "Array doubled: " << doublingCounter << endl
         << "Total number of cases returned after the query: " << --recordIndx << endl;
    printQueriedCases(arr1, recordIndx);
    delete[] arr1;
    return 0;
}