#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <random>

class Particle {
private:
    double x, y;
    int lifespan, _lifespan;
    int angle;
    double vx, vy;
    double ang;
public:
    Particle();

    void updateX(double _x);
    void updateY(double _y);
    void update_lifespan(double v);
    void updateVX(double v);
    void updateVY(double v);
    double getVX();
    double getVY();
    int getLifespan();
    int get_lifespan();
    double getX();
    double getY();
    double distance();
    double getAng();
};

#endif
