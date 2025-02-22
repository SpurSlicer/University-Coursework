#include "outpost.h"

outpost::outpost(double sides) {
    initStyles();
    this->sides = sides+1;
    //  Latitude bands
    const float factor = 360 / sides;
    float multiplier_1 = 4.0, multiplier_2 = 4.0;
    for (double a = 0; a <= 360; a += factor) {
        this->coords.push_back(new coordinate({multiplier_1 * Cos(a), 0, multiplier_1 * Sin(a)}));
        this->coords.push_back(new coordinate({multiplier_2 * Cos(a), 3, multiplier_2 * Sin(a)}));
    }
    multiplier_2 = 2.0;
    for (double a = 0; a <= 360; a += factor) {
        this->coords.push_back(new coordinate({multiplier_1 * Cos(a), 3, multiplier_1 * Sin(a)}));
        this->coords.push_back(new coordinate({multiplier_2 * Cos(a), 4.0, multiplier_2 * Sin(a)}));

    }
    multiplier_1 = 2.0;
    for (double a = 0; a <= 360; a += factor) {
        this->coords.push_back(new coordinate({multiplier_1 * Cos(a), 4.0, multiplier_1 * Sin(a)}));
        this->coords.push_back(new coordinate({multiplier_2 * Cos(a), 6.0, multiplier_2 * Sin(a)}));
    }
    multiplier_2 = 4.0;
    for (double a = 0; a <= 360; a += factor) {
        this->coords.push_back(new coordinate({multiplier_1 * Cos(a), 6.0, multiplier_1 * Sin(a)}));
        this->coords.push_back(new coordinate({multiplier_2 * Cos(a), 7.0, multiplier_2 * Sin(a)}));
    }
    for (double a = 0; a <= 360; a += factor)
        this->coords.push_back(new coordinate({multiplier_2 * Cos(a), 7.0, multiplier_2 * Sin(a)}));
    multiplier_1 = 4.0;
    multiplier_2 = 3.0;
    int cnt = 0, height = 2;
    for (double a = 0; a < 360; a += factor) {
        if (cnt % 2 == 0) height = 3;
        else height = 2;
        this->alt_coords.push_back(new coordinate({multiplier_1 * Cos(a), 7.0, multiplier_1 * Sin(a)}));
        this->alt_coords.push_back(new coordinate({multiplier_1 * Cos(a), 7.0+height, multiplier_1 * Sin(a)}));
        a += factor;
        this->alt_coords.push_back(new coordinate({multiplier_1 * Cos(a), 7.0+height, multiplier_1 * Sin(a)}));
        this->alt_coords.push_back(new coordinate({multiplier_1 * Cos(a), 7.0, multiplier_1 * Sin(a)}));

        this->alt_coords.push_back(new coordinate({multiplier_1 * Cos(a), 7.0, multiplier_1 * Sin(a)}));
        this->alt_coords.push_back(new coordinate({multiplier_1 * Cos(a), 7.0+height, multiplier_1 * Sin(a)}));
        this->alt_coords.push_back(new coordinate({multiplier_2 * Cos(a), 7.0+height, multiplier_2 * Sin(a)}));
        this->alt_coords.push_back(new coordinate({multiplier_2 * Cos(a), 7.0, multiplier_2 * Sin(a)}));

        this->alt_coords.push_back(new coordinate({multiplier_2 * Cos(a), 7.0, multiplier_2 * Sin(a)}));
        this->alt_coords.push_back(new coordinate({multiplier_2 * Cos(a), 7.0+height, multiplier_2 * Sin(a)}));
        a -= factor;
        this->alt_coords.push_back(new coordinate({multiplier_2 * Cos(a), 7.0+height, multiplier_2 * Sin(a)}));
        this->alt_coords.push_back(new coordinate({multiplier_2 * Cos(a), 7.0, multiplier_2 * Sin(a)}));

        this->alt_coords.push_back(new coordinate({multiplier_2 * Cos(a), 7.0, multiplier_2 * Sin(a)}));
        this->alt_coords.push_back(new coordinate({multiplier_2 * Cos(a), 7.0+height, multiplier_2 * Sin(a)}));
        this->alt_coords.push_back(new coordinate({multiplier_1 * Cos(a), 7.0+height, multiplier_1 * Sin(a)}));
        this->alt_coords.push_back(new coordinate({multiplier_1 * Cos(a), 7.0, multiplier_1 * Sin(a)}));

        this->alt_coords.push_back(new coordinate({multiplier_1 * Cos(a), 7.0+height, multiplier_1 * Sin(a)}));
        a += factor;
        this->alt_coords.push_back(new coordinate({multiplier_1 * Cos(a), 7.0+height, multiplier_1 * Sin(a)}));
        this->alt_coords.push_back(new coordinate({multiplier_2 * Cos(a), 7.0+height, multiplier_2 * Sin(a)}));
        a -= factor;
        this->alt_coords.push_back(new coordinate({multiplier_2 * Cos(a), 7.0+height, multiplier_2 * Sin(a)}));

                this->alt_coords.push_back(new coordinate({multiplier_1 * Cos(a), 7.0, multiplier_1 * Sin(a)}));
        a += factor;
        this->alt_coords.push_back(new coordinate({multiplier_1 * Cos(a), 7.0, multiplier_1 * Sin(a)}));
        this->alt_coords.push_back(new coordinate({multiplier_2 * Cos(a), 7.0, multiplier_2 * Sin(a)}));
        a -= factor;
        this->alt_coords.push_back(new coordinate({multiplier_2 * Cos(a), 7.0, multiplier_2 * Sin(a)}));
        cnt++;
    }
}

