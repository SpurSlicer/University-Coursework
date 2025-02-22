#include "BookCollection.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#define DBL_MIN 2.2250738585072014e-308
using namespace std;

//HELPER FUNCTION: it's just a simplified strcmp to show greater and less than stuff


/*
CONSTRUCTOR
*/
BookCollection::BookCollection() {
    root = nullptr;
}
/*------*/


/*
DESTRUCTOR
*/
void traversalCompareDestructor(Book* b) {
    if (b == nullptr) {
        return;
    }
    Book* l = b->left;
    Book* r = b->right;
    traversalCompareDestructor(l);
    delete b;
    traversalCompareDestructor(r);
    return;
}
BookCollection::~BookCollection() {
    traversalCompareDestructor(root);
}
/*-----*/


/*-----
ADD BOOK
-----*/
void traversalCompareAdd(string n, Book*& b, Book* newBook) {
    if (b == nullptr) {
        b = newBook;
        b->left = nullptr;
        b->right = nullptr;
    } else if (b->bookName > n) {
        traversalCompareAdd(n, b->left, newBook);
    } else {
        traversalCompareAdd(n, b->right, newBook);
    }
}
void BookCollection::addBook(string bookName, string author, double rating) {
    Book* newBook = new Book {bookName, author, rating};
    if (root == nullptr) {
        root = newBook;
        return;
    }
    traversalCompareAdd(bookName, root, newBook);
    return;
}
/*------*/


/*-----
SHOW BOOK COLLECTION
-----*/
void traversalDisplay(Book* b) {
    if (b) {
        traversalDisplay(b->left);
        cout << "BOOK: " << b->bookName << " BY: " << b->author << " RATING: " << b->rating << endl;
        traversalDisplay(b->right);
    }
    return;
}
void BookCollection::showBookCollection() {
    if (root == nullptr) {
        cout << "Collection is empty." << endl;
    } else {
        traversalDisplay(root);
    }
    return;
}
/*------*/


/*-----
SHOW BOOK
-----*/
void traversalDisplayShow(Book* b, string n, bool& f) {
    if (b == nullptr) {
        return;
    }
    if (b->bookName == n) {
        if (!f) {
            f = true;
        }
        cout << "Book:\n==================\nName :" << b->bookName << "\nAuthor :" << b->author << "\nRating :" << b->rating << endl;
        return;
    }
    traversalDisplayShow(b->left, n, f);
    traversalDisplayShow(b->right, n, f);
    return;
}
void BookCollection::showBook(string bookName) {
    bool flag = false;
    traversalDisplayShow(root, bookName, flag);
    if (!flag) {
        cout << "Book not found." << endl;
    }
    return;
}
/*------*/



/*-----
SHOW BOOKS BY AUTHOR
-----*/
void traversalDisplayAuthor(Book* b, string a, bool& f) {
    if (b == nullptr) {
        return;
    }
    traversalDisplayAuthor(b->left, a, f);
    if (b->author == a) {
        if (!f) {
            f = true;
        }
        cout << b->bookName << " RATING: " << b->rating << endl;
    }
    traversalDisplayAuthor(b->right, a, f);
    return;
}
void BookCollection::showBooksByAuthor(string author) {
    bool flag = false;
    cout << "Books By: " << author << endl;
    traversalDisplayAuthor(root, author, flag);
    return;
}
/*------*/


/*-----
SHOW HIGHEST RATED BOOKS
-----*/
void traversalDisplayHigh(Book* b, double& d) {
    if (b == nullptr) {
        return;
    }
    traversalDisplayHigh(b->left, d);        
    if (b->rating > d) {
        d = b->rating;
    }
    traversalDisplayHigh(b->right, d);
    return;
}
void traversalDisplayHigh2(Book* b, double d) {
    if (b) {
        traversalDisplayHigh2(b->left, d);
        if (d == b->rating) {
            cout << b->bookName << " BY: " << b->author << endl;
        }
        traversalDisplayHigh2(b->right, d);
    }
    return;
}
void BookCollection::showHighestRatedBooks() {
    if (root == nullptr) {
        cout << "Collection is empty." << endl;
        return;
    }
    double d = DBL_MIN;
    traversalDisplayHigh(root, d);
    cout << "Highest Rating: " << d << endl;
    traversalDisplayHigh2(root, d);
    return;
}
/*------*/


/*-----
GETS n TO CALCULATE HEIGHT
-----*/
int traversalGetHieght(Book* b) {
    if (b == nullptr) {
        return 0;
    } else {
        int l = traversalGetHieght(b->left);
        int r = traversalGetHieght(b->right);
        return max(l,r)+1;
    }
}
int BookCollection::getHeightOfBookCollection() {
    return traversalGetHieght(root); 
}
