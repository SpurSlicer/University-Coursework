#include "pyramid.h"

pyramid::pyramid() {
    // Colors
    initStyles();
    //Front
    this->coords.push_back(new coordinate({-1.0,0.0, 1.0}));
    this->coords.push_back(new coordinate({-1.0,0.0, -1.0}));
    this->coords.push_back(new coordinate({0.0,1.0, 0.0}));
    
    this->coords.push_back(new coordinate({-1.0,0.0, -1.0}));
    this->coords.push_back(new coordinate({1.0,0.0, -1.0}));
    this->coords.push_back(new coordinate({0.0,1.0, 0.0}));
    
    this->coords.push_back(new coordinate({1.0,0.0, -1.0}));
    this->coords.push_back(new coordinate({1.0,0.0, 1.0}));
    this->coords.push_back(new coordinate({0.0,1.0, 0.0}));
    
    this->coords.push_back(new coordinate({1.0,0.0, 1.0}));
    this->coords.push_back(new coordinate({-1.0,0.0, 1.0}));
    this->coords.push_back(new coordinate({0.0,1.0, 0.0}));

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
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D,this->texs->getTextureId("_sand.bmp"));

    coordinate* minus_y_normal = getGenericNormal(MINUS_Y);
    for (int i = 0; i < num_coords; i++) {
        if (i % 3 == 0) {
            if (i != 0) glEnd();
        }
        glColor3f(1.0, 1.0, 1.0);
        switch (s) {
            case PYRAMID_SAND:
                //glColor3f(this->colors.at(s).at(0)->x, this->colors.at(s).at(0)->y, this->colors.at(s).at(0)->z);
                if (i%3 == 0) glBindTexture(GL_TEXTURE_2D,this->texs->getTextureId("_sand.bmp"));
                break;
            case PYRAMID_GRASS:
                //glColor3f(this->colors.at(s).at(0)->x, this->colors.at(s).at(0)->y, this->colors.at(s).at(0)->z);
                if (i%3 == 0) glBindTexture(GL_TEXTURE_2D,this->texs->getTextureId("_grass.bmp"));
                break;
            case PYRAMID_ROOF:
                //glColor3f(this->colors.at(s).at(0)->x, this->colors.at(s).at(0)->y, this->colors.at(s).at(0)->z);
                if (i%3 == 0) glBindTexture(GL_TEXTURE_2D,this->texs->getTextureId("_roof.bmp"));
                break;
            default:
                //glColor3f(this->colors.at(s).at(normal_cnt)->x, this->colors.at(s).at(normal_cnt)->y, this->colors.at(s).at(normal_cnt)->z);
                if (i%3 == 0) glBindTexture(GL_TEXTURE_2D,this->texs->getTextureId("_rocks.bmp"));
        }

        if (i % 3 == 0) {
            glBegin(GL_POLYGON);
            glNormal3f(-this->normals.at(normal_cnt)->x, -this->normals.at(normal_cnt)->y, -this->normals.at(normal_cnt)->z);
            normal_cnt++;
        }
        if (i % 3 == 0) {
            glTexCoord2f(0,0);
        } else if (i % 3 == 1) {
            glTexCoord2f(scale.x/2,0);
        } else if (i % 3 == 2) {
            glTexCoord2f(scale.x/4,scale.x/2);
        }
        glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
    }
    glEnd();
    switch (s) {
        case PYRAMID_SAND:
            glColor3f(this->colors.at(s).at(1)->x, this->colors.at(s).at(1)->y, this->colors.at(s).at(1)->z);
            break;
        case PYRAMID_GRASS:
            glColor3f(this->colors.at(s).at(0)->x, this->colors.at(s).at(0)->y, this->colors.at(s).at(0)->z);
            break;
        case PYRAMID_ROOF:
            glColor3f(this->colors.at(s).at(1)->x, this->colors.at(s).at(1)->y, this->colors.at(s).at(1)->z);
            break;
        default:
            glColor3f(this->colors.at(s).at(normal_cnt)->x, this->colors.at(s).at(normal_cnt)->y, this->colors.at(s).at(normal_cnt)->z);
    }
    glBindTexture(GL_TEXTURE_2D,this->texs->getTextureId("_rocks.bmp"));
    glBegin(GL_POLYGON);
    glNormal3f(minus_y_normal->x, minus_y_normal->y, minus_y_normal->z);
    for (int i = 0; i < num_coords; i+=3) {
        if (i % 4 == 0) {
            glTexCoord2f(0,0);
        } else if (i % 4 == 1) {
            glTexCoord2f(scale.x/2,0);
        } else if (i % 4 == 2) {
            glTexCoord2f(scale.x/2,scale.x/2);
        } else if (i % 4 == 3) {
            glTexCoord2f(0,scale.x/2);
        }
        glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
    }
    glEnd();
    //  Undo transformations
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}