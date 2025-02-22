#ifndef CONE_H
#define CONE_H

#include "shape.h"

/*
typedef struct coordinate {
    double x;
    double y;
    double z;
} coordinate;
*/

enum cone_style {
    CONE_DEFAULT = 0,
};

class cone : public shape {
    private:
//      std::list<coordinate*> coords;
        void initStyles();
        int sides;
    public:
        cone(double);
        void render(coordinate, coordinate, double, cone_style);
};

#endif