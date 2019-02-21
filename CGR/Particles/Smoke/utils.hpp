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

#include "Particle.hpp"

using namespace std;

#define WIDTH  1280
#define HEIGHT 720
#define PI 3.14159265358979323846 
#define MAX_PART 40000

#define SIDES 8
#define ROTATION 0.05
#define KONOHA false

typedef vector<Particle> v1d; 

void drawFunction();
void bonfire();
void drawParticle(Particle &p, int sides);

void updateParticles();

#endif