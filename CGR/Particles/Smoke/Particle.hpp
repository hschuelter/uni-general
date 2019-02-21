#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "utils.hpp"

class Particle{

	public:
		double x, y;
		double size;
		double randMov;

		int spin;
		double angle, dx, dy;
		double lifespan;

		double red, green, blue, alpha;
		double randColor;

		Particle();
		void drawMe(int);
};

#endif