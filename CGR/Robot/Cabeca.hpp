#ifndef CABECA_HPP
#define CABECA_HPP

#include "Olho.hpp"
#include "Boca.hpp"

class Cabeca {
private:
    GLUquadricObj *quadric;
    GLfloat radius;
    GLint slices, stacks;

    Olho *olho_dir;
    Olho *olho_esq;

    Boca *boca;
public:
    Cabeca(GLfloat radius, GLint slices, GLint stacks);
    void draw();
};

#endif
