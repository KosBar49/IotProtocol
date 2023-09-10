#include "ChaoticCipher.h"
#include <string.h>
#include <math.h>
#include <iostream>
#include <iomanip>

using namespace std;

ChaoticCipher::ChaoticCipher(float u_, float x_)
{
    x = x_;
    u = u_;
    x_min = x_;
    x_max = x_;
    //weights = new float[8*8];
}

float ChaoticCipher::getX()
{
    return x;
}

float ChaoticCipher::getU()
{
    return u;
}

float ChaoticCipher::getMin()
{
    return x_min;
}

float ChaoticCipher::getMax()
{
    return x_max;
}

void ChaoticCipher::setX(float x_)
{
    x = x_;
    x_min = x_;
    x_max = x_;
}

void ChaoticCipher::genChaotic()
{
    for (int i = 0; i < len ; i++)
    {
        chaoticSeq[i] = x;
        genNextElem();
    }
}

uint8_t ChaoticCipher::normElem(float seqElem)
{
    int result = fabs( (( seqElem - x_min) / x_max * 255));
    return (uint8_t)result;
}

uint8_t ChaoticCipher::getMantissa(float f)
{
    uint8_t bytes[4];
    memcpy(&bytes, &f, sizeof(f));
    return bytes[0];
}

void ChaoticCipher::setWeights(uint8_t elem)
{
    for (int i = 0; i <= 7; i++)
    {
        for (int j = 0; j <= 7; j++)
        {
            weights[i][j]= 0;
            if ( elem & ( 1<< i) )
            {
                biases[i] = 0.5;
                if (j == i)
                {
                    weights[i][j]= -1;
                }
            }
            else
            {
                biases[i] = -0.5;
                if (j == i)
                {
                    weights[i][j] = 1;
                }
            }
        }
    }
}

uint8_t ChaoticCipher::calcCipher(uint8_t data_)
{
    float sum;

    for (int i = 0; i <= 7; i++)
    {
        sum = 0;
        for (int j = 0; j <= 7; j++)
        {
            if ( data_ & ( 1 << i ))
            {
                sum += weights[i][j];
            }

        }
        sum += biases[i];
        if (sum >= 0)
        {
            data_ = data_ | ( 1 << i);
        }
        else
        {
            data_ = data_ & ~( 1 << i);
        }

    }
    return data_;
}



void ChaoticCipher::cipherDataNorm(uint8_t* data_, uint8_t len_)
{
    this->len = len_;
    genChaotic();
    uint8_t seqElem;
    for (int i = 0; i < this->len; i++)
    {
        // normalize the elem of the chaotic sequence
        seqElem = normElem(chaoticSeq[i]);
        setWeights(seqElem);
        data_[i] = calcCipher(data_[i]);
    }
}

void ChaoticCipher::cipherDataSimple(uint8_t* data_, uint8_t len_){
    uint8_t seqElem;
    genChaotic();
    for (int i = 0; i < len_; i++)
    {
        // normalize the elem of the chaotic sequence

        seqElem = getMantissa(chaoticSeq[i]);
        for (int j = 0; j <= 7; j ++){
            cout << ((seqElem >> j) & 0X01) ;
        }
        cout << endl;
        data_[i] = data_[i] ^ seqElem;
    }

}

void ChaoticCipher::cipherWithFreezeWeights(uint8_t* data_, uint8_t len_)
{
    for (int i = 0; i < this->len; i++)
    {
        data_[i] = calcCipher(data_[i]);
    }
}

void ChaoticCipher::cipherDataMantissa(uint8_t* data_, uint8_t len_)
{
    this->len = len_;
    genChaotic();
    uint8_t seqElem;
    for (int i = 0; i < this->len; i++)
    {
        seqElem = getMantissa(chaoticSeq[i]);
        setWeights(seqElem);
        data_[i] = calcCipher(data_[i]);
    }
}


void ChaoticCipher::presetX()
{
    x = u*x*(1.0 - x);
    x_min = x;
    x_max = x;
}

float ChaoticCipher::genNextElem()
{
    if (x > x_max)
    {
        x_max = x;
    }
    if (x < x_min)
    {
        x_min = x;
    }
    x = u*x*(1.0 - x);
    return x;
}

void ChaoticCipher::showChaotic()
{
    for (int i = 0; i < this-> len ; i ++)
    {
        cout <<fixed<<std::setprecision(10) << chaoticSeq[i] << " ";
    }
    cout << endl;
}

void ChaoticCipher::showData(uint8_t* data, uint8_t len)
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
