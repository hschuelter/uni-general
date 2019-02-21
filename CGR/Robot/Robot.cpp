#include "Robot.hpp"

Robot::Robot(GLfloat base, GLfloat top, GLfloat height, GLint slices, GLint stacks){
    this -> corpo = new Corpo(base, top, height, slices, stacks);
}
void Robot::draw(){
    this -> corpo -> draw();
}

void Robot::update(){
    this -> corpo -> update();
}
