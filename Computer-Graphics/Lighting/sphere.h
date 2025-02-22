#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h"

/*
typedef struct coordinate {
    double x;
    double y;
    double z;
} coordinate;
*/

enum sphere_style {
    SPHERE_DEFAULT = 0,
    SPHERE_MOON = 1,
    SPHERE_TREE = 2
};

class sphere : public shape {
    private:
//      std::list<coordinate*> coords;
        void initStyles();
        const int d = 15;
    public:
        sphere();
        void render(coordinate, double, sphere_style);
};

#endif