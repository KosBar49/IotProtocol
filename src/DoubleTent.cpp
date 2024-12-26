#include "DoubleTent.h"
#include <cmath>

DoubleTent::DoubleTent(double x_, double u_)
{
    //ctor
    x = x_;
    u = u_;
}

void DoubleTent::setU(double u_){
    u = u_;
}

void DoubleTent::setX(double x_){
    x = x_;
}

double DoubleTent::nextElem(){
    if ( x < c){
        x = x * u;
    }
    else {
        x = u * ( k - x);
    }
    return x;
}

void DoubleTent::iterate(int iter){
    for(int i = 0; i < iter; i++){
        this->nextElem();
    }
}

double DoubleTent::getU(){
    return u;
}

double DoubleTent::getX(){
    return x;
}

DoubleTent::~DoubleTent()
{
    //dtor
}
