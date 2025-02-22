#include "shape.h"

void shape::printCoords(void) {
    for (auto i : this->coords)
        printf("x: %.3f y: %.3f z: %.3f\n", i->x, i->y, i->z);
}
coordinate* shape::sphericalCoord(double th,double ph) { return new coordinate({Sin(th)*Cos(ph) , Sin(ph) , Cos(th)*Cos(ph)}); }
/*void shape::translate(double x, double y, double z) {
    for (auto i: this->coords) {
        i->x += x;
        i->y += y;
        i->z += z;
    }
}*/