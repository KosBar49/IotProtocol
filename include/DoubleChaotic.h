#include <stdint.h>
#ifndef DOUBLECHAOTIC_H
#define DOUBLECHAOTIC_H


class DoubleChaotic
{
    double u;
    double x;
    double xt;
    uint8_t getMantissa(double seqElem);
    uint8_t calcCipher(uint8_t data);

public:
    DoubleChaotic(double u, double x);
    void setX(double x);
    void cipherDataSimple(uint8_t* data_, uint8_t len_);
    double genNextTentElem();
};

#endif // DOUBLECHAOTIC_H
