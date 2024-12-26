#include "SimpleMap.h"

SimpleMap::SimpleMap(uint32_t x_){
    x = x_;
}

void SimpleMap::setX(uint32_t x_){
    x = x_;
}

uint32_t SimpleMap::nextElem() {
    x = x * ( 1 + x ) + 1;
    return x;
}

void SimpleMap::iterate(int iter){
    for(int i = 0; i < iter; i++){
        this->nextElem();
    }
}

uint32_t SimpleMap::getX(){
    return x;
}
