#include "outpost.h"

outpost::outpost(double sides) {
    initStyles();
    this->sides = sides+1;
    //  Latitude bands
    const float factor = 360 / sides;
    float multiplier_1 = 4.0, multiplier_2 = 4.0;
    for (double a = 0; a < 360; a += factor) {
        this->coords.push_back(new coordinate({multiplier_1 * Cos(a), 0, multiplier_1 * Sin(a)}));
        a += factor;
        this->coords.push_back(new coordinate({multiplier_1 * Cos(a), 0, multiplier_1 * Sin(a)}));
        this->coords.push_back(new coordinate({multiplier_2 * Cos(a), 3, multiplier_2 * Sin(a)})); 
        a-=factor;
        this->coords.push_back(new coordinate({multiplier_2 * Cos(a), 3, multiplier_2 * Sin(a)})); 
    }
    multiplier_2 = 2.0;
    for (double a = 0; a < 360; a += factor) {
        this->coords.push_back(new coordinate({multiplier_1 * Cos(a), 3, multiplier_1 * Sin(a)}));
        a += factor;
        this->coords.push_back(new coordinate({multiplier_1 * Cos(a), 3, multiplier_1 * Sin(a)}));
        this->coords.push_back(new coordinate({multiplier_2 * Cos(a), 4, multiplier_2 * Sin(a)})); 
        a-=factor;
        this->coords.push_back(new coordinate({multiplier_2 * Cos(a), 4, multiplier_2 * Sin(a)})); 
    }
    multiplier_1 = 2.0;
    for (double a = 0; a < 360; a += factor) {
        this->coords.push_back(new coordinate({multiplier_1 * Cos(a), 4, multiplier_1 * Sin(a)}));
        a += factor;
        this->coords.push_back(new coordinate({multiplier_1 * Cos(a), 4, multiplier_1 * Sin(a)}));
        this->coords.push_back(new coordinate({multiplier_2 * Cos(a), 6, multiplier_2 * Sin(a)})); 
        a-=factor;
        this->coords.push_back(new coordinate({multiplier_2 * Cos(a), 6, multiplier_2 * Sin(a)}));     
    }
    multiplier_2 = 4.0;
    for (double a = 0; a < 360; a += factor) {
        this->coords.push_back(new coordinate({multiplier_2 * Cos(a), 7, multiplier_2 * Sin(a)})); 
        a+=factor;
        this->coords.push_back(new coordinate({multiplier_2 * Cos(a), 7, multiplier_2 * Sin(a)}));   
        this->coords.push_back(new coordinate({multiplier_1 * Cos(a), 6, multiplier_1 * Sin(a)}));
        a -= factor;
        this->coords.push_back(new coordinate({multiplier_1 * Cos(a), 6, multiplier_1 * Sin(a)}));
    }
    
    
    /*for (double a = 0; a <= 360; a += factor) {
        this->coords.push_back(new coordinate({multiplier_1 * Cos(a), 0, multiplier_1 * Sin(a)}));
        this->coords.push_back(new coordinate({multiplier_2 * Cos(a), 3, multiplier_2 * Sin(a)})); 
    }
    multiplier_2 = 2.0;
    for (double a = 0; a <= 360; a += factor) {
        this->coords.push_back(new coordinate({multiplier_1 * Cos(a), 3, multiplier_1 * Sin(a)}));
        this->coords.push_back(new coordinate({multiplier_2 * Cos(a), 4, multiplier_2 * Sin(a)})); 
    }
    multiplier_1 = 2.0;
    for (double a = 0; a <= 360; a += factor) {
        this->coords.push_back(new coordinate({multiplier_1 * Cos(a), 4, multiplier_1 * Sin(a)}));
        this->coords.push_back(new coordinate({multiplier_2 * Cos(a), 6, multiplier_2 * Sin(a)}));     }
    multiplier_2 = 4.0;
    for (double a = 0; a <= 360; a += factor) {
        this->coords.push_back(new coordinate({multiplier_2 * Cos(a), 7, multiplier_2 * Sin(a)})); 
        this->coords.push_back(new coordinate({multiplier_1 * Cos(a), 6, multiplier_1 * Sin(a)}));
  
    }*/
    int coords_size = this->coords.size();
    for (int i = 0; i < coords_size; i+=4) {
        this->generateNormalBySquare(this->coords, i, false);
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
    //printf("alt size: %d\n", this->alt_coords.size());
    int alt_coords_size = this->alt_coords.size();   
    for (int i = 0; i < alt_coords_size; i+=4) {
        if ((i % 24) == 16) {
            //printf("I'm here\n");
            this->normals.push_back(getGenericNormal(PLUS_Y));
        }else if ((i % 24) == 20) this->normals.push_back(getGenericNormal(MINUS_Y));
        else this->generateNormalBySquare(this->alt_coords, i, true);
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
    // Lighting
    float Emission[]  = {0.0,0.0,static_cast<float>(0.01* static_cast<float>(this->emission)),1.0};
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, this->shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,this->WHITE);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
    //  Save transformation
    glPushMatrix();
    //  Offset and scale
    glTranslated(offset.x, offset.y,offset.z);
    glScaled(scale.x,scale.y,scale.z);
    int norm_cnt = 0, num_coords_slice = (this->coords.size() - sides) /4;
    int coords_size = this->coords.size();
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D,this->texs->getTextureId("_castle.bmp"));
    float mult = 1.0;
    //glBegin(GL_POLYGON);
    for (int i = 0; i < coords_size-sides; i++) {
        if (i % 4 == 0) {
            if (i != 0) glEnd();
            //glColor3f(1.0, 1.0, 1.0);
            glColor3f(this->colors.at(0).at(0)->x, this->colors.at(0).at(0)->y, this->colors.at(0).at(0)->z);
            glBindTexture(GL_TEXTURE_2D,this->texs->getTextureId("_castle.bmp"));
            glBegin(GL_POLYGON);
            //if (i > 2*num_coords_slice || i <= num_coords_slice)
            //    glNormal3f(this->normals.at(norm_cnt)->x, this->normals.at(norm_cnt)->y, this->normals.at(norm_cnt)->z);
            //else glNormal3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
            //if (i < num_coords_slice || i >= 2*num_coords_slice)
            if (i >= 3*num_coords_slice) glNormal3f(this->normals.at(norm_cnt)->x, this->normals.at(norm_cnt)->y, this->normals.at(norm_cnt)->z);
            else if (i >= num_coords_slice && i < 2*num_coords_slice) glNormal3f(-this->normals.at(norm_cnt)->x, -this->normals.at(norm_cnt)->y, -this->normals.at(norm_cnt)->z);
            else glNormal3f(-this->normals.at(norm_cnt)->x, -this->normals.at(norm_cnt)->y, -this->normals.at(norm_cnt)->z);
            norm_cnt++;
        }
        /*if ((i >= num_coords_slice && i < 2*num_coords_slice)) {
            //glEnd();
            //glBegin(GL_POLYGON);
            //glColor3f(this->colors.at(0).at(0)->x, this->colors.at(0).at(0)->y, this->colors.at(0).at(0)->z);
            glNormal3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
        } 
        else if (i >= 3*num_coords_slice) {
            glNormal3f(this->coords.at(i)->x, -this->coords.at(i)->y, this->coords.at(i)->z);
        }*/
        /*
        if (i > num_coords_slice*3) {
            mult = 1;
        } else if (i > num_coords_slice*2) {
            mult = (float)1/2;
        } else if (i > num_coords_slice) {
            mult = 1;
        }*/
        if (i % 4 == 0) {
            glTexCoord2f(0,0);
        } else if (i % 4 == 1) {
            glTexCoord2f(1*mult,0);
        } else if (i % 4 == 2) {
            glTexCoord2f(1*mult,1*mult);
        } else if (i % 4 == 3) {
            glTexCoord2f(0,1*mult);
        }
        glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
    }
    glEnd();
    const int body_number = this->coords.size() - sides, strip_number = (this->coords.size()-sides)/4; 
    /*for (int off = 0; off < (body_number-1); off += strip_number) {
        glPolygonOffset(3,3);
        glBegin(GL_QUAD_STRIP);
        glColor3f(this->colors.at(s).at(0)->x, this->colors.at(s).at(0)->y, this->colors.at(s).at(0)->z);
        for (int i = 0; i < strip_number; i++) {
            if (off == strip_number*3) glNormal3f(this->coords.at(i+off)->x, -this->coords.at(i+off)->y, this->coords.at(i+off)->z);
            else glNormal3f(this->coords.at(i+off)->x, this->coords.at(i+off)->y, this->coords.at(i+off)->z);
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
    }*/
    glColor3f(this->colors.at(s).at(0)->x, this->colors.at(s).at(0)->y, this->colors.at(s).at(0)->z);
    glBindTexture(GL_TEXTURE_2D,this->texs->getTextureId("_rocks.bmp"));
    glBegin(GL_POLYGON);
    coordinate* plus_y_normal = this->getGenericNormal(PLUS_Y);
    coordinate* minus_y_normal = this->getGenericNormal(MINUS_Y);
    glNormal3f(plus_y_normal->x, plus_y_normal->y, plus_y_normal->z);
    for (int i = this->coords.size()-sides; i < coords_size; i++) {
        glTexCoord2f(this->coords.at(i)->x, this->coords.at(i)->z);
        glVertex3f(this->coords.at(i)->x, this->coords.at(i)->y, this->coords.at(i)->z);
    }
    glEnd();
    const int num_cube_vertices = this->alt_coords.size();
    mult = 1.0;
    for (int off = 0; off < num_cube_vertices; off += 4*6) {
        //glColor3f(1.0, 1.0, 1.0);
        if (off % 48 == 4*6) mult = 0.5;
        else mult = 1.0;
        glColor3f(this->colors.at(0).at(0)->x, this->colors.at(0).at(0)->y, this->colors.at(0).at(0)->z);
        glBindTexture(GL_TEXTURE_2D,this->texs->getTextureId("_castle.bmp"));
        glBegin(GL_QUADS);
        //glColor3f(this->colors.at(s).at(0)->x, this->colors.at(s).at(0)->y, this->colors.at(s).at(0)->z);
        for (int i = 0; i < 4*6; i++) {
            //if (i == 8) glColor3f(this->colors.at(s).at(1)->x, this->colors.at(s).at(1)->y, this->colors.at(s).at(1)->z);
            //else if (i == 12) glColor3f(this->colors.at(s).at(0)->x, this->colors.at(s).at(0)->y, this->colors.at(s).at(0)->z);
            //if (i < 16) glNormal3f(this->alt_coords.at(i+off)->x, this->alt_coords.at(i+off)->y, this->alt_coords.at(i+off)->z);
            //if (i > 15 && i < 20) glNormal3f(plus_y_normal->x, plus_y_normal->y, plus_y_normal->z);
            //else if (i >= 20) glNormal3f(minus_y_normal->x, minus_y_normal->y, minus_y_normal->z);
            if (i%4 == 0) {

                glNormal3f(this->normals.at(norm_cnt)->x, this->normals.at(norm_cnt)->y, this->normals.at(norm_cnt)->z);
                norm_cnt++;
            }
            if (i < 4 || (i < 12 && i > 7)) {
                if (i % 4 == 0) {
                    glTexCoord2f(1,0);
                } else if (i % 4 == 1) {
                    glTexCoord2f(1,1*mult);
                } else if (i % 4 == 2) {
                    glTexCoord2f(0,1*mult);
                } else if (i % 4 == 3) {
                    glTexCoord2f(0,0);
                }  
            }  else if (i > 15) {
                if (i % 4 == 0) {
                    glTexCoord2f(1,1*0.5);
                } else if (i % 4 == 1) {
                    glTexCoord2f(0,1*0.5);
                } else if (i % 4 == 2) {
                    glTexCoord2f(0,0);
                } else if (i % 4 == 3) {
                    glTexCoord2f(1,0);
                } 
            } else {
                if (i % 4 == 0) {
                    glTexCoord2f(1,0);
                } else if (i % 4 == 1) {
                    glTexCoord2f(1,1);
                } else if (i % 4 == 2) {
                    glTexCoord2f(0,1);
                } else if (i % 4 == 3) {
                    glTexCoord2f(0,0);
                } 
            } 
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
    delete plus_y_normal;
    delete minus_y_normal;
   //  Undo transformations
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}