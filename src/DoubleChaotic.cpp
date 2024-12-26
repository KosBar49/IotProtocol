#include "DoubleChaotic.h"
#include <math.h>
#include <string.h>

DoubleChaotic::DoubleChaotic(double u_, double x_)
{
    x = x_;
    xt = x_;
    u = u_;
}

void DoubleChaotic::cipherDataSimple(uint8_t* data_, uint8_t len_){

    uint8_t seqElem[8];

    int len = floor(len_ / 5);
    int i = 0;
    double f;
    while(len){
        f = genNextTentElem();
        memcpy(&seqElem, &f, 8);


        data_[i] = data_[i] ^ seqElem[0];
        data_[i+1] = data_[i+1] ^ seqElem[1];
        data_[i+2] = data_[i+2] ^ seqElem[2];
        data_[i+3] = data_[i+3] ^ seqElem[3];
        data_[i+4] = data_[i+4] ^ seqElem[4];
        len -= 1;
        i += 5;
    }
    f = genNextTentElem();
    memcpy(&seqElem, &f, 8);
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

void DoubleChaotic::setX(double x_)
{
    x = x_;
    xt = x_;
}
