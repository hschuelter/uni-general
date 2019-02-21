#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "Corpo.hpp"

class Robot {
private:
    Corpo *corpo;
public:
    Robot(GLfloat base, GLfloat top, GLfloat height, GLint slices, GLint stacks);
    void draw();
    void update();
};

#endif
