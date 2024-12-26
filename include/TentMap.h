#ifndef TENTMAP_H_INCLUDED
#define TENTMAP_H_INCLUDED

class TentMap
{
    float u;
    float x;

public: 
    TentMap(float u, float x); 
    float nextElem();
    void setX(float x);
    void setU(float u);
    float getX();
    float getU();
    void iterate(int iter);
};

#endif //TENTMAP_H_INCLUDED