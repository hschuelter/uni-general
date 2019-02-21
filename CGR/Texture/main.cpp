#include "utils.hpp"

GLuint texture;

int window;
float angle = 0.0;

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Texture");

    glutDisplayFunc(drawFunction);
    glutIdleFunc(drawFunction);

    initialize();

    texture = loadTexture("Images/cubinho-2.bmp");

    glutMainLoop();

    return 0;
}
