#ifndef BOCA_HPP
#define BOCA_HPP

#include <cstdlib>
#include <math.h>
#include <GL/freeglut.h> 	// sudo apt-get install freeglut3-dev
#include <GL/glut.h>		// sudo apt-get install libglew-dev
#include <GL/gl.h>

class Boca {
private:
    GLUquadricObj *quadric;
    GLfloat base, top, height;
    GLint slices, stacks;
public:
    Boca(GLfloat base, GLfloat top, GLfloat height, GLint slices, GLint stacks);
    void draw();
};

#endif
