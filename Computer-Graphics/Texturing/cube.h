#ifndef CUBE_H
#define CUBE_H

#include "shape.h"

/*
typedef struct coordinate {
    double x;
    double y;
    double z;
} coordinate;
*/

enum cube_style {
    CUBE_DEFAULT = 0,
    CUBE_GROUND = 1,
    CUBE_WATER = 2
};

class cube : public shape {
    private:
//      std::list<coordinate*> coords;
        void initStyles();
    public:
        cube();
        void render(coordinate, coordinate, double, cube_style, bool);
};

#endif