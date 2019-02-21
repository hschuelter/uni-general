#include "Antebraco.hpp"

Antebraco::Antebraco(GLfloat base, GLfloat top, GLfloat height, GLint slices, GLint stacks, int sentido){
    this -> quadric = gluNewQuadric();
    this -> base = base;
    this -> top = top;
    this -> height = height;
    this -> slices = slices;
    this -> stacks = stacks;
    this -> sentido = sentido;
    this -> ang = (sentido == -1 ? 45 : -45);
    this -> max_ang = (sentido == -1 ? 80 : -80);
    this -> min_ang = (sentido == -1 ? 5 : -5);
    this -> dir_vel = 1.5;
}

void Antebraco::draw(){
    glPushMatrix();
        glColor3f(0, 0, 1);
        glTranslatef(0.0 * this -> sentido, 0, 0.5);
        glRotated(this -> ang, 0, 1, 0);
        gluCylinder(this -> quadric, this -> base, this -> top, this -> height, this -> slices, this -> stacks);
        glColor3f(0.6, 0.6, 0.6);
        glTranslatef(0.0, 0.0, 0.55);
        gluSphere(this -> quadric, 0.13, 6, 6);
    glPopMatrix();
}

void Antebraco::update(){
    this -> ang += dir_vel;
    if(this -> ang > this -> max_ang or this -> ang < this -> min_ang){
        dir_vel = -dir_vel;
    }
}
