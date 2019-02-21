#ifndef CORPO_HPP
#define CORPO_HPP

#include "Braco.hpp"
#include "Coxa.hpp"
#include "Cabeca.hpp"

class Corpo {
private:
    GLUquadricObj *quadric;
    GLfloat base, top, height;
    GLint slices, stacks;

    Braco *braco_dir;
    Braco *braco_esq;

    Coxa *coxa_dir;
    Coxa *coxa_esq;

    Cabeca *cabeca;

public:
    Corpo(GLfloat base, GLfloat top, GLfloat height, GLint slices, GLint stacks);
    void draw();
    void update();
};

#endif
