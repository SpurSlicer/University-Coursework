#ifndef PYRAMID_H
#define PYRAMID_H

#include "shape.h"

/*
typedef struct coordinate {
    double x;
    double y;
    double z;
} coordinate;
*/

enum pyramid_style {
    PYRAMID_DEFAULT = 0,
    PYRAMID_SAND = 1,
    PYRAMID_GRASS = 2,
    PYRAMID_ROOF = 3
};

class pyramid : public shape {
    private:
//      std::list<coordinate*> coords;
        void initStyles();
    public:
        pyramid();
        void render(coordinate, coordinate, double, pyramid_style);
};

#endif