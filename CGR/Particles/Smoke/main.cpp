#include "utils.hpp"

int window;
v1d particles;

int main(int argc, char *argv[]){

    srand(time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);
    window = glutCreateWindow("particles");
    glutDisplayFunc(&drawFunction);
    glutIdleFunc(&drawFunction);
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
    glutMainLoop();

    return 0;
}