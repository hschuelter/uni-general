#include <stdlib.h>
#include <ctime>
#include <cmath>
#include <unistd.h>
#include <iostream>

#include "Particle.hpp"

Particle::Particle(){
    this -> x = x;
    this -> y = y;
    this -> lifespan = this -> _lifespan = rand() % 400 + 100;
    this -> angle = (rand() % 60) - 30;
    double vel = (double)(rand() % 100) / 7500.0 + (double)(100 / 7500.0);
    this -> vx = sin(angle * M_PI / 180.0) * vel;
    this -> vy = cos(angle * M_PI / 180.0) * vel;
    this -> ang = 0;
}

void Particle::updateX(double _x){
    this -> x += _x;
}

void Particle::updateY(double _y){
    if(this -> y + _y > 0){
        this -> y += _y;
    }
}

void Particle::update_lifespan(double v){
    this -> _lifespan += v;
}

void Particle::updateVX(double v){
    if(abs(this -> vx) < 0.005){
        this -> vx += v;
    }
}

void Particle::updateVY(double v){
    if(abs(this -> vy) < 0.005){
        this -> vy += v;
    }
}

double Particle::getVX(){
    this -> ang += 5;
    return this -> vx;
}
double Particle::getVY(){
    return this -> vy;
}
int Particle::getLifespan(){
    return this -> lifespan;
}
int Particle::get_lifespan(){
    return this -> _lifespan;
}
double Particle::getX(){
    return this -> x;
}

double Particle::getY(){
    return this -> y;
}

double Particle::distance(){
    return sqrt(this -> x * this -> x + this -> y * this -> y);
}

double Particle::getAng(){
    return this -> ang;
}
