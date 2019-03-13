#ifndef ITEM_HPP
#define ITEM_HPP


#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> v1d;
typedef vector<v1d> v2d;

class Item{
    public:
        vector<double> features;
        int color;

        Item();
        Item(double x, double y, double z, double w, int c);
};

#endif
