#include "Item.hpp"

Item::Item(){
    this->features = vector<double>(2);
    this->features[0] = 0;
    this->features[1] = 0;
    this->color = 0;
}

Item::Item(double a, double b, int c){
    this->features = vector<double>(2);
    this->features[0] = a;
    this->features[1] = b;

    this->color = c;
}
