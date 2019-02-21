#ifndef ANTEBRACO_HPP
#define ANTEBRACO_HPP

#include <cstdlib>
#include <math.h>
#include <GL/freeglut.h> 	// sudo apt-get install freeglut3-dev
#include <GL/glut.h>		// sudo apt-get install libglew-dev
#include <GL/gl.h>

class Antebraco {
private:
    GLUquadricObj *quadric;
    GLfloat base, top, height;
    GLint slices, stacks;
    int sentido, ang, max_ang, min_ang, dir_vel;
public:
    Antebraco(GLfloat base, GLfloat top, GLfloat height, GLint slices, GLint stacks, int sentido);
    void draw();
    void update();
};

#endif
