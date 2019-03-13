#ifndef ITEM_HPP
#define ITEM_HPP


#include <iostream>
#include <vector>
#include <utility>

#include <stdlib.h>
#include <time.h>

#include <SFML/Graphics.hpp>

using namespace std;

typedef vector<int> v1d;
typedef vector<v1d> v2d;

class Item{
    public:
        vector<double> features;
        sf::Color color;

        Item();
        Item(double a, double b, sf::Color c);
};

#endif
