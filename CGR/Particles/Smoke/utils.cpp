#include "utils.hpp"

extern v1d particles;

void drawFunction(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0, -0.6, -2.2);
    glEnable(GL_BLEND);
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

    bonfire();

    glutSwapBuffers();
}

void bonfire(){
	int i;
	int sides = SIDES;

	for(i = 0; i < 5; i++){

		if ( particles.size() < MAX_PART ){
			particles.push_back( Particle() );
		}

	}

	updateParticles();

	for(Particle &p : particles)
		p.drawMe(sides);	

}


void updateParticles(){

	for(int i = 0; i < particles.size(); i++){
		particles[i].lifespan--;
		particles[i].x += particles[i].dx;
		particles[i].y += particles[i].dy;

		particles[i].spin = (particles[i].spin%360) + 1;		

		particles[i].red 	-= (0.6 + particles[i].randColor) / 175;
		particles[i].green 	-= (0.6 + particles[i].randColor) / 175;
		particles[i].blue 	-= (0.6 + particles[i].randColor) / 175; 
		particles[i].alpha 	-= (1.0) / 150;


		if(particles[i].lifespan == -1)
			particles.erase( particles.begin() + i );
		
	}
	

	
	
}