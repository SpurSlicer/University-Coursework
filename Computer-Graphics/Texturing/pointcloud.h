#ifndef POINTCLOUD_H
#define POINTCLOUD_H

#include "shape.h"
#include <ctime>
#include <cstdlib>

/*
typedef struct coordinate {
    double x;
    double y;
    double z;
} coordinate;
*/

enum pointcloud_style {
    POINTCLOUD_DEFAULT = 0,
    POINTCLOUD_WHITE = 1
};

class pointcloud : public shape {
    private:
//      std::list<coordinate*> coords;
        const int point_count = 10000;
        void initStyles();
    public:
        pointcloud();
        void render(pointcloud_style);


};

#endif