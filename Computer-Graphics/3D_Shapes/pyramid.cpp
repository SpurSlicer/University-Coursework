#include "pyramid.h"

pyramid::pyramid() {
    // Colors
    initStyles();
    //Front
    this->coords.push_back(new coordinate({0.0,1.0, 0.0}));
    this->coords.push_back(new coordinate({1,0.0, -1.0}));
    this->coords.push_back(new coordinate({-1.0,0.0, -1.0}));
    this->coords.push_back(new coordinate({-1.0,0.0, 1.0}));
    this->coords.push_back(new coordinate({1.0,0.0, 1.0}));
    this->coords.push_back(new coordinate({1,0.0, -1.0}));
}

void pyramid::initStyles() {
    std::vector<color*> d; 
    d.push_back(new color({1.0, 0.0, 0.0}));
    d.push_back(new color({1.0, 1.0, 0.0}));
    d.push_back(new color({0.0, 1.0, 0.0}));
    d.push_back(new color({0.0, 1.0, 1.0}));
    d.push_back(new color({0.0, 0.0, 1.0}));
    d.push_back(new color({1.0, 0.0, 1.0}));
    this->colors.push_back(d);
    std::vector<color*> s;
    s.push_back(new color({1, 0.898, 0.098})); // yellow
    s.push_back(new color({0.639, 0.573, 0.051})); // darker yellow
    this->colors.push_back(s);
    std::vector<color*> g;
    g.push_back(new color({0.008, 0.902, 0.188})); // grass green
    this->colors.push_back(g);
    std::vector<color*> r;
    r.push_back(new color({0.529, 0.11, 0.027})); // roof red 
    r.push_back(new color({0.322, 0.071, 0.02})); // dark roof red 
    this->colors.push_back(r);
}

void pyramid::render(coordinate offset, coordinate scale, double th, pyramid_style s) {
   //  Save transformation
    glPushMatrix();
    //  Offset
    glTranslated(offset.x, offset.y, offset.z);
    glRotated(th,0,1,0);
    glScaled(scale.x,scale.y,scale.z);
    const int num_coords = this->coords.size();
    switch (s) {
        case PYRAMID_SAND:
            glBegin(GL_TRIANGLE_FAN);
            for (int i = 0; i < num_coords; i++) {
                if (i == 0) glColor3f(this->colors.at(s).at(1)->x, this->colors.at(s).at(1)->y, this->colors.at(s).at(1)->z);
                else glColor3f(this->colors.at(s).at(1)->x, this->colors.at(s).at(1)->y, this->colors.at(s).at(1)->z);
                glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
            }
            glEnd();
            glBegin(GL_POLYGON);
            for (int i = 1; i < (num_coords-1); i++)
                glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
            glEnd();
            break;
        case PYRAMID_GRASS:
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(this->colors.at(s).at(0)->x, this->colors.at(s).at(0)->y, this->colors.at(s).at(0)->z);
            for (int i = 0; i < num_coords; i++)
                glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
            glEnd();
            glBegin(GL_POLYGON);
            for (int i = 1; i < (num_coords-1); i++)
                glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
            glEnd();
            break;
        case PYRAMID_ROOF:
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(this->colors.at(s).at(0)->x, this->colors.at(s).at(0)->y, this->colors.at(s).at(0)->z);
            for (int i = 0; i < num_coords; i++)
                glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
            glEnd();
            glBegin(GL_POLYGON);
            glColor3f(this->colors.at(s).at(1)->x, this->colors.at(s).at(1)->y, this->colors.at(s).at(1)->z);
            for (int i = 1; i < (num_coords-1); i++)
                glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
            glEnd();
            break;
        default:
            glBegin(GL_TRIANGLE_FAN);
            for (int i = 0; i < num_coords; i++) {
                glColor3f(this->colors.at(s).at(i)->x, this->colors.at(s).at(i)->y, this->colors.at(s).at(i)->z);
                glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
            }
            glEnd();
            glBegin(GL_POLYGON);
            for (int i = 1; i < (num_coords-1); i++) {
                glColor3f(this->colors.at(s).at(i)->x, this->colors.at(s).at(i)->y, this->colors.at(s).at(i)->z);
                glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
            }
            glEnd();
    }
    //  Undo transformations
    glPopMatrix();
}