/*
 *  Hello World Triangle Version 4
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "lorenz.h"
//  Default resolution
//  For Retina displays compile with -DRES=2
#ifndef RES
#define RES 1
#endif
int ph=0, th=0;  //  Rotation angle
double w = 1.0;
lorenz* l = new lorenz();

/*
 * Convenience function for text
 */
#define LEN 8192  //  Maximum amount of text
void Print(const char* format , ...)
{
   char    buf[LEN]; // Text storage
   char*   ch=buf;   // Text pointer
   //  Create text to be display
   va_list args;
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   //  Display text string
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

/*
 * This function is called by GLUT to display the scene
 */
void display()
{
   //  Clear screen and Z-buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Reset transformations
   glLoadIdentity();
   //  Rotate around Y axis
   glRotatef(ph,1,0,0);
   glRotatef(th,0,1,0);
   //  RGB triangle
   glBegin(GL_LINES);
   l->displayCoordinates(w);
   glEnd();
   //  Draw axes in white
   glColor3f(1,1,1);
   glBegin(GL_LINES);
   glVertex3d(0,0,0);
   glVertex3d(20,0,0);
   glVertex3d(0,0,0);
   glVertex3d(0,20,0);
   glVertex3d(0,0,0);
   glVertex3d(0,0,20);
   glEnd();
   //  Label axes
   glRasterPos3d(20,0,0);
   Print("X");
   glRasterPos3d(0,20,0);
   Print("Y");
   glRasterPos3d(0,0,20);
   Print("Z");
   //  Display rotation angle
   glColor3f(1,1,1);
   glWindowPos2i(5,5);
   Print("Angle=%d,%d; w=%.2f; s=%.0f; b=%.3f; r=%.0f; iter=%d",th,ph,w,l->getS(),l->getB(),l->getR(),l->getIterations());
   //  Flush and swap buffer
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 * This function is called by GLUT when special keys are pressed
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
   glutPostRedisplay();
}

void key(unsigned char ch, int x, int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   else if (ch == 'w' || ch == 'W')
      w += ((ch == 'w') ? (-0.01) : (+0.01));
   else if (ch == 's' || ch == 'S')
      l->modifyS((ch == 's') ? (-1.0) : (+1.0));
   else if (ch == 'b' || ch == 'B')
      l->modifyB((ch == 'b') ? (-1.0) : (+1.0));
   else if (ch == 'r' || ch == 'R')
      l->modifyR((ch == 'r') ? (-1.0) : (+1.0));
   else if (ch == '=' || ch == '-')
      l->modifyIterations((ch == '-') ? (-1000) : (+1000));
   else if (ch == '+' || ch == '_')
      l->modifyIterations((ch == '_') ? (-10000) : (+10000));
   else if (ch == '0') {
      th = ph = 0;
      l->resetParameters();
      w = 1.0;
   } 
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 * This function is called by GLUT when the window is resized
 */
void reshape(int width,int height)
{
   //  Set the viewport to the entire window
   glViewport(0,0, RES*width,RES*height);
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Orthogonal projection
   const double dim=50.0;
   double asp = (height>0) ? (double)width/height : 1;
   glOrtho(-asp*dim,+asp*dim, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

/*
 * GLUT based Hello World
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered true color window with Z-buffer
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowSize(500,500);
   //  Create window
   glutCreateWindow("Lorenz Attractor");
#ifdef USEGLEW
   //  Initialize GLEW
   if (glewInit()!=GLEW_OK) Fatal("Error initializing GLEW\n");
#endif
   //  Register display, reshape and key callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   //  Enable Z-buffer depth test
   glEnable(GL_DEPTH_TEST);
   //  Pass control to GLUT for events
   glutMainLoop();
   //  Return to OS
   return 0;
}
