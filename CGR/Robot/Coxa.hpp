#ifndef COXA_HPP
#define COXA_HPP

#include "Canela.hpp"

class Coxa {
private:
    GLUquadricObj *quadric;
    GLfloat base, top, height;
    GLint slices, stacks;
    int sentido;
    GLfloat max_ang, min_ang, ang, ang_vel;

    Canela *canela;

public:
    Coxa(GLfloat base, GLfloat top, GLfloat height, GLint slices, GLint stacks, int sentido);
    void draw();
    void update();
};

#endif
