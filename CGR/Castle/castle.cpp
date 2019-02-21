// g++ castle.cpp -lglut -lGL -lGLU -o castle && ./castle
#include "utils.hpp"

float angle = 0.0;

int main(int argc, char* argv[]){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize(800,600);
    glutCreateWindow("Castle");


    glutDisplayFunc(drawFunction);
    glutIdleFunc(drawFunction);

    initialize();


    glutMainLoop();
    return 0;
}

void drawFunction(){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(0.0, 5.0, 1.0,
              0.0, 0.0, 1.0,
              0.0, 0.0, 1.0);

    angle += 0.5;

    glRotated(angle,0,0,1);

    glPushMatrix(); // Starto

        /* Background */
        glPushMatrix();
            glColor3f(0.2, 0.95, 0.2);
            glutWireSphere(8, 20, 20);
        glPopMatrix();

        /* Stand */
        glPushMatrix();
            glColor3f(0.20, 0.08, 0.0);
            glutSolidCylinder(1.5, 0.2, 20, 20);
        glPopMatrix();

        /* Castle */
        
        glPushMatrix();
            glScalef(0.35,0.35,0.35);
            glTranslatef(2.5,-2,0.3);
            makeCastle();
        glPopMatrix();
        

    glPopMatrix();


    glFlush();
    glutSwapBuffers();
}

void initialize(){

    glMatrixMode(GL_PROJECTION);
    glViewport(0,0, 800, 600);

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

}

void glutEntrance(void){

    glColor3f(0.50, 0.35, 0.15);
    glTranslatef(0, 0, 1.25);

    /* Gate */
    glScalef(1.5, 1.5, 2.5);
    glutSolidCube(1);


    /* Roof */
    glPushMatrix();
        glColor3f(0.50, 0.2, 0.05);
        glTranslatef(0,0,0.5);
        glutSolidCone(0.8, 0.5, 20, 20);
    glPopMatrix();

    glPushMatrix();
        entranceWindows();
    glPopMatrix();

}

void entranceWindows(){
    glPushMatrix();
        glColor3f(0.05,0.05,0.05);
        glTranslatef(0,0,-0.15);
        glScalef(1.005, 0.25, 0.25);
        glutSolidCube(1);
    glPopMatrix();

    /* Windows */

    glPushMatrix();
        glColor3f(0.05,0.05,0.05);
        glTranslatef(0,0.40,0.45);

        glScalef(1.005, 0.10, 0.07);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.05,0.05,0.05);
        glTranslatef(0,0.13,0.45);

        glScalef(1.005, 0.10, 0.07);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.05,0.05,0.05);
        glTranslatef(0,-0.13,0.45);

        glScalef(1.005, 0.10, 0.07);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.05,0.05,0.05);
        glTranslatef(0,-0.4,0.45);

        glScalef(1.005, 0.10, 0.07);
        glutSolidCube(1);
    glPopMatrix();

    /* End of Windows */


    /* Main Window*/

    glPushMatrix();
        glColor3f(0.05,0.05,0.05);
        glTranslatef(0,0,0.175);

        glScalef(1.005, 0.10, 0.15);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.05,0.05,0.05);
        glTranslatef(-0.505,0,0.25);
        glRotated(90, 0, 1 , 0);

        //glScalef(0.10, 0.10, 1.005);
        glutSolidCylinder(0.05,1.006,20,20);
    glPopMatrix();


}

void glutSolidCastleTower(){

        glColor3f(0.50, 0.35, 0.15);
        glTranslatef(0, 0, 0.1);
        glutSolidCylinder(0.5, 1.5, 20, 20);


            /* Roof + Flag */
            glPushMatrix();
                glColor3f(0.50, 0.2, 0.05); /* Roof */
                glTranslatef(0,0,1.5);
                glutSolidCone(0.6, 0.8, 20, 20);


                glutSolidCylinder(0.01, 1.3, 20, 20); /* Flag */

                glRotated(45,0,0,1);
                glTranslatef(0.095, 0.0, 1.3);

                glScalef(2, 0.1, 1);
                glutSolidCube(0.1);

            glPopMatrix();

            glPushMatrix();
                glutMakeWindows();

                glRotated(22.5, 0, 0, 1);
                glutMakeWindows();
            glPopMatrix();
}

