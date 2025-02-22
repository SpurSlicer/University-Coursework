/**
* This is the implementation for the hash table class provided by the project.
*/
#include<iostream>
#include <vector>
#include <string>
#include "MovieHashTable.hpp"
using namespace std;

/**
* Default constructor for the hash table.
* @param void
* @return void
*/
MovieHashTable::MovieHashTable() {
    table_size = DEFAULT_HTABLE_CAPACITY;
    table = new MovieNode*[table_size];
    for (int i = 0; i < table_size; ++i) {
        table[i] = nullptr;
    }
    n_collisions = 0;
}

/**
* Overloaded constructor for the hash table.
* @param void
* @return void
*/
MovieHashTable::MovieHashTable(int s) {
    table_size = s;
    table = new MovieNode*[table_size];
    for (int i = 0; i < table_size; ++i) {
        table[i] = nullptr;
    }
    n_collisions = 0;
}

/**
* Deconstructor for the hash table.
* @param void
* @return void
*/
MovieHashTable::~MovieHashTable() {
    for (int i = 0; i < table_size; ++i) {
        MovieNode* temp = table[i];
        while (temp) {
            MovieNode* temp2 = temp->next;
            delete temp;
            temp = temp2;
        }
    }
    delete[] table;
}

/**
* Computes the hash index by adding all of the character ascii values of "grde1275" together.
* It does the same thing with th eprovided title string.
* It ends by returning the absolute value of both values multiplied together modulo the table size
* as to prevent overflow :3
* @param string
* @return int
*/
int MovieHashTable::hash(string title) {
    int num = 1;
    int key = 1;
    string identikey = "grde1275";
    for (int i = 0; i < identikey.size(); ++i) {
        num += (identikey[i]);
    }
    for (int i = 0; i < title.size(); ++i) {
        key += title[i];
    }
    return (abs(num*key)) % table_size;
}

/**
* It begins by calculating the hash of the value provided.
* It then checks whether there is a value in that hash index (i.e. a collision)
* If that is the case, it performs a chaining algorithm to attatch that node.
* If not, then it adds the node to that table index.
* @param string, MovieNode*
* @return void
*/
void MovieHashTable::insert(string title, MovieNode* movie) {
    int h = hash(title);
    while (true) {
        if (!table[h]) {
            table[h] = movie;
            return;
        } else {
            MovieNode* temp = table[h];
            while (temp->next) {
               temp = temp->next;
               setCollisions();
            }
            temp->next = movie;
            return;
        }
    }
}

/**
* Creates a temporary movie node at the given hash value of the title provided.
* It then checks if the title of the hashed node matches the title given.
* If it does not, it begins to iterate through the linked list.
* If it gets to the end, then that node does not exist.
* If it finds matching titles, then it returns that node.
* @param string
* @return MovieNode*
*/
MovieNode* MovieHashTable::search(string title) {
    MovieNode* temp = table[hash(title)];
    if (!temp) return nullptr;
    while (temp && (temp->title != title)) {
        temp = temp->next;
    }
    if (!temp) return nullptr;
    return temp;
}

/**
* Returns the collision value.
* @param void
* @return int
*/
int MovieHashTable::getCollisions() {
    return n_collisions;
}

/**
* Increments the collision value.
* @param void
* @return void
*/
void MovieHashTable::setCollisions() {
    ++n_collisions;
    return;
}
