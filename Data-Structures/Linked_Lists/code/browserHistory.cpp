/*************************************************************/
/*                BrowserHistory Definition                  */
/*************************************************************/
/* TODO: Implement the member functions of BrowserHistory    */
/*     This class uses a linked-list of WebPage structs to   */
/*     represent the schedule of web pages                   */
/*************************************************************/

#include "browserHistory.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

/*
 * Purpose: Constructor for empty linked list
 * @param none
 * @return none
 */
BrowserHistory::BrowserHistory() {
    /*
    DO NOT MODIFY THIS
    This constructor is already complete. 
    */
    head = nullptr;
}

/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool BrowserHistory::isEmpty() {
    /* finished. do not touch. */
    return (head == nullptr);
}

/*
 * Purpose: prints the current list of pages 
 * in the given format.
 * [ID::1]-(URL::url1) -> ... -> NULL
 * @param none
 * @return none
 */
void BrowserHistory::displayHistory() {
    WebPage* temp = head;
    cout << "== CURRENT BROWSER HISTORY ==" << endl;
    if (temp == nullptr) {
        cout << "Empty History" << endl;
    } else {
        while (temp != nullptr) {
            cout << "[ID:: " << temp->id << "]-(URL::" << temp->url << ") -> ";
            temp = temp->next;
        }
    }
    cout << "NULL\n===\n";
    return;
}

/*
 * Purpose: Add a new webpage to the browser history LL
 *   between the previous and the page that follows it in the list.
 * @param previousPage, the show that comes before the new page
 * @param newPage, the webpage to be added. 
 * @return none
 */
void BrowserHistory::addWebPage(WebPage* previousPage, WebPage* newPage) {
    WebPage* newPagePtr = new WebPage;
    WebPage* previousPagePtr = new WebPage;
    newPagePtr = newPage;
    previousPagePtr = previousPage;
    if (previousPagePtr == nullptr) {
        newPagePtr->next = head;
        head = newPagePtr;
        cout  <<  "adding: "  <<  "["  <<  newPagePtr->id  <<  "]-"  <<  newPagePtr->url  <<  " (HEAD)\n";
        return;
    } else if (previousPagePtr->next == nullptr) {
        previousPagePtr->next = newPagePtr;
        previousPagePtr = newPagePtr;
    } else {
        newPagePtr->next = previousPagePtr->next;
        previousPagePtr->next = newPagePtr;
    }
    cout  <<  "adding: "  <<  "["  <<  newPagePtr->id  <<  "]-"  <<  newPagePtr->url  <<  " (prev: "  <<  "["  <<  previousPage->id  <<  "])\n";
    return;
}

/*
 * Purpose: populates the BrowserHistory with the predetermined pages
 * @param none
 * @return none
 */
void BrowserHistory::buildBrowserHistory() {
    WebPage* Web1 = new WebPage;
    WebPage* Web2 = new WebPage;
    WebPage* Web3 = new WebPage;
    WebPage* Web4 = new WebPage;
    WebPage* Web5 = new WebPage;

    Web1->id = 10;
    Web1->owner = "";
    Web1->url =  "https://www.colorado.edu/";
    Web1->views = 0;
    Web1->next = nullptr;

    Web2->id = 11;
    Web2->owner = "";
    Web2->url =  "https://www.wikipedia.org/";
    Web2->views = 0;
    Web2->next = nullptr;

    Web3->id = 12;
    Web3->owner = "";
    Web3->url =  "https://brilliant.org/";
    Web3->views = 0;
    Web3->next = nullptr;

    Web4->id = 13;
    Web4->owner = "";
    Web4->url =  "https://www.khanacademy.org/";
    Web4->views = 0;
    Web4->next = nullptr;

    Web5->id = 14;
    Web5->owner = "";
    Web5->url =  "https://www.numberphile.com/";
    Web5->views = 0;
    Web5->next = nullptr;

    WebPage* temp = head;
    while (temp != nullptr) {
        temp = temp->next;
    }

    addWebPage(temp, Web1);
    addWebPage(Web1, Web2);
    addWebPage(Web2, Web3);
    addWebPage(Web3, Web4);
    addWebPage(Web4, Web5);
    return;
}


/*
 * Purpose: Search the BrowserHistory for the specified 
 * web page by ID and return a pointer to that node.
 * @param int id - ID of the web page to look for in LL.
 * @return pointer to node of page, or NULL if not found
 *
 */
WebPage* BrowserHistory::searchPageByID(int id) {
    WebPage* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}


/*
 * Purpose: Search the BrowserHistory for the specified 
 * web page by the URL and return a pointer to that node.
 * @param string url - url of the web page to look for in LL.
 * @return pointer to node of page, or NULL if not found
 *
 */
WebPage* BrowserHistory::searchPageByURL(std::string url) {
    WebPage* temp = head;
    while (temp != nullptr) {
        if (temp->url == url) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

/*
 * Purpose: Give an owner to a web page.
 * @param receiver - name of the show that is receiving the rating
 * @param rating - the rating that is being given to a show
 * @return none
 */
void BrowserHistory::addOwner(std::string url, string owner) {
    WebPage* temp = head;
    while (temp != nullptr) {
        if (temp->url == url ) {
            temp->owner = owner;
            cout  <<  "The owner ("  <<  owner  <<  ") has been added for the ID - "<<  temp->id  <<  "\n";
            return;
        }
        temp = temp->next;
    }
    cout  <<  "Page not found\n";
    return;
}

void BrowserHistory::updateViews(string url) {
    WebPage* temp = head;
    while (temp != nullptr) {
        if (temp->url == url ) {
            ++temp->views;
        }
        temp = temp->next;
    }
    return;  
}