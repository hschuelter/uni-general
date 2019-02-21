#ifndef CANELA_HPP
#define CANELA_HPP

#include <cstdlib>
#include <math.h>
#include <GL/freeglut.h> 	// sudo apt-get install freeglut3-dev
#include <GL/glut.h>		// sudo apt-get install libglew-dev
#include <GL/gl.h>

class Canela {
private:
    GLUquadricObj *quadric;
    GLfloat base, top, height;
    GLint slices, stacks;
    int sentido;
    GLfloat max_ang, min_ang, ang, ang_vel;
public:
    Canela(GLfloat base, GLfloat top, GLfloat height, GLint slices, GLint stacks, int sentido);
    void draw();
    void update();
};

#endif
