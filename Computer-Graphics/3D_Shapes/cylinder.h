#ifndef CYLINDER_H
#define CYLINDER_H

#include "shape.h"

/*
typedef struct coordinate {
    double x;
    double y;
    double z;
} coordinate;
*/

enum cylinder_style {
    CYLINDER_DEFAULT = 0,
};

enum cylinder_type {
    FLIP_NONE = 0,
    FLIP_V = 1,
    FLIP_H_V = 2
};

class cylinder : public shape {
    private:
//      std::list<coordinate*> coords;
        void initStyles();
        int sides;
    public:
        cylinder(double);
        void render(coordinate, coordinate, cylinder_type, cylinder_style);
};

#endif