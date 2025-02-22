#ifndef SHAPE_H
#define SHAPE_H
#include <vector>
#include <iostream>
#include <math.h>

#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//  Cosine and Sine in degrees
#define Cos(x) (cos((x)*3.14159265/180))
#define Sin(x) (sin((x)*3.14159265/180))

typedef struct coordinate {
    double x;
    double y;
    double z;
} coordinate;

typedef coordinate color;

class shape {
    protected:
        std::vector<coordinate*> coords;
        std::vector<coordinate*> alt_coords;
        std::vector<coordinate*> lines;
        std::vector<std::vector<color*>> colors;
        coordinate* sphericalCoord(double, double);
    public:
        void printCoords(void);
        //void translate(double, double, double);
};
#endif
