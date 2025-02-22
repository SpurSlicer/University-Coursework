#include "LinkedInNetwork.hpp"
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

void LinkedInNetwork::addProfessional(string name){
    bool flag = false;
    for (int i = 0; i < professionals.size(); ++i) {
        if (professionals[i]->name == name) {
            flag = true;
            break;
        }
    }
    if (flag) {
        cout << name << " found." << endl;
        return;
    }
    Professional* p = new Professional;
    p->name = name;
    p->connectionOrder = professionals.size();
    professionals.push_back(p);
    return;
}

void LinkedInNetwork::addConnection(string v1, string v2){
    for (int i = 0; i < professionals.size(); ++i) {
        if (professionals[i]->name == v1) {
            for (int j = 0; j < professionals.size(); ++j) {
                if ((professionals[j]->name == v2) && (i != j)) {
                    neighbor p;
                    p.v = professionals[j];
                    professionals[i]->neighbors.push_back(p);
                    neighbor p2;
                    p2.v = professionals[i];
                    professionals[j]->neighbors.push_back(p2);
                }
            }
        }
    }
}

void LinkedInNetwork::displayConnections(){
    for (vector<Professional*>::iterator itr = professionals.begin(); itr != professionals.end(); ++itr) {
        auto position = itr - professionals.begin();
        cout << (*itr)->name << " --> ";
        for (int i = 0; i < (*itr)->neighbors.size(); ++i) {
            cout << (*itr)->neighbors[i].v->name << " ";
        }
        cout << endl;
    }
}
/*bool checker(Professional* p) {
    if (p->neighbors.empty()) return false;
    for (auto i : p->neighbors) {
        if (i.v->visited == false) return true;
    }
    return false;
}*/

void LinkedInNetwork::breadthFirstTraverse(string sourceProfessional){
    /* this finds the given professional source */
    Professional* profStart;
    for (int i = 0; i < (int) professionals.size(); ++i) {
        professionals[i]->visited = false;
        if (professionals[i]->name == sourceProfessional) {
            profStart = professionals[i];
        }
    }
    /*-------------------------------------------*/
    /* this adjusts the other thing */
    
    queue<Professional*> q;
    queue<Professional*> q_temp;
    q.push(profStart);
    profStart->visited = true;
    int counter = 1;
    cout << "Starting Professional (root): " << sourceProfessional << "-> ";
    do {
        while (!q.empty()) {
            for (int i = 0; i < q_temp.size(); ++i) {
                q_temp.pop();
            } 
            for (auto i : q.front()->neighbors) {
                if (!i.v->visited) {
                    q_temp.push(i.v);
                    i.v->visited = true;
                    cout << i.v->name << "(" << counter << ") ";
                }   
            }
            q.pop();
        }
        ++counter;
        q = q_temp;
    } while (!q_temp.empty());
}
vector<string> LinkedInNetwork::suggestProfessionalsWithinKthOrder(string professionalName, int k){
    vector<string> professionalsWithinK;
    /* this finds the given professional source */
    Professional* profStart;
    for (int i = 0; i < (int) professionals.size(); ++i) {
        professionals[i]->visited = false;
        if (professionals[i]->name == professionalName) {
            profStart = professionals[i];
        }
    }
    /*-------------------------------------------*/
    /* this adjusts the other thing */
    
    queue<Professional*> q;
    queue<Professional*> q_temp;
    q.push(profStart);
    profStart->visited = true;
    int counter = 1;
    do {
        while (!q.empty()) {
            for (int i = 0; i < q_temp.size(); ++i) {
                q_temp.pop();
            } 
            for (auto i : q.front()->neighbors) {
                if (!i.v->visited) {
                    q_temp.push(i.v);
                    if (k >= counter) {
                        professionalsWithinK.push_back(i.v->name);
                    }
                    i.v->visited = true;
                }   
            }
            q.pop();
        }
        q = q_temp;
        ++counter;
    } while (!q_temp.empty());
    if (professionalsWithinK.size() > 2) iter_swap(professionalsWithinK.begin(),(professionalsWithinK.end()-1));
    reverse(professionalsWithinK.begin(), professionalsWithinK.end());
    return professionalsWithinK;
}