#ifndef OUTPOST_H
#define OUTPOST_H

#include "shape.h"

/*
typedef struct coordinate {
    double x;
    double y;
    double z;
} coordinate;
*/

enum outpost_style {
    OUTPOST_DEFAULT = 0,
};

class outpost : public shape {
    private:
//      std::list<coordinate*> coords;
        void initStyles();
        int sides;
    public:
        outpost(double);
        void render(coordinate, coordinate, outpost_style, bool);
};

#endif