#include "Braco.hpp"

Braco::Braco(GLfloat base, GLfloat top, GLfloat height, GLint slices, GLint stacks, int sentido){
    this -> quadric = gluNewQuadric();
    this -> base = base;
    this -> top = top;
    this -> height = height;
    this -> slices = slices;
    this -> stacks = stacks;
    this -> sentido = sentido;
    this -> ang = (sentido == -1 ? 260 : 75);
    this -> max_ang = (sentido == -1 ? 325 : 150);
    this -> min_ang = (sentido == -1 ? 220 : 35);
    this -> dir_vel = 1;
    this -> antebraco = new Antebraco(0.1, 0.1, 0.5, 20, 20, sentido);
}

void Braco::draw(){
    glPushMatrix();
        glColor3f(0, 1, 0);
        glTranslatef(0.30  * this -> sentido, 0.0, 1);
        glRotated(this -> ang, 0, 1, 0);
        gluCylinder(this -> quadric, this -> base, this -> top, this -> height, this -> slices, this -> stacks);
        this -> antebraco -> draw();
        glColor3f(1, 1, 1);
        glTranslatef(0.0, 0.0, 0.5);
        gluSphere(this -> quadric, 0.09, 20, 20);
    glPopMatrix();
}

void Braco::update(){
    this -> ang += dir_vel;
    if(this -> ang > this -> max_ang or this -> ang < this -> min_ang){
        dir_vel = -dir_vel;
    }
    this -> antebraco -> update();
}
