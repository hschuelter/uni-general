#include "Boca.hpp"

Boca::Boca(GLfloat base, GLfloat top, GLfloat height, GLint slices, GLint stacks){
    this -> base = base;
    this -> top = top;
    this -> height = height;
    this -> slices = slices;
    this -> stacks = stacks;
    this -> quadric = gluNewQuadric();
}

void Boca::draw(){
    glPushMatrix();
        glColor3f(1, 1, 1);
        glTranslatef(0.0, 0.3, -0.1);
        gluCylinder(this -> quadric, this -> base, this -> top, this -> height, this -> slices, this -> stacks);
    glPopMatrix();
}
