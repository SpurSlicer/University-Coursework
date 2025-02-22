//#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
//#include "helpers.h"
#include "pointcloud.h"
#include "cube.h"
#include "sphere.h"
#include "pyramid.h"
#include "cylinder.h"
#include "cone.h"
#include "outpost.h"
#include "camera.h"
#include "textures.h"
#ifdef USEGLEW
#include <GL/glew.h>
#endif
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
// Tell Xcode IDE to not gripe about OpenGL deprecation
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#else
#include <GL/glut.h>
#endif
//  Default resolution
//  For Retina displays compile with -DRES=2
#ifndef RES
#define RES 1
#endif

bool only_castle_visible = false;
double t = 0.0; // for idle get time function
bool moon_rotation = true;
bool lined_posts = false;
bool axes = false;        //  Display axes
const char* text[] = {"Ortho", "Perspective", "First Person"};
shape* setting = new shape();
pointcloud* pc = new pointcloud();
cube* c = new cube();
sphere* s = new sphere();
pyramid* p = new pyramid();
cylinder* cyl = new cylinder(12);
cone* co = new cone(12);
outpost* op = new outpost(12);
textures* tex = new textures();
class camera* camera = new class camera();

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Undo previous transformations
   glLoadIdentity();
   camera->display();
   setting->activateSmoothness();
   coordinate* lighting = new coordinate({0.0, 30.0*Cos(setting->getZh())-12.5, 30.0*Sin(setting->getZh())});
   if (setting->isLightingEnabled()) {
      //  Translate intensity to color vectors
      float Ambient[]   = {(float)0.01*setting->getAmbient() ,(float)0.01*setting->getAmbient() ,(float)0.01*setting->getAmbient() ,1.0};
      float Diffuse[]   = {(float)0.01*setting->getDiffuse() ,(float)0.01*setting->getDiffuse() ,(float)0.01*setting->getDiffuse() ,1.0};
      float Specular[]  = {(float)0.01*setting->getSpecular(),(float)0.01*setting->getSpecular(),(float)0.01*setting->getSpecular(),1.0};
      //  Light position
      float Position[]  = {(float)lighting->x, (float)lighting->y, (float)lighting->z};
      //  Draw light position as ball (still no lighting here)
      //glColor3f(1,1,1);
      s->render({(float)lighting->x, (float)lighting->y, (float)lighting->z}, 3.0, SPHERE_MOON);
      //  OpenGL should normalize normal vectors
      glEnable(GL_NORMALIZE);
      //  Enable lighting
      glEnable(GL_LIGHTING);
      //  Location of viewer for specular calculations
      glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,setting->getLocal());
      //  glColor sets ambient and diffuse color materials
      glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
      glEnable(GL_COLOR_MATERIAL);
      //  Enable light 0
      glEnable(GL_LIGHT0);
      //  Set ambient, diffuse, specular components and position of light 0
      glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
      glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
      glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
      glLightfv(GL_LIGHT0,GL_POSITION,Position);   // Draw
   } else setting->deactivateLighting();
      if (!only_castle_visible) {
      pc->render(POINTCLOUD_DEFAULT);
      //cyl->render({0.0, -15.0, 0.0}, {1.0, 50.0, 1.0}, FLIP_H_V, CYLINDER_DEFAULT);
      //cyl->render({0.0, -15.0, 0.0}, {1.0, 50.0, 1.0}, FLIP_V, CYLINDER_DEFAULT);
      glEnable(GL_POLYGON_OFFSET_FILL);
      c->render({0.0, -15.0, -0.0}, {15.0, 2.5, 15.0}, 0.0, CUBE_GROUND, lined_posts);
      c->render({20.0, -15.25, 0.0}, {4.0, 2.0, 4.0}, 0.0, CUBE_GROUND, lined_posts); 
      c->render({-20.0, -15.25, 0.0}, {4.0, 2.0, 4.0}, 0.0, CUBE_GROUND, lined_posts); 
      c->render({0.0, -15.25, 20.0}, {4.0, 2.0, 4.0}, 0.0, CUBE_GROUND, lined_posts); 
      c->render({0.0, -15.25, -20.0}, {4.0, 2.0, 4.0}, 0.0, CUBE_GROUND, lined_posts);  
      c->render({-8.0,-12.0, 8.0}, {4.0, 4.0, 4.0}, 0.0, CUBE_DEFAULT, lined_posts); 
      c->render({5.0, -15.0, -5.0}, {10.0, 2.5, 10.0}, 0.0, CUBE_WATER, true); 
      glDisable(GL_POLYGON_OFFSET_FILL);
      if (lined_posts) glEnable(GL_POLYGON_OFFSET_FILL);
      if (setting->isLightingEnabled()) setting->deactivateSmoothness();
      op->render({20.0, -13.5, 0.0}, {0.9, 1.0, 0.9}, OUTPOST_DEFAULT, lined_posts);
      //op->render({-20.0, -13.5, 0.0}, {1.0, 0.5, 1.0}, OUTPOST_DEFAULT);
      op->render({0.0, -13.5, 20.0}, {0.9, 0.5, 0.9}, OUTPOST_DEFAULT, lined_posts);
      op->render({0.0, -13.5, -20.0}, {0.9, 0.5, 0.9}, OUTPOST_DEFAULT, lined_posts);
      if (setting->isLightingEnabled()) setting->activateSmoothness();
      if (lined_posts) glDisable(GL_POLYGON_OFFSET_FILL);
      //s->render({0.0, 20.0, -12.0}, 3.0, SPHERE_MOON);
      p->render({12.0, -12.45, -12.0}, {3.0, 5.0, 3.0}, 0.0, PYRAMID_SAND);
      p->render({12.0, -12.45, -8.0}, {3.0, 3.0, 3.0}, 0.0, PYRAMID_SAND);
      p->render({8.0, -12.45, -12.0}, {3.0, 3.0, 3.0}, 0.0, PYRAMID_SAND);
      p->render({9.0, -12.45, -9.0}, {6.0, 1.0, 6.0}, 0.0, PYRAMID_SAND);
      p->render({-3.0, -13.0, 3.0}, {6.0, 1.0, 6.0}, 0.0, PYRAMID_GRASS);
      p->render({-8.0, -8.0, 8.0}, {6.0, 4.0, 6.0}, 0.0, PYRAMID_ROOF);
      s->render({14.0, -12.5, 14.0}, 2.0, SPHERE_TREE);
      s->render({11.5, -12.5, 14.0}, 1.5, SPHERE_TREE);
      s->render({14.0, -12.5, 11.5}, 1.5, SPHERE_TREE);
      s->render({14.0, -12.5, 10.0}, 1.0, SPHERE_TREE);
      s->render({11.5, -12.5, 11.5}, 1.0, SPHERE_TREE);
      s->render({10.0, -12.5, 14.0}, 1.0, SPHERE_TREE);
      s->render({11.0, -12.5, 12.5}, 0.75, SPHERE_TREE);
      s->render({12.5, -12.5, 11.0}, 0.75, SPHERE_TREE);
      s->render({-14.0, -12.5, 14.0}, 2.0, SPHERE_TREE);
      s->render({-11.5, -12.5, 14.0}, 1.5, SPHERE_TREE);
      s->render({-14.0, -12.5, 11.5}, 1.5, SPHERE_TREE);
      co->render({0.0, -24.0, 0.0}, {15.0, 10.0, 15.0}, 0.0, CONE_DEFAULT);
      co->render({-20.0, -20.0, 0.0}, {3.9, 4.0, 3.9}, 0.0, CONE_DEFAULT);
      co->render({20.0, -20.0, 0.0}, {3.9, 4.0, 3.9}, 0.0, CONE_DEFAULT);
      co->render({0.0, -20.0, -20.0}, {3.9, 4.0, 3.9}, 0.0, CONE_DEFAULT);
      co->render({0.0, -20.0, 20.0}, {3.9, 4.0, 3.9}, 0.0, CONE_DEFAULT);
   } else {
      c->render({0.0, -15.0, -0.0}, {15.0, 2.5, 15.0}, 0.0, CUBE_GROUND, lined_posts);
      op->render({0.0, -13.5, 0.0}, {1.0, 1.0, 1.0}, OUTPOST_DEFAULT, lined_posts);
   }
   glColor3f(1,1,1); // White
   //  Draw axes
   if (setting->isLightingEnabled()) setting->deactivateLighting(); 
   if (axes)
   {
      const double len=20.0;  //  Length of axes
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");
   }
   //  Five pixels from the lower left corner of the window
   glWindowPos2i(5,5);
   //  Print the text string
   Print("Angle=%d,%d, View-Type: %s",camera->getTh(), (camera->getState() == FIRST_PERSON) ? camera->getFpPh() : camera->getPh(), text[camera->getState()]);
   //  Render the scene
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
   delete lighting;
}


