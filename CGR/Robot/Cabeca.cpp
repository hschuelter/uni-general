#include "Cabeca.hpp"

Cabeca::Cabeca(GLfloat radius, GLint slices, GLint stacks){
    this -> radius = radius;
    this -> slices = slices;
    this -> stacks = stacks;
    this -> quadric = gluNewQuadric();

    this -> olho_dir = new Olho(0.05, 20, 20, -1);
    this -> olho_esq = new Olho(0.05, 20, 20, 1);

    this -> boca = new Boca(0.05, 0.05, 0.1, 20, 20);
}

void Cabeca::draw(){
    glPushMatrix();
        glColor3f(0.75, 0.5, 0.25);
        glTranslatef(0, 0.0, 1.2);
        gluSphere(this -> quadric, this -> radius, this -> slices, this -> stacks);

        this -> olho_dir -> draw();
        this -> olho_esq -> draw();

        this -> boca -> draw();
    glPopMatrix();
}
