#include <stdint.h>
#ifndef CHAOTICCIPHER_H_INCLUDED
#define CHAOTICCIPHER_H_INCLUDED

class ChaoticCipher
{
    float u;
    float x;
    float x_min;
    float x_max;
    float weights[8][8];
    float biases[8];
    float chaoticSeq[64];
    uint8_t len;
    uint8_t normElem(float seqElem);
    uint8_t getMantissa(float seqElem);
    uint8_t calcCipher(uint8_t data);
    //calculate cipher using only xor operation nor pushing the bits thought the NN model
    uint8_t calcCipherSimple(uint8_t data);
    void presetX();
    void setWeights(uint8_t elem);

public:
    ChaoticCipher(float u, float x);
    void setX(float x);
    float getX();
    float getU();
    float getMin();
    float getMax();
    uint8_t* getData(uint8_t len);
    void cipherDataNorm(uint8_t* data, uint8_t len);
    void cipherDataMantissa(uint8_t* data, uint8_t len);
    void cipherDataMantissaSimple();
    void cipherWithFreezeWeights(uint8_t* data_, uint8_t len_);
    void cipherDataSimple(uint8_t* data_, uint8_t len_);
    void genChaotic();
    float genNextElem();
    void showData(uint8_t* data, uint8_t len);
    void showChaotic();
};

#endif // CHAOTICCIPHER_H_INCLUDED