void glutMakeWindows(){


            /* Windows Y */

            glColor3f(0.1, 0.1, 0.1);
            glPushMatrix();
                glTranslatef(0.0, 0.0, 1.4);

                glScalef(1,10,1);
                glutSolidCube(0.1);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0, 0, 1.1);

                glScalef(1,10,1.5);
                glutSolidCube(0.1);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0, 0.0, 0.8);

                glScalef(1,10,1);
                glutSolidCube(0.1);
            glPopMatrix();



            /* Windows X */
            glPushMatrix();
                glTranslatef(0.0, 0.0, 1.4);

                glScalef(10,1,1);
                glutSolidCube(0.1);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0, 0, 1.1);

                glScalef(10,1,1.5);
                glutSolidCube(0.1);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0, 0.0, 0.8);

                glScalef(10,1,1);
                glutSolidCube(0.1);
            glPopMatrix();



            /* Windows X, Y  */
            glPushMatrix();
                glTranslatef(0.0, 0.0, 1.4);
                glRotated(45, 0, 0, 1);

                glScalef(10,1,1);
                glutSolidCube(0.1);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0, 0, 1.1);
                glRotated(45, 0, 0, 1);

                glScalef(10,1,1.5);
                glutSolidCube(0.1);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0, 0.0, 0.8);
                glRotated(45, 0, 0, 1);

                glScalef(10,1,1);
                glutSolidCube(0.1);
            glPopMatrix();



            /* Windows -X, Y  */
            glPushMatrix();
                glTranslatef(0.0, 0.0, 1.4);
                glRotated(-45, 0, 0, 1);

                glScalef(10,1,1);
                glutSolidCube(0.1);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0, 0, 1.1);
                glRotated(-45, 0, 0, 1);

                glScalef(10,1,1.5);
                glutSolidCube(0.1);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0, 0.0, 0.8);
                glRotated(-45, 0, 0, 1);

                glScalef(10,1,1);
                glutSolidCube(0.1);
            glPopMatrix();

}

void glutMakeWalls(){
    glColor3f(0.50, 0.35, 0.15);

    glPushMatrix();
        glRotated(45,0,0,1);
        glTranslatef(2,0,0.35);

        glScalef(40,1,6);
        glutSolidCube(0.1);
    glPopMatrix();

        /* Base */
        glColor3f(0.50, 0.2, 0.05);

        /* Parede em si */
        glPushMatrix();
            glRotated(45,0,0,1);
            glTranslatef(1.25,0,0.65);

            glScalef(150, 25 ,1);
            glutSolidCube(0.01);
        glPopMatrix();

        /* Lado 1 */
        glPushMatrix();
            glRotated(45,0,0,1);
            glTranslatef(2,0,0.65);

            glTranslatef(0, 0.125, 0);
            glRotated(120, 1, 0, 0);
            glTranslatef(0, 0.125, 0);

            glScalef(400, 25 ,1);
            glutSolidCube(0.01);
        glPopMatrix();

        /* Lado 2*/
        glPushMatrix();
            glRotated(45,0,0,1);
            glTranslatef(2 , 0 , 0.65);

            glTranslatef(0, -0.125, 0);
            glRotated(-120, 1, 0, 0);
            glTranslatef(0, -0.125, 0);

            glScalef(400, 25 ,1);
            glutSolidCube(0.01);
        glPopMatrix();
}

void makeCastle(){


            /* Tower no.1 */
            glutSolidCastleTower();

            /* Walls */
            glPushMatrix();
                glRotated(45,0,0,1);
                glutMakeWalls();


                glRotated(90,0,0,1);
                glutMakeWalls();
            glPopMatrix();

            /* Tower no.2 */

            glPushMatrix();
                glTranslatef(-4.5,0,0);
                glutSolidCastleTower();

                glRotated(45,0,0,1);
                glutMakeWalls();
            glPopMatrix();

            /* Tower no. 3 */
            glPushMatrix();
                glTranslatef(0,4.5,0);
                glutSolidCastleTower();

                glRotated(135,0,0,1);
                glutMakeWalls();
            glPopMatrix();

            /* Tower no. 4 */
            glPushMatrix();
                glTranslatef(-4.5,4.5,0);
                glutSolidCastleTower();
            glPopMatrix();

            /* Entrance */

            glPushMatrix();
                glTranslatef(0, 2.25, -0.08);

                glScalef(0.4, 0.4, 0.4);
                glutEntrance();
            glPopMatrix();


}
