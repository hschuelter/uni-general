// g++ boneve.cpp -lglut -lGL -lGLU -o boneve && ./boneve

#include "utils.hpp"

float angle = 0.0;

GLUquadricObj *quadric;
Robot *robot;

void drawFunction(){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(0.0, 5.0, 1.0,
              0.0, 0.0, 1.0,
              0.0, 0.0, 1.0);

    angle += 0.5;

    glRotated(angle,0,0,1);

    /* Background */
    glPushMatrix();
        glColor3f(0.3, 0.3, 0.9);
        glTranslatef(0.0, 0.0, 0);
        glutWireSphere(8, 20,20);
    glPopMatrix();
    /* Stand */
    glPushMatrix();
        glColor3f(0.30, 0.12, 0.0);
        glTranslatef(0,0,-0.80);
        glutSolidCylinder(1.5, 0.2, 20, 20);
    glPopMatrix();

    robot -> draw();
    robot -> update();

    glFlush();
    glutSwapBuffers();
}

void initialize(){

    glMatrixMode(GL_PROJECTION);
    glViewport(0, 0, 800, 600);
    glLoadIdentity();
    GLfloat aspect = (GLfloat) 800 / 600;
    gluPerspective(45, aspect, 2.0f, 15.0f);
    glMatrixMode(GL_MODELVIEW);
    glShadeModel( GL_SMOOTH );
    glClearDepth( 1.0f );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc( GL_LEQUAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
    glClearColor(0.0, 0.0, 0.0, 1.0);

    robot = new Robot(0.35, 0.35, 1, 20, 20);

    /*
    GLfloat mat_shininess[] =  { 50.0 };
    GLfloat mat_specular[] =   { 0.75, 0.75, 0.75, 0.75 };

    GLfloat light_ambient[] =  {  0.3,  0.3,  0.9, 1.0 };
    GLfloat light_diffuse[] =  {  1.0,  1.0,  1.0, 1.0 };
    GLfloat light_specular[] = {  1.0,  1.0,  1.0, 1.0 };
    GLfloat light_position[] = {  10.0,  2.0,  10.0, 0.0 };

    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    */

}

int main(int argc, char* argv[]){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize(800,600);
    glutCreateWindow("Robot");


    glutDisplayFunc(drawFunction);
    glutIdleFunc(drawFunction);

    initialize();

    glutMainLoop();
    return 0;
}
