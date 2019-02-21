#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdlib.h>
#include <math.h>
#include <time.h>

/*
#include <unistd.h>
*/


using namespace std;

#define WIDTH  800
#define HEIGHT 600

void initialize();
void makeLight();
GLuint loadTexture( const char * filename );
/*================*/

void drawFunction();
void drawCube();

#endif