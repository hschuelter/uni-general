#include "Item.hpp"

Item::Item(){
    this->features = vector<double>(4);
    this->features[0] = 0;
    this->features[1] = 0;
    this->features[2] = 0;
    this->features[3] = 0;
    this->color = 0;
}

Item::Item(double x, double y, double z, double w, int c){
    this->features = vector<double>(4);
    this->features[0] = x;
    this->features[1] = y;
    this->features[2] = z;
    this->features[3] = w;

    this->color = c;
}
