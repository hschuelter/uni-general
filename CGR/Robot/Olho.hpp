#ifndef OLHO_HPP
#define OLHO_HPP

#include <cstdlib>
#include <math.h>
#include <GL/freeglut.h> 	// sudo apt-get install freeglut3-dev
#include <GL/glut.h>		// sudo apt-get install libglew-dev
#include <GL/gl.h>

class Olho {
private:
    GLUquadricObj *quadric;
    GLfloat radius;
    GLint slices, stacks;
    int sentido;
public:
    Olho(GLfloat radius, GLint stack, GLint slices, int sentido);
    void draw();
};

#endif
