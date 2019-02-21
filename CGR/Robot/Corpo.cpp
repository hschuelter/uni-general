#include "Corpo.hpp"

Corpo::Corpo(GLfloat base, GLfloat top, GLfloat height, GLint slices, GLint stacks){
    this -> quadric = gluNewQuadric();
    this -> base = base;
    this -> top = top;
    this -> height = height;
    this -> slices = slices;
    this -> stacks = stacks;

    this -> braco_dir = new Braco(0.1, 0.1, 0.5, 20, 20, -1);
    this -> braco_esq = new Braco(0.1, 0.1, 0.5, 20, 20, 1);

    this -> coxa_dir = new Coxa(0.1, 0.1, 0.30, 20, 20, -1);
    this -> coxa_esq = new Coxa(0.1, 0.1, 0.30, 20, 20, 1);

    this -> cabeca = new Cabeca(0.35, 20, 20);
}

void Corpo::draw(){
    glPushMatrix();
        glColor3f(1, 1, 0);
        glTranslatef(0, 0.0, 0);
        gluCylinder(this -> quadric, this -> base, this -> top, this -> height, this -> slices, this -> stacks);
        braco_dir -> draw();
        braco_esq -> draw();
        coxa_dir -> draw();
        coxa_esq -> draw();
        cabeca -> draw();
    glPopMatrix();
}

void Corpo::update(){
    braco_dir -> update();
    braco_esq -> update();
    coxa_dir -> update();
    coxa_esq -> update();
}
