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
    uint8_t* getData(uint8_t len);

    void cipherDataSimple(uint8_t* data_, uint8_t len_);
    void cipherDataComplex(uint8_t* data_, uint8_t len_);
    void cipherDataComplexDecrypt(uint8_t* data_, uint8_t len_);
    double genNextTentElem();
    double genNextElem();
    void showData(uint8_t* data, uint8_t len);
    void showChaotic();
};

#endif // DOUBLECHAOTIC_H
