#include "cone.h"

cone::cone(double sides) {
    initStyles();
    this->sides = sides+1;
    //  Latitude bands
    const float factor = 360 / sides;
        this->coords.push_back(new coordinate({0.0, 0.0, 0.0}));
    for (double a = 0; a <= 360; a += factor)
        this->coords.push_back(new coordinate({Cos(a), 1.0, Sin(a)}));
    for (double a = 0; a <= 360; a += factor)
        this->coords.push_back(new coordinate({Cos(a), 1.0, Sin(a)}));
}

void cone::initStyles() {
    std::vector<color*> e;
    e.push_back(new color({0.239, 0.141, 0})); //  brown
    e.push_back(new color({0.149, 0.086, 0})); // dark brown
    this->colors.push_back(e);
}
/*
 *  Draw a sphere (version 2)
 *     at (x,y,z)
 *     radius (r)
 */
void cone::render(coordinate offset, coordinate scale, double th, cone_style s) {
    //  Save transformation
    glPushMatrix();
    //  Offset and scale
    glRotated(th,0,1,0);
    glTranslated(offset.x, offset.y,offset.z);
    glScaled(scale.x,scale.y,scale.z);
    const int body_number = this->coords.size() - (this->sides);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(this->colors.at(0).at(1)->x, this->colors.at(0).at(1)->y, this->colors.at(0).at(1)->z);
    for (int i = 0; i < body_number; i++) {
        glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
    }
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(this->colors.at(0).at(0)->x, this->colors.at(0).at(0)->y, this->colors.at(0).at(0)->z);
    for (int i = body_number; i < body_number + this->sides; i++)
        glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
    glEnd();
   //  Undo transformations
   glPopMatrix();
}