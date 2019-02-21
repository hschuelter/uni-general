#ifndef _BIGINTHPP_
#define _BIGINTHPP_

#include "utils.hpp"

class BigInt{
public:
    string number;
    int size;

    BigInt();
    BigInt(string number);

    void print();
};


#endif
