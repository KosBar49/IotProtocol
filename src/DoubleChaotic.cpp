#include "DoubleChaotic.h"
#include <cmath>
#include <iostream>

DoubleChaotic::DoubleChaotic(double u_, double x_)
{
    x = x_;
    xt = x_;
    u = u_;
}

DoubleChaotic::~DoubleChaotic()
{
    //dtor
}

uint8_t DoubleChaotic::getMantissa(double f)
{
    uint8_t bytes[4];
    memcpy(&bytes, &f, sizeof(f));
    return bytes[0];
}

double DoubleChaotic::genNextElem()
{
    x = u*x*(1 - x);
    return x;
}

void DoubleChaotic::cipherDataSimple(uint8_t* data_, uint8_t len_){
    
    uint8_t seqElem[8];

    int len = floor(len_ / 5);
    int i = 0;

    while(len){
        memcpy(&seqElem, &genNextElem(), 8);

        
        data_[i] = data_[i] ^ seqElem[0];
        data_[i+1] = data_[i+1] ^ seqElem[1];
        data_[i+2] = data_[i+2] ^ seqElem[2];
        data_[i+3] = data_[i+3] ^ seqElem[3];
        data_[i+4] = data_[i+4] ^ seqElem[4];
        len -= 1;
        i += 5;
    }

    memcpy(&seqElem, &genNextElem(), 8);
    for (int j = 1; j <= len_ - i; j++){
        data_[i+j] = data_[i+j] ^ seqElem[j - 1];
    }
}

double DoubleChaotic::genNextTentElem()
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

void DoubleChaotic::cipherDataComplex(uint8_t* data_, uint8_t len_){
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


void DoubleChaotic::cipherDataComplexDecrypt(uint8_t* data_, uint8_t len_){

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

void DoubleChaotic::setX(double x_)
{
    x = x_;
    xt = x_;
}

void DoubleChaotic::showData(uint8_t* data, uint8_t len)
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
