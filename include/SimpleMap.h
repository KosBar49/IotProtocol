#include <stdint.h>

#ifndef SIMPLEMAP_H_INCLUDED
#define SIMPLEMAP_H_INCLUDED

class SimpleMap
{
    uint32_t x;

public:
    SimpleMap(uint32_t x); 
    uint32_t nextElem();
    void iterate(int iter);
    void setX(uint32_t x);
    uint32_t getX();
};

#endif // SIMPLEMAP_H_INCLUDED
