//g++ -std=c++11 code_1/browserHistory.cpp code_1/browserHistory.hpp app_1/main_1.cpp
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "../code_1/browserHistory.hpp"

using namespace std;

void displayMenu();

int main(int argc, char* argv[]) {

    // DO NOT MODIFY THIS.
    BrowserHistory bH;
    if(argc>1) 
    {
        freopen(argv[1],"r",stdin);
    }
    // DO NOT MODIFY ABOVE.

    char option;
    while (true) {
        /* switch statement var declarations*/
        string line4 = "", line5 = "";
        string line = "", line3 = "";
        int line2 = 0;
        string line6 = "";
        WebPage* temp = new WebPage;
        /* --- */
        displayMenu();
start:
        option = getchar();
        switch (option) {
            case '1':
            /*
                cout <<
                "adding: [10]-https://www.github.com/ (HEAD)\n" <<
                "adding: [11]-https://www.wikipedia.org/ (prev: [10])\n" <<
                "adding: [12]-https://brilliant.org/ (prev: [11])\n" <<
                "adding: [13]-https://www.khanacademy.org/ (prev: [12])\n" <<
                "adding: [14]-https://www.numberphile.com/ (prev: [13])\n" <<
                endl; */
                bH.buildBrowserHistory();
                bH.displayHistory();
                break;
            case '2':
                if (bH.isEmpty()) {
                    cout <<
                    "== CURRENT BROWSER HISTORY ==\n" <<
                    "Empty History\n" <<
                    "NULL\n" <<
                    "===" <<
                    endl;
                } else {
                    bH.displayHistory();
                }
                break;
            case '3':
                cout << "Enter the new web page's url:" << endl;
                cin >> line;
                while (true) {
                    cout << "Enter the new web page's id:" << endl;
                    cin >> line2;
                    if (!(bH.searchPageByID(line2) == nullptr)) {
                        cout << "This ID already exists. Try again." << endl;
                    } else {
                        break;
                    }
                }
                while (true) {
                    cout << "Enter the previous page's url (or First):" << endl;
                    cin >> line3;
                    if ((bH.searchPageByURL(line3) == nullptr) && (line3 != "First")) {
                        cout << "INVALID(previous page url)... Please enter a VALID previous page url!" << endl;
                    } else {
                        break;
                    }
                } 
                if (line3 == "First") {
                    temp->id = line2;
                    temp->url = line;
                    temp->next = nullptr;
                    temp->views = 0;
                    temp->owner = "";
                    bH.addWebPage(nullptr, temp);
                    break;
                } else {
                    temp->id = line2;
                    temp->url = line;
                    temp->next = nullptr;
                    temp->views = 0;
                    temp->owner = "";
                    bH.addWebPage(bH.searchPageByURL(line3), temp);
                    break;
                }
                break;
            case '4':
                cout << "Enter url of the web page to add the owner:" << endl;
                cin >> line4;
                if (bH.searchPageByURL(line4) == nullptr) {
                    cout << "Page not found." << endl;
                    break;
                }
                cout << "Enter the owner:";
                cin.ignore();
                getline(cin, line5);
                bH.addOwner(line4, line5);
                break;
            case '5':
                while (true) {
                    cout << "Enter url of the web page to check the view count: " << endl;
                    cin >> line6;
                    if (bH.searchPageByURL(line6) == nullptr) {
                        cout << "Page not found. Try again." << endl;
                    } else {
                        cout << "View count for URL - " << line6 << " is " << bH.searchPageByURL(line6)->views << endl;
                        bH.updateViews(line6);
                        break;
                    }
                }
                break;
            case '6':
                cout << "Quitting...Goodbye!\n";
                delete temp;
                exit(0);
            default:
                goto start;
        }
        //delete temp;
    }
    return 0;
}




/************************************************
           Definitions for main_1.cpp
************************************************/
void displayMenu()
{
    // COMPLETE: You DO NOT need to edit this
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build history " << endl;
    cout << " 2. Display history " << endl;
    cout << " 3. Add web page " << endl;
    cout << " 4. Add owner" << endl;
    cout << " 5. View count for a web page" << endl;
    cout << " 6. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
