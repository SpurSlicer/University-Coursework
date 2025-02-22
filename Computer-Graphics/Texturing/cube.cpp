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
   int color_index = 0, normal_cnt = 0, coords_size = this->coords.size();
   color* current_color = nullptr;
   //  Cube
   if (s == CUBE_WATER) glPolygonOffset(2,2);
   else glPolygonOffset(3, 3);

   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_MODULATE);
   glColor3f(1,1,1);
   glBindTexture(GL_TEXTURE_2D,this->texs->getTextureId("_log.bmp"));

   //  Front
   for (int i = 0; i < coords_size; i++) {
      if (i % 4 == 0) {
         if (i != 0) glEnd();
      }
      glColor3f(1.0, 1.0, 1.0);
      switch (s) {
         case CUBE_GROUND:
            if (i % 4 == 0) {
               //glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
               //glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
               //glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
               //glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );  
               if (i < 16 || i > 19) glBindTexture(GL_TEXTURE_2D,this->texs->getTextureId("_dirt.bmp"));
               else glBindTexture(GL_TEXTURE_2D,this->texs->getTextureId("_grass.bmp"));
            }          
            if (i == 0) {
               //current_color = this->colors.at(CUBE_GROUND).at(0);
               //glColor3f(current_color->x, current_color->y, current_color->z);
            } else if (i == 8) {
               //current_color = this->colors.at(CUBE_GROUND).at(1);
               //glColor3f(current_color->x, current_color->y, current_color->z);
            } else if (i == 16) {
               //current_color = this->colors.at(CUBE_GROUND).at(2);
               //glColor3f(current_color->x, current_color->y, current_color->z);
            } else if (i == 20) {
               //current_color = this->colors.at(CUBE_GROUND).at(3);
               //glColor3f(current_color->x, current_color->y, current_color->z);
            }
            break;
         case CUBE_WATER:
            if (i % 4 == 0) {
               glBindTexture(GL_TEXTURE_2D,this->texs->getTextureId("_water.bmp"));
            }
            //current_color = this->colors.at(CUBE_WATER).at(0);
            //glColor3f(current_color->x, current_color->y, current_color->z);
            break;
         default:
            if (i % 4 == 0) {
               glBindTexture(GL_TEXTURE_2D,this->texs->getTextureId("_log.bmp"));
            }
            //current_color = this->colors.at(CUBE_DEFAULT).at(i);
            //glColor3f(current_color->x, current_color->y, current_color->z);
      }
      if (i % 4 == 0) {
         //std::cout << this->normals.at(normal_cnt)->x << this->normals.at(normal_cnt)->y << this->normals.at(normal_cnt)->z << std::endl;
         glBegin(GL_POLYGON);
         glNormal3f(this->normals.at(normal_cnt)->x, this->normals.at(normal_cnt)->y, this->normals.at(normal_cnt)->z);
         normal_cnt++;
      }
      if (i % 4 == 0) {
         glTexCoord2f(0,0);
      } else if (i % 4 == 1) {
         glTexCoord2f(scale.x/2,0);
      } else if (i % 4 == 2) {
         glTexCoord2f(scale.x/2,scale.x/2);
      } else if (i % 4 == 3) {
         glTexCoord2f(0,scale.x/2);
      }
      if (s == CUBE_WATER) {
         if (i > 15 && i < 20) glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);   
      }
      else glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);   
   }
   glEnd();
   if (s == CUBE_GROUND && lined_posts) {
      for (int i = 0; i < 6*4; i += 4) {
            glPolygonOffset(1,1);
            glColor3f(0.0, 0.0, 0.0);
            glBegin(GL_LINES);
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
   glDisable(GL_TEXTURE_2D);
}