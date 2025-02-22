#include "sphere.h"

sphere::sphere() {
    initStyles();
    //  Latitude bands
    for (int ph = -90; ph < 90; ph += this->d) {
        for (int th=0;th<=360;th+=this->d) {
            this->coords.push_back(this->sphericalCoord(th,ph));
            this->coords.push_back(this->sphericalCoord(th,ph+d));
        }
        glEnd();
    }
}

void sphere::initStyles() {
    std::vector<color*> m;
    m.push_back(new color({0.875, 0.988, 0.988})); // moon blue
    this->colors.push_back(m);
    std::vector<color*> t;
    t.push_back(new color({0.071, 0.451, 0.02})); // forest green
    this->colors.push_back(t);

}
/*
 *  Draw a sphere (version 2)
 *     at (x,y,z)
 *     radius (r)
 */
void sphere::render(coordinate offset, double r, sphere_style s) {
    // Lighting
    if (s == SPHERE_MOON) {
        glMaterialf(GL_FRONT,GL_SHININESS,this->shiny);
        glMaterialfv(GL_FRONT,GL_SPECULAR,this->YELLOW);
        glMaterialfv(GL_FRONT,GL_EMISSION,this->EMISSION);
    } else {
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->shiny);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->WHITE);
        glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,this->BLACK);
    }
    //  Save transformation
    glPushMatrix();
    //  Offset and scale
    glTranslated(offset.x, offset.y,offset.z);
    glScaled(r,r,r);
    int cnt = 0;
    //  Latitude bands
    switch (s) {
        case SPHERE_MOON: 
            glColor3f(this->colors.at(s-1).at(0)->x, this->colors.at(s-1).at(0)->y, this->colors.at(s-1).at(0)->z);
            for (int ph=-90;ph<90;ph+=this->d) {
                glBegin(GL_QUAD_STRIP);
                for (int th=0;th<=360;th+=this->d) {
                    coordinate* temp_coord = this->coords.at(cnt);
                    glNormal3f(temp_coord->x, temp_coord->y, temp_coord->z);
                    glVertex3f(temp_coord->x, temp_coord->y, temp_coord->z);
                    cnt++;
                    temp_coord = this->coords.at(cnt);
                    glNormal3f(temp_coord->x, temp_coord->y, temp_coord->z);
                    glVertex3f(temp_coord->x, temp_coord->y, temp_coord->z);
                    cnt++;
                }
                glEnd();
            }
            break;
        case SPHERE_TREE: 
            glColor3f(this->colors.at(s-1).at(0)->x, this->colors.at(s-1).at(0)->y, this->colors.at(s-1).at(0)->z);
            for (int ph=-90;ph<90;ph+=this->d) {
                glBegin(GL_QUAD_STRIP);
                for (int th=0;th<=360;th+=this->d) {
                    coordinate* temp_coord = this->coords.at(cnt);
                    glNormal3f(temp_coord->x, temp_coord->y, temp_coord->z);
                    glVertex3f(temp_coord->x, temp_coord->y, temp_coord->z);
                    cnt++;
                    temp_coord = this->coords.at(cnt);
                    glNormal3f(temp_coord->x, temp_coord->y, temp_coord->z);
                    glVertex3f(temp_coord->x, temp_coord->y, temp_coord->z);
                    cnt++;
                }
                glEnd();
            }
            break;
        default:
            for (int ph=-90;ph<90;ph+=this->d) {
                glBegin(GL_QUAD_STRIP);
                for (int th=0;th<=360;th+=this->d) {
                    coordinate* temp_coord = this->coords.at(cnt);
                    glColor3f(Cos(th)*Cos(th) , Sin(ph)*Sin(ph) , Sin(th)*Sin(th));
                    glNormal3f(temp_coord->x, temp_coord->y, temp_coord->z);
                    glVertex3f(temp_coord->x, temp_coord->y, temp_coord->z);
                    cnt++;
                    temp_coord = this->coords.at(cnt);
                    glColor3f(Cos(th)*Cos(th) , Sin(ph+this->d)*Sin(ph) , Sin(th)*Sin(th));
                    glNormal3f(temp_coord->x, temp_coord->y, temp_coord->z);
                    glVertex3f(temp_coord->x, temp_coord->y, temp_coord->z);
                    cnt++;
                }
                glEnd();
            }
    }
   //  Undo transformations
   glPopMatrix();
}

/*
 *  Draw a sphere (version 1)
 *     at (x,y,z)
 *     radius (r)
 *
static void sphere1(double x,double y,double z,double r)
{
   const int d=15;

   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
   glScaled(r,r,r);

   //  South pole cap
   glBegin(GL_TRIANGLE_FAN);
   Vertex(0,-90);
   for (int th=0;th<=360;th+=d)
   {
      Vertex(th,d-90);
   }
   glEnd();

   //  Latitude bands
   for (int ph=d-90;ph<=90-2*d;ph+=d)
   {
      glBegin(GL_QUAD_STRIP);
      for (int th=0;th<=360;th+=d)
      {
         Vertex(th,ph);
         Vertex(th,ph+d);
      }
      glEnd();
   }

   //  North pole cap
   glBegin(GL_TRIANGLE_FAN);
   Vertex(0,90);
   for (int th=0;th<=360;th+=d)
   {
      Vertex(th,90-d);
   }
   glEnd();

   //  Undo transformations
   glPopMatrix();
}
*/