/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   camera->rotate(key);
   //  Tell GLUT it is necessary to redisplay the scene
   camera->project();
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0') { 
      camera->resetAngles();
   //  Toggle axes
   } else if (ch == '9') {
      camera->resetAnglesPerpendicular();
   }else if (ch == 'q' || ch == 'Q') {
      axes = !axes;
   }else if (ch == 'l' || ch == 'L') {
      lined_posts = !lined_posts;
   }else if (ch == 'm' || ch == 'M') {
      camera->changeState(); 
   } else if (ch == 'p') {
      moon_rotation = !moon_rotation;
   } else if (ch == 'o' || ch == 'O') {
      only_castle_visible = !only_castle_visible;
   } else if (ch == ']') {
      if (!moon_rotation) {
         t += 0.05;
         if (t > 4.0) t = t - 4.0;
         else if (t < 0.0) t = t + 4.0;
         camera->idleSetZh(t);
         setting->updateZh(t);
      }
   } else if (ch == '[') {
      if (!moon_rotation) {
         t -= 0.05;
         if (t > 4.0) t = t - 4.0;
         else if (t < 0.0) t = t + 4.0;
         camera->idleSetZh(t);
         setting->updateZh(t);
      }
   }
   camera->translate(ch);
   //  Tell GLUT it is necessary to redisplay the scene
   camera->project();
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height) {
   //  Ratio of the width to the height of the window
   camera->reshapeAsp(width, height);
   //  Set the viewport to the entire window
   glViewport(0,0, RES*width,RES*height);
   //  Set projection
   camera->project();
}

