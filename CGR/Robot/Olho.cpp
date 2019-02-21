#include "Olho.hpp"

Olho::Olho(GLfloat radius, GLint stacks, GLint slices, int sentido){
    this -> radius = radius;
    this -> stacks = stacks;
    this -> slices = slices;
    this -> quadric = gluNewQuadric();
    this -> sentido = sentido;
}

void Olho::draw(){
    glPushMatrix();
        glColor3f(0, 0, 0);
        glTranslatef(0.19 * this -> sentido, 0.25, 0.13);
        gluSphere(this -> quadric, this -> radius, this -> slices, this -> stacks);
    glPopMatrix();
}
