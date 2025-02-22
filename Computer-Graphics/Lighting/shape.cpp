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

void shape::generateNormalByTriangle(std::vector<coordinate*> v, int start) {
    coordinate* cross_product = new coordinate({0, 0, 0});
    //printf("AVERAGE - x: %f, y: %f, z: %f of size %d\n", vector->x, vector->y, vector->z, size);
    coordinate* vector_u = new coordinate({v.at(start+1)->x-v.at(start)->x, v.at(start+1)->y-v.at(start)->y, v.at(start+1)->z-v.at(start)->z});
    coordinate* vector_v = new coordinate({v.at(start+2)->x-v.at(start)->x, v.at(start+2)->y-v.at(start)->y, v.at(start+2)->z-v.at(start)->z});
    cross_product->x = vector_u->y*vector_v->z - vector_u->z*vector_v->y;
    cross_product->y = vector_u->z*vector_v->x - vector_u->x*vector_v->z;
    cross_product->z = vector_u->x*vector_v->y - vector_u->y*vector_v->x;
    //printf("NORMAL - x: %f, y: %f, z: %f\n", cross_product->x, cross_product->y, cross_product->z);
    delete vector_u;
    delete vector_v;
    this->normals.push_back(cross_product);
}
void shape::generateNormalBySquare(std::vector<coordinate*> v, int start, bool flip) {
    coordinate* cross_product = new coordinate({0, 0, 0});
    coordinate* vector_u = new coordinate({v.at(start+2)->x-v.at(start)->x, v.at(start+2)->y-v.at(start)->y, v.at(start+2)->z-v.at(start)->z});
    coordinate* vector_v = new coordinate({v.at(start+3)->x-v.at(start+1)->x, v.at(start+3)->y-v.at(start+1)->y, v.at(start+3)->z-v.at(start+1)->z});
    //printf("AVERAGE - x: %f, y: %f, z: %f of size %d\n", vector->x, vector->y, vector->z, size);
    if (true /*flip*/) {
        cross_product->x = vector_u->y*vector_v->z - vector_u->z*vector_v->y;
        cross_product->y = vector_u->z*vector_v->x - vector_u->x*vector_v->z;
        cross_product->z = vector_u->x*vector_v->y - vector_u->y*vector_v->x;
    }
    //printf("NORMAL - x: %f, y: %f, z: %f\n", cross_product->x, cross_product->y, cross_product->z);
    delete vector_u;
    delete vector_v;
    this->normals.push_back(cross_product);
}

void shape::activateSmoothness() {
   glShadeModel(GL_SMOOTH);
    return;
}

void shape::deactivateSmoothness() {
    glShadeModel(GL_FLAT);
}

void shape::deactivateLighting() {
    glDisable(GL_LIGHTING);
}

float shape::getAmbient() { return this->ambient; }
float shape::getDiffuse() { return this->diffuse; }
float shape::getSpecular() { return this->specular; }
int shape::getLocal() { return this->local; }
bool shape::isLightingEnabled() { return this->light; }
void shape::setLightingEnabled(bool light) { this->light = light; };

coordinate* shape::getGenericNormal(generic_lighting_state g) {
    switch (g) {
        case PLUS_X:
            return new coordinate({+1, 0, 0});
        case MINUS_X:
            return new coordinate({-1, 0, 0});
        case PLUS_Y:
            return new coordinate({0, +1, 0});
        case MINUS_Y:
            return new coordinate({0, -1, 0});
        case PLUS_Z:
            return new coordinate({0, 0, 1});
        case MINUS_Z:
            return new coordinate({0, 0, -1});
        default:
            return nullptr;
    }
}

void shape::updateZh(double t) {
    this->zh = fmod(90*t, 360.0);
}

double shape::getZh() { return this->zh; }