/*
 *  GLUT calls this routine when there is nothing else to do
 */
void idle()
{
   if (moon_rotation) {
      //t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
      t += 0.015;
      if (t > 4.0) t = 0.0;
      camera->idleSetZh(t);
      setting->updateZh(t);
   }
   glutPostRedisplay();
}

std::vector<std::string> generateBMPVector() {
   std::vector<std::string> names;
   names.push_back("_dirt.bmp");
   names.push_back("_grass.bmp");
   names.push_back("_rocks.bmp");
   names.push_back("_sand.bmp");
   names.push_back("_water.bmp");
   names.push_back("_roof.bmp");
   names.push_back("_moon.bmp");
   names.push_back("_castle.bmp");
   names.push_back("_log.bmp");
   return names;
}

void populateTexs() {
   op->setTexturesMap(tex);
   c->setTexturesMap(tex);
   s->setTexturesMap(tex);
   p->setTexturesMap(tex);
   cyl->setTexturesMap(tex);
   co->setTexturesMap(tex);
   return;
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT and process user parameters
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitWindowSize(600,600);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   //  Create the window
   glutCreateWindow("Textures!! - Homework 6");
#ifdef USEGLEW
   //  Initialize GLEW
   if (glewInit()!=GLEW_OK) Fatal("Error initializing GLEW\n");
#endif
   //  Tell GLUT to call "idle" when there is nothing else to do
   glutIdleFunc(idle);
   //  Tell GLUT to call "display" when the scene should be drawn
   glutDisplayFunc(display);
   //  Tell GLUT to call "reshape" when the window is resized
   glutReshapeFunc(reshape);
   //  Tell GLUT to call "special" when an arrow key is pressed
   glutSpecialFunc(special);
   //  Tell GLUT to call "key" when a key is pressed
   glutKeyboardFunc(key);
   //  Pass control to GLUT so it can interact with the user
   tex->loadTextures(generateBMPVector());
   populateTexs();
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
