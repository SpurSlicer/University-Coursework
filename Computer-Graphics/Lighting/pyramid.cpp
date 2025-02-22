#include "pyramid.h"

pyramid::pyramid() {
    // Colors
    initStyles();
    //Front
    this->coords.push_back(new coordinate({-1.0,0.0, 1.0}));
    this->coords.push_back(new coordinate({0.0,1.0, 0.0}));
    this->coords.push_back(new coordinate({-1.0,0.0, -1.0}));
    
    this->coords.push_back(new coordinate({-1.0,0.0, -1.0}));
    this->coords.push_back(new coordinate({0.0,1.0, 0.0}));
    this->coords.push_back(new coordinate({1.0,0.0, -1.0}));
    
    this->coords.push_back(new coordinate({1.0,0.0, -1.0}));
    this->coords.push_back(new coordinate({0.0,1.0, 0.0}));
    this->coords.push_back(new coordinate({1.0,0.0, 1.0}));
    
    this->coords.push_back(new coordinate({1.0,0.0, 1.0}));
    this->coords.push_back(new coordinate({0.0, 1.0, 0.0}));
    this->coords.push_back(new coordinate({-1.0,0.0, 1.0}));

    const int normal_cnt = this->coords.size();
    for (int i = 0; i < normal_cnt; i += 3)
        this->generateNormalByTriangle(this->coords, i);
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
    // Lighting
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->WHITE);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,this->BLACK);
    // Save transformation
    glPushMatrix();
    //  Offset
    glTranslated(offset.x, offset.y, offset.z);
    glRotated(th,0,1,0);
    glScaled(scale.x,scale.y,scale.z);
    const int num_coords = this->coords.size();
    int normal_cnt = 0;
    coordinate* minus_y_normal = getGenericNormal(MINUS_Y);
    switch (s) {
        case PYRAMID_SAND:
            glBegin(GL_POLYGON);
            for (int i = 0; i < num_coords; i++) {
                if (i % 3 == 0) {
                    glEnd();
                    glBegin(GL_POLYGON);
                    glColor3f(this->colors.at(s).at(1)->x, this->colors.at(s).at(1)->y, this->colors.at(s).at(1)->z);
                    glNormal3f(this->normals.at(normal_cnt)->x, this->normals.at(normal_cnt)->y, this->normals.at(normal_cnt)->z);
                    normal_cnt++;
                } else glColor3f(this->colors.at(s).at(1)->x, this->colors.at(s).at(1)->y, this->colors.at(s).at(1)->z);
                glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
            }
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(minus_y_normal->x, minus_y_normal->y, minus_y_normal->z);
            for (int i = 0; i < num_coords; i += 3)
                glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
            glEnd();
            break;
        case PYRAMID_GRASS:
            glBegin(GL_POLYGON);
            for (int i = 0; i < num_coords; i++) {
                if (i % 3 == 0) {
                    glEnd();
                    glBegin(GL_POLYGON);
                    glColor3f(this->colors.at(s).at(0)->x, this->colors.at(s).at(0)->y, this->colors.at(s).at(0)->z);
                    glNormal3f(this->normals.at(normal_cnt)->x, this->normals.at(normal_cnt)->y, this->normals.at(normal_cnt)->z);
                    normal_cnt++;
                }
                glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
            }
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(minus_y_normal->x, minus_y_normal->y, minus_y_normal->z);
            for (int i = 0; i < num_coords; i += 3)
                glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
            glEnd();
            break;
        case PYRAMID_ROOF:
            glBegin(GL_POLYGON);
            for (int i = 0; i < num_coords; i++) {
                if (i % 3 == 0) {
                    glEnd();
                    glBegin(GL_POLYGON);
                    glColor3f(this->colors.at(s).at(0)->x, this->colors.at(s).at(0)->y, this->colors.at(s).at(0)->z);
                    glNormal3f(this->normals.at(normal_cnt)->x, this->normals.at(normal_cnt)->y, this->normals.at(normal_cnt)->z);
                    normal_cnt++;
                }
                glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
            }
            glEnd();
            glBegin(GL_POLYGON);
            glColor3f(this->colors.at(s).at(1)->x, this->colors.at(s).at(1)->y, this->colors.at(s).at(1)->z);
            glNormal3f(minus_y_normal->x, minus_y_normal->y, minus_y_normal->z);
            for (int i = 0; i < num_coords; i += 3)
                glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
            glEnd();
            break;
        default:
            glBegin(GL_POLYGON);
            for (int i = 0; i < num_coords; i++) {
                if (i % 3 == 0) {
                    glEnd();
                    glBegin(GL_POLYGON);
                    glColor3f(this->colors.at(s).at(normal_cnt)->x, this->colors.at(s).at(normal_cnt)->y, this->colors.at(s).at(normal_cnt)->z);
                    glNormal3f(this->normals.at(normal_cnt)->x, this->normals.at(normal_cnt)->y, this->normals.at(normal_cnt)->z);
                    normal_cnt++;
                }
                glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
            }
            glEnd();
            glBegin(GL_POLYGON);
            glNormal3f(minus_y_normal->x, minus_y_normal->y, minus_y_normal->z);
            for (int i = 0; i < num_coords; i += 3) {
                glColor3f(this->colors.at(s).at(i)->x, this->colors.at(s).at(i)->y, this->colors.at(s).at(i)->z);
                glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
            }
            glEnd();
    }
    //  Undo transformations
    glPopMatrix();
}