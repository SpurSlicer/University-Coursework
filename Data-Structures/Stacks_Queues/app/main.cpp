#include<iostream>
#include <fstream>
#include<cmath>
#include<iomanip>
#include "../code/MessageDecoder.hpp"

using namespace std;


int main(int argc, char* argv[])
{
   if (argc < 2) {
        cout << "Usage: ./run_app <inputfilename>" << endl;
        return 0;
    } else {
        ifstream fin(argv[1]);
        if (fin.fail()) {
          cout << "Error: Could not open file." << endl;
          return 0;
        }
        string buffer;
        getline(fin, buffer);
        MessageDecoder md;
        md.generate_operator_queue(buffer);
        string postfix = md.generate_postfix(buffer);
        int answer = md.evaluate_postfix(postfix);
        cout << "Postfix Notation::" << postfix << endl;
        cout << "Final Answer::" << answer << endl;
    }
    
  return 0;
}