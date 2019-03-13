#ifndef ANT_HPP
#define ANT_HPP

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

#include "Item.hpp"
#define INFINITE 0x3f3f3f3f

using namespace std;


typedef vector<int> v1d;
typedef vector<v1d> v2d;

typedef vector<Item> v1I;
typedef vector<v1I> v2I;

class Ant{
    public:
        int raio;
        int x;
        int y;
        int last_move;
        double alpha;
        double sigma;

        bool carrying;
        bool dead;

        Item item;

        Ant();
        Ant(int r, int x, int y, double alpha, double sigma);

        void move(v2I& grid);
        float pickup(v2I& grid);
        float drop(v2I& grid);
        bool forceDrop(v2I& grid);

        double distance(Item& a, Item& b);

        void info();
};

#endif
