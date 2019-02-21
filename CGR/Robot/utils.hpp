#ifndef UTILS_HPP
#define UTILS_HPP

#include "Robot.hpp"
//#include "Braco.hpp"
//#include "Antebraco.hpp"
//#include "Coxa.hpp"

//#define DIR -1
//#define ESQ 1

// class Braco;
// class Antebraco;
// class Coxa;
// class Canela;
// class Corpo;

// class Robot {
// private:
//     Corpo *corpo;
//     Braco *bracos;
//     Antebraco *antebraco;
//     Coxa *coxa;
// };

/*class Corpo {
private:
    GLUquadricObj *quadric;
    GLfloat base, top, height;
    GLint slices, stacks;

    Braco *braco_dir;
    Braco *braco_esq;
public:
    Corpo(GLfloat base, GLfloat top, GLfloat height, GLint slices, GLint stacks);
    void draw();
};*/

// class Braco {
// private:
//     GLUquadricObj *quadric;
//     GLfloat base, top, height;
//     GLint slices, stacks;
//     int sentido, ang, max_ang, min_ang;
//     GLfloat dir_vel;
//     Antebraco *antebraco;
// public:
//     Braco(GLfloat base, GLfloat top, GLfloat height, GLint slices, GLint stacks, int sentido);
//     void draw();
//     void update();
// };

// class Antebraco{
// private:
//     GLUquadricObj *quadric;
//     GLfloat base, top, height;
//     GLint slices, stacks;
//     int sentido, ang, max_ang, min_ang, dir_vel;
// public:
//     Antebraco(GLfloat base, GLfloat top, GLfloat height, GLint slices, GLint stacks, int sentido);
//     void draw();
//     void update();
// };
/*
class Coxa {
private:
    GLUquadricObj *quadric;
    GLfloat base, top, height;
    GLint slices, stacks;
public:
    Coxa(GLfloat base, GLfloat top, GLfloat height, GLint slices, GLint stacks);
    void draw();
    void update();
};*/

void drawFunction();
void initialize();

#endif
