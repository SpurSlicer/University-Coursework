#include "cube.h"

cube::cube() {
   // Colors
   initStyles();
   //Front
   this->coords.push_back(new coordinate({-1,-1, 1}));
   this->coords.push_back(new coordinate({+1,-1, 1}));
   this->coords.push_back(new coordinate({+1,+1, 1}));
   this->coords.push_back(new coordinate({-1,+1, 1}));
   this->normals.push_back(this->getGenericNormal(PLUS_Z));
   //  Back
   this->coords.push_back(new coordinate({+1,-1,-1}));
   this->coords.push_back(new coordinate({-1,-1,-1}));
   this->coords.push_back(new coordinate({-1,+1,-1}));
   this->coords.push_back(new coordinate({+1,+1,-1}));
   this->normals.push_back(this->getGenericNormal(MINUS_Z));
   //  Right
   this->coords.push_back(new coordinate({+1,-1,+1}));
   this->coords.push_back(new coordinate({+1,-1,-1}));
   this->coords.push_back(new coordinate({+1,+1,-1}));
   this->coords.push_back(new coordinate({+1,+1,+1}));
   this->normals.push_back(this->getGenericNormal(PLUS_X));
   //  Left
   this->coords.push_back(new coordinate({-1,-1,-1}));
   this->coords.push_back(new coordinate({-1,-1,+1}));
   this->coords.push_back(new coordinate({-1,+1,+1}));
   this->coords.push_back(new coordinate({-1,+1,-1}));
   this->normals.push_back(this->getGenericNormal(MINUS_X));
   //  Top
   this->coords.push_back(new coordinate({-1,+1,+1}));
   this->coords.push_back(new coordinate({+1,+1,+1}));
   this->coords.push_back(new coordinate({+1,+1,-1}));
   this->coords.push_back(new coordinate({-1,+1,-1}));
   this->normals.push_back(this->getGenericNormal(PLUS_Y));
   //  Bottom
   this->coords.push_back(new coordinate({-1,-1,-1}));
   this->coords.push_back(new coordinate({+1,-1,-1}));
   this->coords.push_back(new coordinate({+1,-1,+1}));
   this->coords.push_back(new coordinate({-1,-1,+1}));
   this->normals.push_back(this->getGenericNormal(MINUS_Y));
}

void cube::initStyles() {
   std::vector<color*> d; 
   d.push_back(new color({1.0, 0.0, 0.0}));
   d.push_back(new color({1.0, 1.0, 0.0}));
   d.push_back(new color({0.0, 1.0, 0.0}));
   d.push_back(new color({0.0, 1.0, 1.0}));
   d.push_back(new color({0.0, 0.0, 1.0}));
   d.push_back(new color({1.0, 0.0, 1.0}));
   this->colors.push_back(d);
   std::vector<color*> g;
   g.push_back(new color({0.4, 0.239, 0.024})); // brown 
   g.push_back(new color({0.29, 0.173, 0.016})); // dark brown
   g.push_back(new color({0.008, 0.902, 0.188})); // grass green 
   g.push_back(new color({0.149, 0.086, 0})); // dark brown
   this->colors.push_back(g);
   std::vector<color*> w;
   w.push_back(new color({0, 0.729, 1})); // blue
   this->colors.push_back(w);
}

void cube::render(coordinate offset, coordinate scale, double th, cube_style s, bool lined_posts) {
   // Lighitng
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->WHITE);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,this->BLACK);
   //  Save transformation
   glPushMatrix();
   //  Offset
   glTranslated(offset.x, offset.y, offset.z);
   glRotated(th,0,1,0);
   glScaled(scale.x,scale.y,scale.z);
   int color_cnt = 0, color_index = 0, normal_cnt = 0;
   color* current_color = nullptr;
   //  Cube
   if (s == CUBE_WATER) glPolygonOffset(2,2);
   else glPolygonOffset(3, 3);
   if (s == CUBE_WATER) glBegin(GL_POLYGON);
   else glBegin(GL_QUADS);
   //  Front
   for (auto i : this->coords) {
      switch (s) {
         case CUBE_GROUND:
            if (color_cnt == 0) {
               current_color = this->colors.at(CUBE_GROUND).at(0);
               glColor3f(current_color->x, current_color->y, current_color->z);
            } else if (color_cnt == 8) {
               current_color = this->colors.at(CUBE_GROUND).at(1);
               glColor3f(current_color->x, current_color->y, current_color->z);
            } else if (color_cnt == 16) {
               current_color = this->colors.at(CUBE_GROUND).at(2);
               glColor3f(current_color->x, current_color->y, current_color->z);
            } else if (color_cnt == 20) {
               current_color = this->colors.at(CUBE_GROUND).at(3);
               glColor3f(current_color->x, current_color->y, current_color->z);
            }
            break;
         case CUBE_WATER:
               current_color = this->colors.at(CUBE_WATER).at(0);
               glColor3f(current_color->x, current_color->y, current_color->z);
               break;
         default:
            if (color_cnt % 4 == 0) {
               current_color = this->colors.at(CUBE_DEFAULT).at(color_index);
               glColor3f(current_color->x, current_color->y, current_color->z);
               color_index++;
            }
      }
      if (color_cnt % 4 == 0) {
         //std::cout << this->normals.at(normal_cnt)->x << this->normals.at(normal_cnt)->y << this->normals.at(normal_cnt)->z << std::endl;
         glNormal3f(this->normals.at(normal_cnt)->x, this->normals.at(normal_cnt)->y, this->normals.at(normal_cnt)->z);
         normal_cnt++;
      }
      if (s == CUBE_WATER) {
         if (color_cnt > 15 && color_cnt < 20) glVertex3f(i->x, i->y, i->z);   
      }
      else glVertex3f(i->x, i->y, i->z);   
      color_cnt++;
   }
   //getchar();
   glEnd();
   if (s == CUBE_GROUND && lined_posts) {
      for (int i = 0; i < 6*4; i += 4) {
            glPolygonOffset(1,1);
            glBegin(GL_LINES);
            glColor3f(0.0, 0.0, 0.0);
            glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
            i++;
            glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
            glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
            i++;
            glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
            glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
            i++;
            glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
            glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
            i -= 3;
            glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
            glEnd();
         }
   }
   //  End
   //  Undo transformations
   glPopMatrix();
}