void outpost::initStyles() {
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
void outpost::render(coordinate offset, coordinate scale, outpost_style s, bool lined_posts) {
    //  Save transformation
    glPushMatrix();
    //  Offset and scale
    glTranslated(offset.x, offset.y,offset.z);
    glScaled(scale.x,scale.y,scale.z);
    const int body_number = this->coords.size() - (this->sides), strip_number = body_number / 4;
    for (int off = 0; off < (body_number-1); off += strip_number) {
        glPolygonOffset(3,3);
        glBegin(GL_QUAD_STRIP);
        glColor3f(this->colors.at(s).at(0)->x, this->colors.at(s).at(0)->y, this->colors.at(s).at(0)->z);
        for (int i = 0; i < strip_number; i++) {
            glVertex3f(this->coords.at(i+off)->x, this->coords.at(i+off)->y, this->coords.at(i+off)->z);
        }
        glEnd();
        if (lined_posts) {
            glPolygonOffset(1,1);
            glBegin(GL_LINES);
            glColor3f(0.0, 0.0, 0.0);
            for (int i = 0; i < strip_number; i++) {
                glVertex3f(this->coords.at(i+off)->x, this->coords.at(i+off)->y, this->coords.at(i+off)->z);
            }
            glEnd();
            glBegin(GL_LINES);
            glColor3f(0.0, 0.0, 0.0);
            for (int i = 0; i+2 < strip_number;) {
                glVertex3f(this->coords.at(i+off)->x, this->coords.at(i+off)->y, this->coords.at(i+off)->z);
                i+=2;
                glVertex3f(this->coords.at(i+off)->x, this->coords.at(i+off)->y, this->coords.at(i+off)->z);
            }
            glEnd();
        }
    }
    glBegin(GL_POLYGON);
    glColor3f(this->colors.at(s).at(0)->x, this->colors.at(s).at(0)->y, this->colors.at(s).at(0)->z);
    for (int i = body_number; i < body_number + this->sides; i++) {
        glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
    }
    glEnd();
    const int num_cube_vertices = this->alt_coords.size();
    for (int off = 0; off < num_cube_vertices; off += 4*6) {
        glBegin(GL_QUADS);
        glColor3f(this->colors.at(s).at(0)->x, this->colors.at(s).at(0)->y, this->colors.at(s).at(0)->z);
        for (int i = 0; i < 4*6; i++) {
            if (i == 8) glColor3f(this->colors.at(s).at(1)->x, this->colors.at(s).at(1)->y, this->colors.at(s).at(1)->z);
            else if (i == 12) glColor3f(this->colors.at(s).at(0)->x, this->colors.at(s).at(0)->y, this->colors.at(s).at(0)->z);
            glVertex3f(this->alt_coords.at(i+off)->x, this->alt_coords.at(i+off)->y, this->alt_coords.at(i+off)->z);
        }
        glEnd();
        if (lined_posts) {
         for (int i = 0; i < 6*4; i += 4) {
            glPolygonOffset(1,1);
            glBegin(GL_LINES);
            glColor3f(0.0, 0.0, 0.0);
            glVertex3f(this->alt_coords.at(i+off)->x, this->alt_coords.at(i+off)->y, this->alt_coords.at(i+off)->z);
            i++;
            glVertex3f(this->alt_coords.at(i+off)->x, this->alt_coords.at(i+off)->y, this->alt_coords.at(i+off)->z);
            glVertex3f(this->alt_coords.at(i+off)->x, this->alt_coords.at(i+off)->y, this->alt_coords.at(i+off)->z);
            i++;
            glVertex3f(this->alt_coords.at(i+off)->x, this->alt_coords.at(i+off)->y, this->alt_coords.at(i+off)->z);
            glVertex3f(this->alt_coords.at(i+off)->x, this->alt_coords.at(i+off)->y, this->alt_coords.at(i+off)->z);
            i++;
            glVertex3f(this->alt_coords.at(i+off)->x, this->alt_coords.at(i+off)->y, this->alt_coords.at(i+off)->z);
            glVertex3f(this->alt_coords.at(i+off)->x, this->alt_coords.at(i+off)->y, this->alt_coords.at(i+off)->z);
            i -= 3;
            glVertex3f(this->alt_coords.at(i+off)->x, this->alt_coords.at(i+off)->y, this->alt_coords.at(i+off)->z);
            glEnd();
         }
        }
    }
   //  Undo transformations
   glPopMatrix();
}