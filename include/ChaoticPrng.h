#include <stdint.h>
#include "LogisticMap.h"
#include "TentMap.h"
#include "SimpleMap.h"
#include "DoubleMap.h"
#include "DoubleTent.h"
#ifndef CHAOTICPRNG_H_INCLUDED
#define CHAOTICPRNG_H_INCLUDED

class ChaoticPrng
{
    double kk = 256;
    uint8_t bytes_double[8];
    uint8_t bytes[4];
    float chaoticSeq[100]; //array for keeping generated floats from chaotic seq.
    uint8_t chaoticIntegers[100];
    uint8_t normElem(float elem);
    LogisticMap log_map;

    SimpleMap lm_map_x;
    SimpleMap lm_map_y;
    TentMap tent_map;

    float x_min;
    float x_max;
public:
    ChaoticPrng();
    DoubleMap double_map;
    DoubleTent double_tent_map;
    uint8_t genElemTent();
    uint8_t genElemLog();
    uint8_t genElemLm();
    uint8_t genElemDouble();
    uint8_t genElemDoubleTent();
    void genElemLogNorm(int range);
    void genElemTentNorm(int range);
};

#endif
