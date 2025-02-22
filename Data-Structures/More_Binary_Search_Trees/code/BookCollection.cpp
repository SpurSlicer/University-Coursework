#include "BookCollection.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

BookCollection::BookCollection() {
    root = nullptr;
}


void destructorHelper(Book* b) {
    if (!b) {
        return;
    }
    Book* l = b->left;
    Book* r = b->right;
    destructorHelper(l);
    delete b;
    destructorHelper(r);
    return;
}
BookCollection::~BookCollection() {
    destructorHelper(root);
}


//----------------------------------------------------------------------------------------
//Remove Book Stuff
//----------------------------------------------------------------------------------------
Book* _searchMinHelper(Book* T) {
    if (T == 0) return 0;
    else if (T->left == 0) return T;
    else return _searchMinHelper(T->left);
}
Book* _findBook(Book* T, string bookName);
void _removeHelper(Book* &T, string key) {
    if (T == 0) return;
    else if (key < T->bookName) _removeHelper(T->left, key);
    else if (key > T->bookName) _removeHelper(T->right, key);
    else {
        if (!T->left  && !T->right) {
            delete T;
            T = nullptr;
        } else if (!T->left && T->right) {
            Book* child = T->right;
            delete T;
            T = child;
        } else if (T->left && !T->right) {
            Book* child = T->left;
            delete T;
            T = child;
        } else {
            Book* temp = _searchMinHelper(T->right);
            T->bookName = temp->bookName;
            T->rating = temp->rating;
            T->author = temp->author;
            _removeHelper(T->right, T->bookName);
        }
    }
    return;
}

void BookCollection::removeBook(string bookName) {
    if (!root) {
        cout << "Book not found!" << endl;
        return;
    }
    if (!root->left && !root->right) {
        delete root;
        root = 0;
        return;
    } else if (!_findBook(root, bookName)) {
        cout << "Book not found!" << endl;
        return;
    }
    _removeHelper(root, bookName);

    return;
}


//----------------------------------------------------------------------------------------
//Rotate Collection Stuff
//----------------------------------------------------------------------------------------
Book* _findBook(Book* T, string bookName) {
    if (!T) return nullptr;
    if (T->bookName == bookName) return T;
    if (T->bookName > bookName) return _findBook(T->left, bookName);
    if (T->bookName < bookName) return _findBook(T->right, bookName);
}
Book* _findParent(Book* T, string bookName) {
    if (!T) return nullptr;
    if ((T) && (T->bookName == bookName)) return nullptr;
    //if ((!T->left) && (!T->right)) return nullptr;
    if (((T->left) && T->left->bookName == bookName) || ((T->right) && T->right->bookName == bookName)) return T;
    if (T->bookName > bookName) return _findParent(T->left, bookName);
    if (T->bookName < bookName) return _findParent(T->right, bookName);
}
void BookCollection::rotateLeftCollection(string bookName) {
    Book* x = _findBook(root, bookName);
    //testing edge cases
    if ((!x)) {
        return;
    } 
    Book* y = x->right;
    Book* xp = _findParent(root, x->bookName);
    if (y) {
        x->right = y->left;
        y->left = x;
        if (xp) {
            if ((xp->left) && (xp->left->bookName == x->bookName)) {
                xp->left = y;
            } else if ((xp->right) && (xp->right->bookName == x->bookName)) {
                xp->right = y;
            }
        } else if (x == root) {
            root = y;
        }
    }
}

//----------------------------------------------------------------------------------------
//Book Collection Stuff
//----------------------------------------------------------------------------------------
bool _pathChecker(Book* T, string CMP, vector<string>& things) {
    if (!T) return false;
    things.push_back(T->bookName);
    if (T->bookName == CMP) return true;
    if (_pathChecker(T->left, CMP, things) || _pathChecker(T->right, CMP, things)) return true;
    things.pop_back();
    return false;
}
string BookCollection::closestParent(string book1, string book2) {
    Book* one = _findBook(root, book1);
    Book* two = _findBook(root, book2);
    if ((!one) || (!two)) {
        cout << "Book not found!" << endl;
        return "Error - wrong book name";
    }
    string ans = "";
    vector<string> book1Names;
    vector<string> book2Names;
    _pathChecker(root, book1, book1Names);
    _pathChecker(root, book2, book2Names);
    for (int i = 0; i < (int)book1Names.size(); ++i) {
        for (int j = 0; j < (int)book2Names.size(); ++j) {
            if (book1Names[i] == book2Names[j]) {
                ans = book1Names[i];
            }
        }
    }
    return ans;
}