#include "LogisticMap.h"


LogisticMap::LogisticMap(float x_, float u_){
    x = x_;
    u = u_;
}

void LogisticMap::setU(float u_){
    u = u_;
}

void LogisticMap::setX(float x_){
    x = x_;
}

float LogisticMap::nextElem(){
    x = x * ( k - x ) * u;
    return x;
}

void LogisticMap::iterate(int iter){
    for(int i = 0; i < iter; i++){
        this->nextElem();
    }
}

float LogisticMap::getU(){
    return u;
}

float LogisticMap::getX(){
    return x;
}
