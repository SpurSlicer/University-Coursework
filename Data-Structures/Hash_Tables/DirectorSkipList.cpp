#include<iostream>
#include <vector>
#include <string>
#include "DirectorSkipList.hpp"
using namespace std;

/**
* Default constructor for director skip list
* @param void
* @return void
*/
DirectorSkipList::DirectorSkipList() {
    head = new DirectorSLNode;
    capacity = DEFAULT_CAPACITY;
    levels = DEFAULT_LEVELS;
    head->next = vector<DirectorSLNode*>(levels, nullptr);
    size = 0;
}

/**
* Overloaded constructor for director skip list
* @param void
* @return void
*/

DirectorSkipList::DirectorSkipList(int _cap, int _levels) {
    head = new DirectorSLNode;
    capacity = _cap;
    levels = _levels;
    head->next = vector<DirectorSLNode*>(levels,nullptr);
    size = 0;
}

/**
* Deconstructor for director skip list
* @param void
* @return void
*/
DirectorSkipList::~DirectorSkipList() {
    DirectorSLNode* temp = head;
    for (int i = (levels - 1); i >= 0; --i) {
        while (temp) {
            DirectorSLNode* del = temp;
            temp = temp->next[i];
            for (auto i : del->movies) {
                delete i;
            }
            delete del;
        }
        temp = head;
    }
    delete head;
}

/**
* Inserts a movie node to a given director (if a director exists) or creates a new director
* in the skip list to store the movie node in.
* Utilizes coin flipping to determine how many levels a node will be visible on.
* @param string, MovieNode*
* @return void
*/
void DirectorSkipList::insert(string director, MovieNode* _movie) {
    if (search(director)) {
        search(director)->addMovie(_movie);
        return;
    } else if (size >= capacity) {
        return;
    }
    int curr_level = 1;
    while ((curr_level < levels) && (rand() % 2 == 0)) { 
        ++curr_level;
    }
    DirectorSLNode* new_node = new DirectorSLNode(director, curr_level);
    new_node->addMovie(_movie);
    DirectorSLNode* temp = head;
    vector<DirectorSLNode*> node_list(levels, nullptr);
    for (int i = (levels - 1); i >= 0; --i) {
        while (temp->next[i] != nullptr && temp->next[i]->director < director) {
            temp = temp->next[i];
        }
        //node_list.push_back(temp);
        node_list[i]=temp;
        //temp = head;
    }
    for (int i = 0; i < curr_level; ++i) {
        new_node->next[i] = node_list[i]->next[i];
        node_list[i]->next[i] = new_node;
    }
    ++size;
    return;
}

/**
* Searches through the skip list by starting at the top level and iterating downwards until the skip list director string is greater than or
* equal to the directors string provided. There are checks to make sure that an equal node isn't skipped along the way.
* Depending on if the node was found, either that node or nullptr will be returned.
* @param string
* @return DirectorSLNode*
*/
DirectorSLNode *DirectorSkipList::search(string director) {
    DirectorSLNode* temp = head;
    for (int i = (levels - 1); i >= 0; --i) {
        if (temp->director == director) break;
        while (temp->next[i] && (temp->next[i]->director < director)) {
            temp = temp->next[i];
        }
        if (temp->director == director) break;
        //cout << temp->director << " " << director << endl;
    }
    return (temp->director == director) ? temp : nullptr;
}

/**
* Iterates through each level and prints every connected node for that level by displaying their director names.
* @param void
* @return void
*/
void DirectorSkipList::prettyPrint() {
    for (int i = 0; i < levels; ++i) {
        DirectorSLNode *temp = head;
        cout << "Level " << i+1;
        if (temp->next[i]) {
            while (temp->next[i]) {
                cout << " -> " << temp->director;
                temp = temp->next[i];
            }
        }
        cout << " END" << endl;
    }
}
