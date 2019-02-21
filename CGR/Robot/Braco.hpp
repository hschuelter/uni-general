#ifndef BRACO_HPP
#define BRACO_HPP

#include "Antebraco.hpp"

class Braco {
private:
    GLUquadricObj *quadric;
    GLfloat base, top, height;
    GLint slices, stacks;
    int sentido, ang, max_ang, min_ang;
    GLfloat dir_vel;
    Antebraco *antebraco;
public:
    Braco(GLfloat base, GLfloat top, GLfloat height, GLint slices, GLint stacks, int sentido);
    void draw();
    void update();
};

#endif
