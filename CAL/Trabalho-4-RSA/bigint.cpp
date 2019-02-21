#include "bigint.hpp"

BigInt::BigInt(){
    this->number = "";
    this->size = 0;
}

BigInt::BigInt(string number){
    this->number = number;
    this->size = number.size();
}

void BigInt::print(){
    cout << this->number << endl;
}
