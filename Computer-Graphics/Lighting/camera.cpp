#include "camera.h"

//camera::camera() { )

void camera::project() {
    glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective transformation
   if (this->state == ORTHO)
      glOrtho(-this->asp*this->dim,+this->asp*this->dim, -this->dim,+this->dim, -this->dim,+this->dim);
   else if (this->state == PERSPECTIVE || this->state == FIRST_PERSON)
      gluPerspective(this->fov,this->asp,this->dim/16,16*this->dim); // zNear and zFar defines clipping distance and render distance, respectively
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

void camera::resetAngles() {
    this->th = 135;
    this->ph = 90;
    this->fp_ph = 0;
}

void camera::resetAnglesPerpendicular() {
    this->th = 90;
    this->ph = 0;
    this->fp_ph = 0;
}

void camera::changeState() {
    if (this->state == ORTHO)
        this->state = PERSPECTIVE;
    else if (this->state == PERSPECTIVE)
        this->state = FIRST_PERSON;
    else if (this->state == FIRST_PERSON)
        this->state = ORTHO;
}

void camera::reshapeAsp(int width, int height) {
    this->asp = (height>0) ? (double)width/height : 1;
}

void camera::rotate(int key) {
    int rotation_factor = 5;
    //  Right arrow key - increase angle by 5 degrees
    if (key == GLUT_KEY_RIGHT)
        this->th += rotation_factor;
    //  Left arrow key - decrease angle by 5 degrees
    else if (key == GLUT_KEY_LEFT)
        this->th -= rotation_factor;
    //  Up arrow key - increase elevation by 5 degrees
    else if (key == GLUT_KEY_UP) {
        if (this->state == FIRST_PERSON)
            this->fp_ph += rotation_factor;
        else
            this->ph += rotation_factor;
    //  Down arrow key - decrease elevation by 5 degrees
    }else if (key == GLUT_KEY_DOWN) {
        if (this->state == FIRST_PERSON)
            this->fp_ph -= rotation_factor;
        else
            this->ph -= rotation_factor;
    //  Keep angles to +/-360 degrees
    }
    this->th %= 360;
    this->ph %= 360;
    this->fp_ph %= 360;
}

void camera::idleSetZh(double t) {
    zh = fmod(90*t,360);
}

int camera::getTh() { return this->th; }
int camera::getPh() { return this->ph; }
int camera::getFpPh() { return this->fp_ph; }
camera_state camera::getState() { return this->state; }

void camera::display() {
    if (this->state == ORTHO) {
        glRotatef(ph,1,0,0);
        glRotatef(th,0,1,0);
    } else if (this->state == PERSPECTIVE) {
    //  Set view angle
        double Ex = -2*dim*Sin(th)*Cos(ph);
        double Ey = +2*dim        *Sin(ph);
        double Ez = +2*dim*Cos(th)*Cos(ph);
        gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(this->ph),0);
    } else if (this->state == FIRST_PERSON) {
        glRotatef(this->fp_ph, -1, 0, 0);
        gluLookAt(this->pos_x, this->pos_y, this->pos_z, (this->pos_x+Sin(this->th)), this->pos_y, (this->pos_z-Cos(th)) , 0,Cos(this->fp_ph),0);
    }
}

void camera::translate(unsigned char key) {

    if (this->state == FIRST_PERSON) {
        if (key == 'z')
            this->pos_y += 0.1f;
        else if (key == 'Z')
            this->pos_y -= 0.1f;
        if (key == 'd' || key == 'D') {
            this->pos_x += Cos(th);
            this->pos_z += Sin(th);
        }
        if (key == 'w' || key == 'W') {
            this->pos_x += Sin(th);
            this->pos_z -= Cos(th);
        }
        if (key == 'a' || key == 'A') {
            this->pos_x -= Cos(th);
            this->pos_z -= Sin(th);
        }
        if (key == 's' || key == 'S') {
            this->pos_x -= Sin(th);
            this->pos_z += Cos(th);
        }
    }
}
