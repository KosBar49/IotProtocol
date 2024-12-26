#include "ChaoticPrng.h"
#include "LogisticMap.h"
#include "TentMap.h"
#include "DoubleMap.h"
#include "SimpleMap.h"
#include "DoubleTent.h"
#include <iomanip>
#include <math.h>
#include <iostream>

using namespace std;

ChaoticPrng::ChaoticPrng() : log_map(0.7215, 3.99), lm_map_x(1000), lm_map_y(3001), tent_map(0.7215, 1.99), double_map(0.7215, 3.99), double_tent_map(0.78121223425, 1.99) {

}

uint8_t ChaoticPrng::genElemLm(){

    uint32_t x;
    uint32_t y;
    uint8_t elem = 0;
    for (int i = 0; i < 8; i ++){
        x = lm_map_x.nextElem();
        y = lm_map_y.nextElem();
        if (x > y){
            elem |= (1 << i);
        }else {
            elem &= ~(1 << i);
        }
    }
    return elem;

}

//generate via mantissa (last byte of the generated float number)
uint8_t ChaoticPrng::genElemLog(){
    float f = log_map.nextElem();
    memcpy(&bytes, &f, 4);
    return bytes[0];
}

uint8_t ChaoticPrng::genElemDouble(){
    double f = double_map.nextElem();
    memcpy(&bytes_double, &f, 8);
    return bytes_double[0];
}

uint8_t ChaoticPrng::genElemDoubleTent(){

    double f = double_tent_map.nextElem();


    memcpy(&bytes_double, &f, 8);
    uint8_t result = bytes_double[0];
    for (int i = 1; i < 5; i++){
        result ^= bytes_double[i];
    }
    return result;
}

//generate via mantissa (last byte of the generated float number)
uint8_t ChaoticPrng::genElemTent(){
    float f = tent_map.nextElem();
    memcpy(&bytes, &f, 4);

    uint8_t result = bytes[0];

    for (int i = 1; i < 4; i++){
        result ^= bytes[i];
    }
    return result;
}

uint8_t ChaoticPrng::normElem(float seqElem)
{
    int result = fabs( (( seqElem - x_min) / x_max * 255));
    return (uint8_t)result;
}

void ChaoticPrng::genElemLogNorm(int range){
    for (int i = 0; i < range; i++){
        chaoticSeq[i] = log_map.nextElem();
        if (chaoticSeq[i] > x_max)
        {
            x_max = chaoticSeq[i];
        }
        if (chaoticSeq[i] < x_min)
        {
            x_min = chaoticSeq[i];
        }
    };

    for (int i = 0; i < range; i++){
        chaoticIntegers[i] = normElem(chaoticSeq[i]);
    }
}

void ChaoticPrng::genElemTentNorm(int range){
    for (int i = 0; i < range; i++){
        chaoticSeq[i] = tent_map.nextElem();
        if (chaoticSeq[i] > x_max)
        {
            x_max = chaoticSeq[i];
        }
        if (chaoticSeq[i] < x_min)
        {
            x_min = chaoticSeq[i];
        }
    };

    for (int i = 0; i < range; i++){
        chaoticIntegers[i] = normElem(chaoticSeq[i]);
    }
}

