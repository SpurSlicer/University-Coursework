#include "cylinder.h"

cylinder::cylinder(double sides) {
    initStyles();
    this->sides = sides+1;
    //  Latitude bands
    const float factor = 360 / sides;
    for (double a = 0; a <= 360; a += factor) {
        this->coords.push_back(new coordinate({Cos(a), 0, Sin(a)}));
        this->coords.push_back(new coordinate({Cos(a), 1, Sin(a)}));
    }
    for (double a = 0; a <= 360; a += factor)
        this->coords.push_back(new coordinate({Cos(a), 0, Sin(a)}));
    for (double a = 0; a <= 360; a += factor)
        this->coords.push_back(new coordinate({Cos(a), 1, Sin(a)}));
}

void cylinder::initStyles() {
    std::vector<color*> e;
    e.push_back(new color({0.4, 0.4, 0.4})); // gray
    e.push_back(new color({0.231, 0.227, 0.227})); // gray
    this->colors.push_back(e);
}
/*
 *  Draw a sphere (version 2)
 *     at (x,y,z)
 *     radius (r)
 */
void cylinder::render(coordinate offset, coordinate scale, cylinder_type t, cylinder_style s) {
    //  Save transformation
    glPushMatrix();
    //  Offset and scale
    if (t == FLIP_V) glTranslated(offset.x, offset.y, offset.z - (scale.y / 2));
    else if (t == FLIP_H_V) glTranslated(offset.x - (scale.y / 2), offset.y, offset.z);
    else glTranslated(offset.x, offset.y,offset.z);
    if (t == FLIP_V) glScaled(scale.x,scale.z,scale.y);
    else if (t == FLIP_H_V) glScaled(scale.y,scale.z,scale.x);
    else glScaled(scale.x,scale.y,scale.z);
    const int body_number = this->coords.size() - (2 * this->sides);
    glBegin(GL_QUAD_STRIP);
    glColor3f(this->colors.at(s).at(0)->x, this->colors.at(s).at(0)->y, this->colors.at(s).at(0)->z);
    for (int i = 0; i < body_number; i++) {
        if (i % 3 == 0) glColor3f(this->colors.at(s).at(1)->x, this->colors.at(s).at(1)->y, this->colors.at(s).at(1)->z);
        else glColor3f(this->colors.at(s).at(0)->x, this->colors.at(s).at(0)->y, this->colors.at(s).at(0)->z);
        if (t == FLIP_V) glVertex3f(this->coords.at(i)->x, this->coords.at(i)->z, this->coords.at(i)->y);
        else if (t == FLIP_H_V) glVertex3f(this->coords.at(i)->y, this->coords.at(i)->z, this->coords.at(i)->x);
        else glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
    }
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(this->colors.at(s).at(1)->x, this->colors.at(s).at(1)->y, this->colors.at(s).at(1)->z);
    for (int i = body_number; i < body_number + this->sides; i++) {
        if (t == FLIP_V) glVertex3f(this->coords.at(i)->x, this->coords.at(i)->z, this->coords.at(i)->y);
        else if (t == FLIP_H_V) glVertex3f(this->coords.at(i)->y, this->coords.at(i)->z, this->coords.at(i)->x);
        else glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
    }
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(this->colors.at(s).at(1)->x, this->colors.at(s).at(1)->y, this->colors.at(s).at(1)->z);
    for (int i = body_number + this->sides; i < body_number + (this->sides * 2); i++) {
        if (t == FLIP_V) glVertex3f(this->coords.at(i)->x, this->coords.at(i)->z, this->coords.at(i)->y);
        else if (t == FLIP_H_V) glVertex3f(this->coords.at(i)->y, this->coords.at(i)->z, this->coords.at(i)->x);
        else glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
    }
    glEnd();
   //  Undo transformations
   glPopMatrix();
}