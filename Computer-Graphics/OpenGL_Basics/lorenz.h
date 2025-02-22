#ifndef LORENZ_H
#define LORENZ_H

#include <array>
#include <iostream>
#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class lorenz {
    private:
        int iterations = 50000;
        double s = 10, b = 2.6666, r = 28;
    public:
        lorenz();
        ~lorenz();
        void displayCoordinates(double);
        void modifyS(double);
        void modifyB(double);
        void modifyR(double);
        double getS();
        double getB();
        double getR();
        void resetParameters();
        void modifyIterations(int);
        int getIterations();
};

#endif