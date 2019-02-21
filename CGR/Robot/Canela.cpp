#include "Canela.hpp"

Canela::Canela(GLfloat base, GLfloat top, GLfloat height, GLint slices, GLint stacks, int sentido){
    this -> base = base;
    this -> top = top;
    this -> height = height;
    this -> slices = slices;
    this -> stacks = stacks;
    this -> quadric = gluNewQuadric();
    this -> sentido = sentido;
    this -> ang = 25.0;
}

void Canela::draw(){
    glPushMatrix();
        glColor3f(1, 0, 0);
        //glRotated(180, 1, 0, 0);
        glTranslatef(0, 0.0, 0.27);
        glRotated(this -> ang * this -> sentido, 1, 0, 0);
        gluCylinder(this -> quadric, this -> base, this -> top, this -> height, this -> slices, this -> stacks);
    glPopMatrix();
}
