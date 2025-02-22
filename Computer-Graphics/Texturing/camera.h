#ifndef CAMERA_H
#define CAMERA_H

#ifdef USEGLEW
#include <GL/glew.h>
#endif
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
// Tell Xcode IDE to not gripe about OpenGL deprecation
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#else
#include <GL/glut.h>
#endif

#include <cmath>
#include "shape.h"

enum camera_state {
    ORTHO = 0,
    PERSPECTIVE = 1,
    FIRST_PERSON = 2
};

class camera {
    private: 
        camera_state state = ORTHO;
        int th = 135;
        int ph = 90, fp_ph;
        double zh = 0;
        double asp = 1;
        int fov = 55;
        double dim = 29.0;
        double pos_x = 0.0, pos_y = -6.0, pos_z = 0.0;

    public:
        //camera();
        void project();
        void resetAngles();
        void resetAnglesPerpendicular();
        void changeState();
        void reshapeAsp(int, int);
        void rotate(int);
        void idleSetZh(double);
        int getTh();
        int getPh();
        int getFpPh();
        camera_state getState();
        void display();
        void translate(unsigned char);
        void timer(int);
};

#endif