// g++ boneve.cpp -lglut -lGL -lGLU -o boneve.out && ./boneve.out 
#include "utils.hpp"

float angle = 0.0;

void drawFunction(){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(0.0, 5.0, 1.0,
              0.0, 0.0, 1.0,
              0.0, 0.0, 1.0);

    angle += 0.5;

    glRotated(angle,0,0,1);

    glPushMatrix();
        /* Background */
        glColor3f(0.3, 0.3, 0.9);
        glTranslatef(0.0, 0.0, 0);
        glutWireSphere(8, 20,20);

        /* Stand */
        glPushMatrix();
            glColor3f(0.30, 0.12, 0.0);
            glTranslatef(0,0,-0.65);
            glutSolidCylinder(1.5, 0.2, 20, 20);
        glPopMatrix();

        /* Body */
        glColor3f(0.85, 0.85, 0.85);
        glTranslatef(0.0, 0.0, 0.2);
        glutSolidSphere(0.75, 20, 20);

        /* Left Arm */
        glPushMatrix();
            glColor3f(0.5, 0.3, 0.0);
            glRotated(50,0,1,0);
            glutSolidCylinder(0.035, 1.5, 20,20);
            
            glPushMatrix();
                glTranslatef(0,0,1.1);
                glRotated(30, 0, 1, 0);
                glutSolidCylinder(0.02, 0.3, 20,20);
            glPopMatrix();

        glPopMatrix();

        /* Right Arm */
        glPushMatrix();
            glRotated(50,0,-1,0);
            glutSolidCylinder(0.035, 1.5, 20,20);
        glPopMatrix();

        /* Botoes */
        glColor3f(0,0,0);

        glPushMatrix();
            glTranslatef(0.0, 0.69, -0.1);
            glutSolidSphere(0.08, 20, 20);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0, 0.69, 0.1);
            glutSolidSphere(0.08, 20, 20);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0, 0.63, 0.3);
            glutSolidSphere(0.08, 20, 20);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0, 0.50, 0.5);
            glutSolidSphere(0.08, 20, 20);
        glPopMatrix();

        /* Head */
        glColor3f(0.85, 0.85, 0.85);
        glTranslatef(0.0, 0.0, 1.1);
        glutSolidSphere(0.45, 20, 20);

        /* Nose */
        glPushMatrix();
            glColor3f(1, 0.3, 0.0);
            glRotated(90, -1, 0, 0);
            glTranslatef(0.0, 0, -0.05);
            glutSolidCone(0.12, 1.0 ,20, 20);
        glPopMatrix();

        /* Left Eye */
        glPushMatrix();
            glColor3f(0,0,0);
            glTranslatef(0.14, 0.36, 0.16);
            glutSolidSphere(0.08, 20, 20);
        glPopMatrix();

        /* Right Eye */
        glPushMatrix();
            glColor3f(0,0,0);
            glTranslatef(-0.14, 0.36, 0.16);
            glutSolidSphere(0.08, 20, 20);
        glPopMatrix();

        /* Top Hat */ 

        /* Yellow Ring */
        glPushMatrix();
            glColor3f(0.8,0.8,0);
            glTranslatef(0,0,0.4);
            glutSolidCylinder(0.40, 0.30, 20, 20);
        glPopMatrix();

        /* Lower Ring */
        glPushMatrix();            
            glColor3f(0.20,0.02,0.35);
            glTranslatef(0,0,0.35);
            glutSolidCylinder(0.7, 0.07, 20, 20);
        glPopMatrix();

        /* Hat */
        glPushMatrix();
            glTranslatef(0,0,0.4);
            glutSolidCylinder(0.37, 0.8, 20, 20);
        glPopMatrix();


    glPopMatrix();

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
    glDepthFunc( GL_LEQUAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
    glClearColor(0.0, 0.0, 0.0, 1.0);

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
    glutCreateWindow("Snowman");


    glutDisplayFunc(drawFunction);
    glutIdleFunc(drawFunction);

    initialize();

    glutMainLoop();
    return 0;
}
