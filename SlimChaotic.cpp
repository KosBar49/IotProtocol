#include "SlimChaotic.h"
#include <string.h>
#include <iostream>

using namespace std;

#define INT_BITS 8

SlimChaotic::SlimChaotic(float u_, float x_)
{
    x = x_;
    xt = x_;
    u = u_;
}

uint8_t SlimChaotic::getMantissa(float f)
{
    uint8_t bytes[4];
    memcpy(&bytes, &f, sizeof(f));
    return bytes[0];
}

float SlimChaotic::genNextElem()
{
    x = u*x*(1 - x);
    return x;
}

void SlimChaotic::cipherDataSimple(uint8_t* data_, uint8_t len_){
    uint8_t seqElem;
    seqElem = getMantissa(genNextElem());
    for (int i = 0; i < len_; i++)
    {
        seqElem = getMantissa(genNextElem());
        data_[i] = data_[i] ^ seqElem;
    }
}

float SlimChaotic::genNextTentElem()
{
    if (xt < 0.5){
        xt = 1.99*xt;
    }
    else {
        xt = 1.99*(1 - xt);
    }
    return xt;
}

int leftRotate(int n, unsigned int d)
{

    /* In n<<d, last d bits are 0. To
     put first 3 bits of n at
    last, do bitwise or of n<<d
    with n >>(INT_BITS - d) */
    return (n << d)|(n >> (INT_BITS - d));
}

/*Function to right rotate n by d bits*/
int rightRotate(int n, unsigned int d)
{
    /* In n>>d, first d bits are 0.
    To put last 3 bits of at
    first, do bitwise or of n>>d
    with n <<(INT_BITS - d) */
    return (n >> d)|(n << (INT_BITS - d));
}

void SlimChaotic::cipherDataComplex(uint8_t* data_, uint8_t len_){
    uint8_t seqElem;
    int rotation;

    for (int i = 0; i < len_; i++)
    {
        seqElem = getMantissa(genNextElem());
        rotation = int(getMantissa(genNextTentElem()) >> 5 );
        cout << "rotation: " << rotation << endl;
        data_[i] = data_[i] ^ seqElem;

        if (rotation < 4){
            data_[i] = leftRotate(data_[i],rotation);
        }
        else{
            data_[i] = rightRotate(data_[i],rotation);
        }
    }
}


void SlimChaotic::cipherDataComplexDecrypt(uint8_t* data_, uint8_t len_){

    uint8_t seqElem;
    int rotation;

    for (int i = 0; i < len_; i++)
    {
        seqElem = getMantissa(genNextElem());
        rotation = int(getMantissa(genNextTentElem()) >> 5 );
        cout << "rotation: " << rotation << endl;
        if (rotation < 4){
            data_[i] = rightRotate(data_[i], rotation);
        }
        else{
            data_[i] = leftRotate(data_[i],rotation);
        }

        data_[i] = data_[i] ^ seqElem;

    }
}

void SlimChaotic::setX(float x_)
{
    x = x_;
    xt = x_;
}

void SlimChaotic::showData(uint8_t* data, uint8_t len)
{
    for (int i = 0; i < len ; i++)
    {
        cout << ((char) data[i]);
        cout << ": ";
        for (int j=7; j >=0; j--)
        {
            cout << ((data[i] >> j) & 0X01);
        }
        cout << endl;
    }
}
