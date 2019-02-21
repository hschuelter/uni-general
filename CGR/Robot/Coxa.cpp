#include "Coxa.hpp"

Coxa::Coxa(GLfloat base, GLfloat top, GLfloat height, GLint slices, GLint stacks, int sentido){
    this -> base = base;
    this -> top = top;
    this -> height = height;
    this -> slices = slices;
    this -> stacks = stacks;
    this -> quadric = gluNewQuadric();
    this -> sentido = sentido;
    this -> ang = 30.0;
    this -> max_ang = 40;
    this -> min_ang = -40;
    this -> ang_vel = 1.0;

    this -> canela = new Canela(0.1, 0.1, 0.30, 20, 20, -1);

}

void Coxa::draw(){

    glPushMatrix();
        glColor3f(0.5, 1, 0.5);
        glRotated(180, 1, 0, 0);
        glTranslatef(0.20 * this -> sentido, 0.0, 0.0);
        glRotated(this -> ang * this -> sentido, 1, 0, 0);
        gluCylinder(this -> quadric, this -> base, this -> top, this -> height, this -> slices, this -> stacks);

        this -> canela -> draw();
    glPopMatrix();
}

void Coxa::update(){
    this -> ang += this -> ang_vel;
    if(this -> ang > this -> max_ang or this -> ang < this -> min_ang){
        this -> ang_vel *= -1;
    }
}
