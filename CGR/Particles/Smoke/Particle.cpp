#include "utils.hpp"

Particle::Particle(){
	this -> x = 0;
	this -> y = 0;
	this -> size = 0.03;
	this -> randMov = (rand()%7 - 3) * 0.0003 ;

	this -> spin = rand()%360;
	this -> angle = rand()%90 - 45;
	this -> dx = sin( this -> angle * ( PI / 180.0)) * 0.01;
	this -> dy = cos( this -> angle * ( PI / 180.0)) * 0.01;
	
	this -> lifespan = 200;


	this -> randColor = (rand()%100 - 50)/1000.0;
	this -> red   = (0.6) + (this -> randColor / 2);
	this -> green = (0.6) + (this -> randColor / 2);
	this -> blue  = (0.6) + (this -> randColor / 2);
	this -> alpha = 1.0;
}

void Particle::drawMe(int sides){
	glColor4f(this -> red,
			  this -> green,
			  this -> blue,
			  this -> alpha);

	this -> x += this -> randMov;

	this -> size *= 1.01;

	if(KONOHA)
		glRotatef(1.0, 0.0, 0.0, 1.0);

	glBegin(GL_POLYGON);
		for(double i = 0; i < 2 * PI; i+= (2.0 * PI)/ sides ){
			double dif = ( this -> angle  * PI ) / 180.0;
			glVertex3f(this -> x + cos(i + dif + (this -> spin * ROTATION) ) * this -> size, this -> y + sin(i + dif + (this -> spin * ROTATION) ) * this -> size, 0.0);
		}
	glEnd();
}