
#include "BrowserHistory.hpp"

BrowserHistory::BrowserHistory()
{
    // No changes needed
}

BrowserHistory::~BrowserHistory()
{
    // No changes needed
}
int size(WebPage* w) {
    int i = 1;
    while (w != nullptr) {
        w = w->next;
        ++i;
    }
    return i;
}
/*
 * Purpose: Has to detect if a defect is present in the linkedlist pointed by head
 * @param none
 * @return integer length of defect if one exists. If defect not present return -1
 */
int BrowserHistory::findDefectLength(){

    // TODO START =============================================
    WebPage* fast = head;
    WebPage* slow = head;
    int i = 0;
    while ((fast != nullptr) && (fast->next != nullptr)) {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow) {
            slow = slow->next;
            while (slow != fast) {
                slow = slow->next;
                ++i;
            }
            return ++i;
        }
    }
    return -1;
    // TODO END ==================================================
}

/*
 * Purpose: Has to remove all the WebPage nodes from [start, end] inclusive.
 * Has to print appropriate messages on cout like below if the linkedlist is empty
 * or if the values of start/ end are improper
 * follow the same order for couts in the writeup - check empty list first, then check wrong start/end values
 * @param integers start and end (1 based indexing not 0 based)
 * @return none
 */
void BrowserHistory::removeWebPages(int start, int end){

    // TODO START ===================================================
    if (head == nullptr) {
        cout << "Browsing history is Empty" << endl;
        return;
    }
    WebPage* pres = head;
    WebPage* prev = head;
    WebPage* temp = nullptr;
    int cnt = 1;
    while (pres != nullptr) {
        ++cnt;
        pres = pres->next;
    }
    //++cnt;
    if ((start < 1) || (end > cnt) || (start > end)) {
        cout << "Invalid start or end values" << endl;
        return;
    } 
    pres = head;
    cnt = 1;
    if (start == cnt) {
        while (cnt <= end) {
            temp = head->next;
            delete head;
            head = temp;
            ++cnt;
        }
    } else if (end == start) {
        while (cnt != end) {
            prev = pres;
            pres = pres->next;
            ++cnt;
        }
        temp = pres->next;
        delete prev->next;
        prev->next = pres->next;
    } else {
        while (pres != nullptr) {
            if (cnt >= start && cnt <= end) {
                temp = pres->next;
                delete prev->next;
                prev->next = temp;
                pres = prev->next;
                ++cnt;
            } else {
                pres = pres->next;
                ++cnt;
            }
        }
    }
    // TODO END ===================================================
}


/*
 * Purpose: Interweave the webpages alternatively into a new linkedlist 
 * starting with the first webpage in the list one
 * Assign the head of the new interweaved list to the head of this BrowserHistory
 * DO NOT create new nodes and copy the data, just use the same nodes from one and two and change pointers
 * If one of them runs out of length append the remaining of the other one at end
 * @param two linkedlist heads one and two
 * @return none
 */
void BrowserHistory::mergeTwoHistories(WebPage *headOne, WebPage* headTwo){

    // TODO START =============================================
    if ((headOne == nullptr) && (headTwo == nullptr)) {
        head = nullptr;
        return;
    } else if (headOne == nullptr) {
        head = headTwo;
        return;
    } else if (headTwo == nullptr) {
        head = headOne;
        return;
    }
    WebPage* temp = new WebPage;
    temp->next = nullptr;
    WebPage* watcher = temp;

    while (true) {
        if (headOne == nullptr) {
            temp->next = headTwo;
            break;
        } else if (headTwo == nullptr) {
            temp->next = headOne;
            break;
        } else {
            temp->next = headOne;
            temp = headOne;
            headOne = headOne->next;
            temp->next = headTwo;
            temp = headTwo;
            headTwo = headTwo->next;
        }
    }
    watcher = watcher->next;
    head = watcher;
    return;
    // TODO END ==================================================
}
