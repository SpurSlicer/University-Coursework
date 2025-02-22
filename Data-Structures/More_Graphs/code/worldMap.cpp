#include "worldMap.hpp"
#include <vector>
#include <stack>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

WorldMap::WorldMap() {}

void WorldMap::createWorldMap(string fileName)
{
    // TODO START
    ifstream fin(fileName);
    bool flag = false;
    if (!fin.fail()) {
        int row = -1;
        while (!fin.eof()) {
            string buffer = "", token = "";
            getline(fin, buffer);
            stringstream ss(buffer);
            int col = 0;
            while (!ss.eof()) {
                getline(ss, token, ' ');
                if (row == -1) {
                    if (!flag) {
                        rows = stoi(token);
                        flag = true;
                    } else {
                        cols = stoi(token);
                    }
                } else {
                    worldMap[row][col] = stoi(token);
                    ++col;
                }
            }
            if (row == -1) {
                worldMap = new int*[rows];
                for (int i = 0; i < rows; ++i) {
                    worldMap[i] = new int[cols];
                }
            } 
            ++row;
        }
    }
    // TODO END
}

void WorldMap::printWorldMap()
{
    // TODO START
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << "| " << worldMap[i][j] << " ";
        }
        cout << "|" << endl;
    }
    // TODO END
}

void WorldMap::addRegion(int x, int y)
{
    // TODO START
    for (auto i : regions) {
        if ((i->x == x) && (i->y == y)) {
            return;
        }
    }
    Region* r = new Region;
    r->x = x;
    r->y = y;
    regions.push_back(r);
    // TODO END
}

bool checkIfEdgeExists(Region *r, int x2, int y2)
{
    if (r->x == x2) {
        if (r->y == y2) {
            return true;
        }
    }
    return false;
}

void WorldMap::addEdgeBetweenRegions(int x1, int y1, int x2, int y2){
    // TODO START
    for(unsigned int i = 0; i < regions.size(); i++){
        if(regions[i]->x == x1 && regions[i]->y == y1){
            for(unsigned int j = 0; j < regions.size(); j++){
                if(i != j && regions[j]->x == x2 && regions[j]->y == y2){
                    if(!checkIfEdgeExists(regions[i], x2, y2)){
                        NeighboringRegion av;
                        av.region = regions[j];
                        regions[i]->neighbors.push_back(av);
                        // another vertex for edge in other direction
                        NeighboringRegion av2;
                        av2.region = regions[i];
                        regions[j]->neighbors.push_back(av2);
                    }
                }
            }
        }
    }
    // TODO END
}

vector<vector<int>> WorldMap::findAdjacentLandRegions(int x, int y){
    // TODO START
    // identify the open paths that are adjacent to the vertex at x, y
    // fill adjArr array with the numbers of the adjacent vertices
    vector<vector<int>> neighbors; 
    for(int i = x-1; i <= x + 1; i++){
        if(i < 0 || i >= this->rows){
            continue;
        }
        for(int j = y-1; j <= y+1; j++){
            if(j < 0 || j >= this->cols){
                continue;
            }
            // if there is an open path at this adjacent position, add to adjArray
            if(!(i == x && j == y) && worldMap[i][j] == 1){
                neighbors.push_back({i,j});
            }
        }
    }
    return neighbors;
    // TODO END
}

void WorldMap::convertWorldMapToAdjacencyListGraph()
{
    // TODO START
    for (int x = 0; x < rows; ++x) {
        for (int y = 0; y < cols; ++y) {
            if (worldMap[x][y] == 1) {
                addRegion(x, y);
                for (auto i : findAdjacentLandRegions(x,y)) {
                    addEdgeBetweenRegions(x, y, i[0], i[1]);
                }
            }
        }
    }
    // TODO END
}

// helper function to check if v2 is a neighbor of verter v1
bool isNeighbor(int x1, int y1, int x2, int y2, const vector<Region *> regions)
{
    return false;
}

WorldMap::~WorldMap()
{
    // TODO START
    for (int i = 0; i < rows; ++i) {
        delete[] worldMap[i];
    }
    delete[] worldMap;
    for (auto i : regions) {
        delete i;
    }
    // TODO END
}

void WorldMap::displayEdges()
{
    // TODO START
    for (auto i : regions) {
        cout << "(" << i->x << "," << i->y << ") --> ";
        for (auto j : i->neighbors) {
            cout << "(" << j.region->x << "," << j.region->y << ") ";
        }
        cout << endl;
    }
    // TODO END
}
// HELPER FOR findNumOfIslands
void findNumOfIslandsHelper(Region *r)
{
    //if (r->visited == true) return;
    cout << "Reached vertex: "<<"("<<r->x<<','<<r->y<<")"<<endl;
    r->visited = true;
    for(auto i : r->neighbors) {
        if (!i.region->visited) findNumOfIslandsHelper(i.region);
    }
    return;
}

int WorldMap::findNumOfIslands()
{
    // TODO START
    if (regions.empty()) {
        return -1;
    }
    int count = 0;
    for (auto i : regions) {
        if (!i->visited) {
            findNumOfIslandsHelper(i);
            ++count;
        }
    }
    return count;
    // TODO END
}

vector<Region *> &WorldMap::getRegions()
{
    return regions;
}
