#ifndef LOGISTICMAP_H_INCLUDED
#define LOGISTICMAP_H_INCLUDED

class LogisticMap
{
    float u;
    float x;
    const float k = 1;

public:
    LogisticMap(float x, float u);
    float nextElem();
    void setX(float x);
    void setU(float u);
    float getX();
    float getU();
    void iterate(int iter);
};

#endif // LOGISTICMAP_H_INCLUDED
