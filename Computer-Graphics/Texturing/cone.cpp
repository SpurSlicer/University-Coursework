#include "cone.h"

cone::cone(double sides) {
    initStyles();
    this->sides = sides+1;
    //  Latitude bands
    const float factor = 360 / sides;
    //this->coords.push_back(new coordinate({0.0, 0.0, 0.0}));
    for (double a = 0; a < 360;) {
        this->coords.push_back(new coordinate({0.0, 0.0, 0.0}));
        this->coords.push_back(new coordinate({Cos(a), 1.0, Sin(a)}));
        a += factor;
        this->coords.push_back(new coordinate({Cos(a), 1.0, Sin(a)}));
    }
    const int coords_size = this->coords.size();
    for (int i = 0; i < coords_size; i += 3) {
        this->generateNormalByTriangle(this->coords, i);
    }
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
    // Lighting
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->WHITE);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,this->BLACK);
    //  Save transformation
    glPushMatrix();
    //  Offset and scale
    glRotated(th,0,1,0);
    glTranslated(offset.x, offset.y,offset.z);
    glScaled(scale.x,scale.y,scale.z);
    const int body_number = this->coords.size() - (this->sides);
    int normal_cnt = 0;
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D,this->texs->getTextureId("_dirt.bmp"));
    for (int i = 0; i < body_number; i++) {
        if (i % 3 == 0) {
            if (i != 0) glEnd();
            glColor3f(1.0, 1.0, 1.0);
            //glColor3f(this->colors.at(0).at(1)->x, this->colors.at(0).at(1)->y, this->colors.at(0).at(1)->z);
            glBindTexture(GL_TEXTURE_2D,this->texs->getTextureId("_dirt.bmp"));
            glBegin(GL_POLYGON);
            glNormal3f(this->normals.at(normal_cnt)->x, this->normals.at(normal_cnt)->y, this->normals.at(normal_cnt)->z);
            normal_cnt++;
        }
        if (i % 3 == 0) {
            glTexCoord2f(scale.x/4,scale.x/2);
        } else if (i % 3 == 1) {
            glTexCoord2f(scale.x/2,0);
        } else if (i % 3 == 2) {
            glTexCoord2f(0,0);
        }
        //glNormal3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
        glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
    }
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(this->colors.at(0).at(0)->x, this->colors.at(0).at(0)->y, this->colors.at(0).at(0)->z);
    coordinate* plus_y_normal = this->getGenericNormal(PLUS_Y);
    glNormal3f(plus_y_normal->x, plus_y_normal->y, plus_y_normal->z);
    delete plus_y_normal;
    for (int i = body_number; i < body_number + this->sides; i++)
        glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
    glEnd();
   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}