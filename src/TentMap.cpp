#include "TentMap.h"

TentMap::TentMap(float x_, float u_){
    x = x_; 
    u = u_; 
}

void TentMap::setU(float u_){
    u = u_; 
}

void TentMap::setX(float x_){
    x = x_; 
}

float TentMap::nextElem(){
    if(x < 0.5){
        x = x * u; 
    }
    else {
        x = u * ( 1 - x );
    }
    return x; 
}

float TentMap::getU(){
    return u;
}

float TentMap::getX(){
    return x; 
}

void TentMap::iterate(int iter){
    for(int i = 0; i < iter; i++){
        this->nextElem();
    }
}