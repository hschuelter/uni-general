#include "utils.hpp"

extern float angle;
extern GLuint texture;

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

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);


	//makeLight();
}

void makeLight(){
    GLfloat mat_shininess[] =  { 50.0 };
    GLfloat mat_specular[] =   { 0.75, 0.75, 0.75, 0.75 };

    GLfloat light_ambient[] =  {  0.3,  0.3,  0.3, 1.0 };
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
}

GLuint loadTexture( const char * filename ){
	GLuint texture;
	int width, height;
	unsigned char * data;

	FILE * file;
	file = fopen( filename, "rb" );

	if ( file == NULL )
		return 0;
	width = 256;
	height = 256;

	data = (unsigned char *)malloc( width * height * 3 );
	fread( data, width * height * 3, 1, file );
	fclose( file );

	for(int i = 0; i < width * height ; i++){
		int index = i*3;
		unsigned char B,R;
		B = data[index];
		R = data[index+2];

		data[index] = R;
		data[index+2] = B;
	}

	glGenTextures( 1, &texture );
	glBindTexture( GL_TEXTURE_2D, texture );
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );


	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
	gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
    cout << "Oi" << endl;

    glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, data );
	free( data );
	return texture;
}

void drawFunction(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glLoadIdentity();

    gluLookAt(10.0, 10.0, 1.0,
              0.0, 0.0, 1.0,
              0.0, 0.0, 1.0);

    angle += 0.10;
    glRotated(angle, 0.0 , 1.0 , 0.5 );
    float scale = 0.75;


    /* ============ Drawing ============ */
    glPushMatrix();

    	/* BACKGROUND */
    	/*
	    glPushMatrix();
			glColor3f(0.3, 0.3, 0.9);
	        glTranslatef(0.0, 0.0, 0);
	        glutWireSphere(8, 30,30);
		glPopMatrix();
		*/


		glPushMatrix();
			glScalef(scale,scale,scale);
			drawCube();
		glPopMatrix();

	glPopMatrix();
	/* ============ Drawing ============ */

    glFlush();
    glutSwapBuffers();
}

void drawCube(){
	glEnable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);

			// White Face
			glColor3f(1.0f,1.0f,1.0f);
		    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, 1.0f,-1.0f);
	        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f,-1.0f);
	        glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	        glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 1.0f);

		    // Yellow Face
		    glColor3f(1.0f,1.0f,0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f,-1.0f, 1.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 1.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,-1.0f,-1.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,-1.0f,-1.0f);

		    // Red Face
		    glColor3f(1.0f,0.0f,0.0f);
		    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, 1.0f, 1.0f);
		    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
		    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,-1.0f, 1.0f);
		    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,-1.0f, 1.0f);

		    // Orange Face
			glColor3f(1.0f,0.5f,0.0f);
		    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f,-1.0f,-1.0f);
		    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f,-1.0f,-1.0f);
		    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f,-1.0f);
		    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, 1.0f,-1.0f);

		    // Green Face
		    glColor3f(0.0f,0.80f,0.0f);
		    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
		    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, 1.0f,-1.0f);
		    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,-1.0f,-1.0f);
		    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,-1.0f, 1.0f);

		    // Blue Face
		    glColor3f(0.2f,0.2f,1.0f);
		    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, 1.0f,-1.0f);
		    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, 1.0f, 1.0f);
		    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,-1.0f, 1.0f);
		    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,-1.0f,-1.0f);

	    glEnd();
    glDisable(GL_TEXTURE_2D);

    glFlush();
}
