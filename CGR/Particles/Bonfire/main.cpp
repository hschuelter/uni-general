#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <random>
#include <thread>

//Minhas bibliotecas
#include "Particle.hpp"

using namespace std;

#define WIDTH 640
#define HEIGHT 480

#define MAX_PARTICLES 20000
#define WIND 0.01
#define GRAVITY 0.006
#define VERTICAL 0
#define LEFT -1
#define RIGHT 1

#define DIR RIGHT

#define ESC 27

int window;
vector<Particle> particles;

vector<Particle> sparks;

const int NUM_THREADS = 4;

void draw_Particle(Particle p){
    double percent = (p.get_lifespan() / (double)p.getLifespan());
    double radius = 0.03 * percent;
    glBegin(GL_POLYGON);
		for(double i = 0; i < 2 * M_PI; i += M_PI / 2.5){
        double aux = (p.getAng() * M_PI) / 180.0;
		    glVertex3f(p.getX() + cos(i + aux) * radius, p.getY() + sin(i + aux) * radius, 0.0);
    }
	glEnd();
}

void updateParticle(int s, int n){
    for(int i = s; i < s + n; i++){
        Particle &p = particles[i];
        if(p.get_lifespan()){
            p.updateX(p.getVX() + !VERTICAL * (rand() % 100 - 50) / 5000.0);
            p.updateY(p.getVY() + VERTICAL * (rand() % 100 - 50) / 5000.0);

            p.updateVX(!VERTICAL * DIR * WIND / 30.0);
            p.updateVY(WIND / 30.0 - GRAVITY / 20.0);

            p.update_lifespan(-1);
        } else {
            p = Particle();
        }
    }
}

long fps = 0;
time_t last;

void draw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, -0.5, -2.2);

    if(particles.size() < MAX_PARTICLES){
        for(int i = 0; i < 8; i++){
            particles.push_back(Particle());
        }
    }

    glEnable(GL_BLEND);
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    thread threads[NUM_THREADS];
    for(int i = 0; i < NUM_THREADS; i++){
        threads[i] = thread(updateParticle, i * (particles.size() / NUM_THREADS), particles.size() / NUM_THREADS);
    }

    for(int i = 0; i < NUM_THREADS; i++){
        threads[i].join();
    }

    for(Particle &p : particles){
        double percent = (p.get_lifespan() / (double)p.getLifespan());
        int ls = p.get_lifespan();
        int lo = p.getLifespan();

        //double f1 = 10.0, f2 = 80.0, f3 = 100.0;
        double f1 = 11.5;
        double ri = 0.1, gi = 0.2, bi = 0.3;
        double rs = 1, gs = 0.95, bs = 0.6;

        double rp = rs - (ri / f1) * (lo - ls);
        double gp = gs - (gi / f1) * (lo - ls);
        double bp = bs - (bi / f1) * (lo - ls);

        glColor4f(rp, gp, bp, percent);
        draw_Particle(p);
    }
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

    fps++;

    double current = glutGet(GLUT_ELAPSED_TIME);
    double t = ((current - last) * 1000.0) / (CLOCKS_PER_SEC);
    //cout << "T: " << t << endl;
    if(t >= 1.0){
        printf("FPS: %lf\n", (double)fps / t);
        last = current;
        fps = 0;
    }

    glutSwapBuffers();
}

void keyPressed(unsigned char key, int x, int y){
    if (key == ESC){
        glutDestroyWindow(window);
        exit(0);
    }
}

int main(int argc, char *argv[]){

    srand(time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);
    window = glutCreateWindow("Fire!!!");
    glutDisplayFunc(&draw);
    //glutFullScreen();
    glutIdleFunc(&draw);
    glutKeyboardFunc(&keyPressed);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_PROJECTION);

    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    gluPerspective(45.0f, (GLfloat)WIDTH/(GLfloat)HEIGHT, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);

    last = 0;

    glutMainLoop();

    return 0;
}
