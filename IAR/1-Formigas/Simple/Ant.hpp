#ifndef ANT_HPP
#define ANT_HPP

#include <iostream>
#include <vector>
#include <utility>

#include "Item.hpp"

using namespace std;

typedef vector<int> v1d;
typedef vector<v1d> v2d;

class Ant{
    public:
        int raio;
        int x;
        int y;


        bool estado;

        Ant();
        Ant(int r, int x, int y);

        void move(int border, vector< vector<bool> >& ant_position);
        float lift(v2d& mat);
        float drop(v2d& mat);
        bool forceDrop(v2d& mat);

        void info();
};

#endif
