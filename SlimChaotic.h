#include <stdint.h>
#ifndef SLIMCHAOTIC_H_INCLUDED
#define SLIMCHAOTIC_H_INCLUDED

class SlimChaotic
{
    float u;
    float x;
    float xt;
    uint8_t getMantissa(float seqElem);
    uint8_t calcCipher(uint8_t data);

public:
    SlimChaotic(float u, float x);
    void setX(float x);
    uint8_t* getData(uint8_t len);

    void cipherDataSimple(uint8_t* data_, uint8_t len_);
    void cipherDataComplex(uint8_t* data_, uint8_t len_);
    void cipherDataComplexDecrypt(uint8_t* data_, uint8_t len_);
    float genNextTentElem();
    float genNextElem();
    void showData(uint8_t* data, uint8_t len);
    void showChaotic();
};

#endif // SLIMCHAOTIC_H_INCLUDED
