#include "lorenz.h"

lorenz::lorenz() { }
lorenz::~lorenz() { }
void lorenz::displayCoordinates(double w) { 
    double x = 1, y = 1, z = 1,dt = 0.001;
    const int colorParam = (int)this->iterations/6;
    const double colorInc = 1.0 / colorParam;
    for (int i = 0; i < this->iterations; i++) {
        glVertex4f(x, y, z, w);
        double dx = this->s*(y-x);
        double dy = x*(this->r-z)-y;
        double dz = x*y - this->b*z; 
        x += dt*dx;
        y += dt*dy;
        z += dt*dz;
        if (i < colorParam)
            glColor3f(1.0,(colorInc*(i%colorParam)),0.0);
        else if (i < 2 * colorParam)
        glColor3f((1.0-(colorInc*(i%colorParam))),1.0,0.0);
        else if (i < 3 * colorParam)
        glColor3f(0.0,1.0,(colorInc*(i%colorParam)));
        else if (i < 4 * colorParam)
            glColor3f(0.0,(1.0-(colorInc*(i%colorParam))),1.0);
        else if (i < 5 * colorParam)
        glColor3f((colorInc*(i%colorParam)),0.0,1.0);
        else if (i < 6 * colorParam)
            glColor3f(1.0,0.0,(1.0-(colorInc*(i%colorParam))));
        glVertex4f(x, y, z, w);
    }
}
void lorenz::modifyS(double d) { this->s += d; }
void lorenz::modifyB(double d) { this->b += d; }
void lorenz::modifyR(double d) { this->r += d; }
double lorenz::getS() { return this->s; }
double lorenz::getB() { return this->b; }
double lorenz::getR() { return this->r; }
void lorenz::resetParameters() {
    this->s = 10;
    this->b = 2.6666;
    this->r = 28;
    this->iterations = 50000;
}
void lorenz::modifyIterations(int i) {
    if (this->iterations + i < 0) this->iterations = 0;
    else this->iterations += i;
}
int lorenz::getIterations() { return this->iterations; }