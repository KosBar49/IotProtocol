#include "DoubleMap.h"

DoubleMap::DoubleMap(double x_, double u_)
{
    //ctor
    x = x_;
    u = u_;
}

void DoubleMap::setU(double u_){
    u = u_;
}

void DoubleMap::setX(double x_){
    x = x_;
}

double DoubleMap::nextElem(){
    x = x * ( k - x) * u;
    return x;
}

void DoubleMap::iterate(int iter){
    for(int i = 0; i < iter; i++){
        this->nextElem();
    }
}

double DoubleMap::getU(){
    return u;
}

double DoubleMap::getX(){
    return x;
}

DoubleMap::~DoubleMap()
{
    //dtor
}
