#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "pointcloud.h"
#include "cube.h"
#include "sphere.h"
#include "pyramid.h"
#include "cylinder.h"
#include "cone.h"
#include "outpost.h"
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

bool lined_posts = false;
int th=135;          //  Azimuth of view angle
int ph=5;          //  Elevation of view angle
double zh=0;       //  Rotation of teapot
int axes=0;        //  Display axes
double asp = 1;
int fov=55;
double dim=29.0;
const char* text[] = {"Cuboids","Spheres","FlatPlane Outline","FlatPlane Fill","SolidPlane","Icosahedron DrawElements","Icosahedron DrawArrays","Icosahedron VBO","Scene"};
pointcloud* pc = new pointcloud();
cube* c = new cube();
sphere* s = new sphere();
pyramid* p = new pyramid();
cylinder* cyl = new cylinder(12);
cone* co = new cone(12);
outpost* op = new outpost(12);

/*
 *  Convenience routine to output raster text
 *  Use VARARGS to make this more flexible
 */
#define LEN 8192  //  Maximum length of text string
void Print(const char* format , ...)
{
   char    buf[LEN];
   char*   ch=buf;
   va_list args;
   //  Turn the parameters into a character string
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   //  Display the characters one at a time at the current raster position
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

/*
 *  Check for OpenGL errors
 */
void ErrCheck(const char* where)
{
   int err = glGetError();
   if (err) fprintf(stderr,"ERROR: %s [%s]\n",gluErrorString(err),where);
}

/*
 *  Print message to stderr and exit
 */
void Fatal(const char* format , ...)
{
   va_list args;
   va_start(args,format);
   vfprintf(stderr,format,args);
   va_end(args);
   exit(1);
}

static void project()
{
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective transformation
   gluPerspective(fov,asp,dim/4,4*dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

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
   //  Set view angle
   double Ex = -2*dim*Sin(th)*Cos(ph);
   double Ey = +2*dim        *Sin(ph);
   double Ez = +2*dim*Cos(th)*Cos(ph);
   gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   // Draw
   pc->render(POINTCLOUD_DEFAULT);
   cyl->render({0.0, -15.0, 0.0}, {1.0, 50.0, 1.0}, FLIP_H_V, CYLINDER_DEFAULT);
   cyl->render({0.0, -15.0, 0.0}, {1.0, 50.0, 1.0}, FLIP_V, CYLINDER_DEFAULT);
   glEnable(GL_POLYGON_OFFSET_FILL);
   c->render({0.0, -15.0, -0.0}, {15.0, 2.5, 15.0}, 0.0, CUBE_GROUND, lined_posts);
   c->render({20.0, -15.25, 0.0}, {4.0, 2.0, 4.0}, 0.0, CUBE_GROUND, lined_posts); 
   c->render({-20.0, -15.25, 0.0}, {4.0, 2.0, 4.0}, 0.0, CUBE_GROUND, lined_posts); 
   c->render({0.0, -15.25, 20.0}, {4.0, 2.0, 4.0}, 0.0, CUBE_GROUND, lined_posts); 
   c->render({0.0, -15.25, -20.0}, {4.0, 2.0, 4.0}, 0.0, CUBE_GROUND, lined_posts);  
   c->render({-8.0,-12.0, 8.0}, {4.0, 4.0, 4.0}, 0.0, CUBE_GROUND, lined_posts); 
   c->render({5.0, -15.0, -5.0}, {10.0, 2.5, 10.0}, 0.0, CUBE_WATER, true); 
   glDisable(GL_POLYGON_OFFSET_FILL);
   if (lined_posts) glEnable(GL_POLYGON_OFFSET_FILL);
   op->render({20.0, -13.5, 0.0}, {0.9, 1.0, 0.9}, OUTPOST_DEFAULT, lined_posts);
   //op->render({-20.0, -13.5, 0.0}, {1.0, 0.5, 1.0}, OUTPOST_DEFAULT);
   op->render({0.0, -13.5, 20.0}, {0.9, 0.5, 0.9}, OUTPOST_DEFAULT, lined_posts);
   op->render({0.0, -13.5, -20.0}, {0.9, 0.5, 0.9}, OUTPOST_DEFAULT, lined_posts);
   if (lined_posts) glDisable(GL_POLYGON_OFFSET_FILL);
   s->render({0.0, 20.0, -12.0}, 3.0, SPHERE_MOON);
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
   glColor3f(1,1,1); // White
   //  Draw axes
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
   Print("Angle=%d,%d",th,ph);
   //  Render the scene
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Tell GLUT it is necessary to redisplay the scene
   project();
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
      th = 135; ph = 5;
   //  Toggle axes
   }else if (ch == 'q' || ch == 'Q') {
      axes = 1-axes;
   }else if (ch == 'm' || ch == 'M') {
      lined_posts = !lined_posts;
   }
   //  Tell GLUT it is necessary to redisplay the scene
   project();
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height) {
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, RES*width,RES*height);
   //  Set projection
   project();
}

/*
 *  GLUT calls this routine when there is nothing else to do
 */
void idle()
{
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360);
   glutPostRedisplay();
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
   glutCreateWindow("Scene in 3D - Homework 3");
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
   glutMainLoop();
   return 0;
}
