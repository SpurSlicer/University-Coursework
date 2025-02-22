//Current error: shitty files won't open. Look up how to fix it or kys
#include <iostream>
#include <fstream>
#include "../code/fundamentals.hpp"
#include <sstream>
#include <string>

using namespace std;
using std::cout;

int main(int argc, char* argv[]) {
    // TODO
    if(argc <= 1) {
        cout << "Too few args!" << endl;
        exit(0);
    }
    struct stockInfo info_arr[argc-1];
    for (int i = 1; i < 2; ++i) {
        string file_name = argv[i];
        //General file decs
        ifstream file;
        ofstream file_o (argv[2]);
        ofstream &file_out = file_o; //creates referecee uwu
        string buffer = "", buffer2 = "";
        stringstream ss;
        buffer.clear();
        buffer2.clear();
        ss.clear();
        int iter = 0;
        double average = 0;
        //---
        file.open(file_name);
        if (file.is_open()) {
            while(getline(file, buffer)) {
                iter = 0;
                average = 0;
                ss.clear();
                ss << buffer;
                //cout << ss.str() << endl;
                while(getline(ss, buffer2, ',')) {
                    //cout << buffer2 << endl;
                    if(iter == 0) {
                        info_arr[i-1].company_name =  buffer2;
                    } else {
                        average += stod(buffer2);
                        info_arr[i-1].stock_prices_arr[iter-1] = stod(buffer2);
                    }
                    ++iter;
                }
                info_arr[i-1].average = average/static_cast<double>((iter-1));
                displaySortedStocks(info_arr[i-1], file_out);
            }
        } else {
            //cout << "File failed to open." << endl;
            exit(0);
        }
    }

    return 0;
}
