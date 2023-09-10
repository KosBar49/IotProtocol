#include <stdint.h>
#ifndef LOCHAHASH_H_INCLUDED
#define LOCHAHASH_H_INCLUDED

class LochaHash
{
    int coeff1;
    int coeff2;
    float x1;
    float x2;
    float u;
    char data [64];
    int sTable1[96]; /* = {977, 149, 797, 991, 577, 137, 571, 37, 941, 167, 967, 353, 439, 887, 107, 23,
                             587, 557, 659, 479, 223, 41, 751, 757, 509, 127, 211, 491, 853, 613, 541, 449,
                             307, 251, 877, 599, 19, 199, 929, 683, 347, 419, 389, 487, 631, 569, 71, 563,
                             131, 823, 173, 317, 937, 277, 839, 59, 151, 431, 67, 379, 337, 293, 907, 227,
                             787, 997, 191, 79, 359, 11, 547, 769, 983, 727, 653, 641, 733, 809, 607, 673,
                             7, 401, 97, 719, 331, 109, 17, 827, 181, 89, 499, 709, 647, 5, 31, 409};*/

    int sTable2[67]; /*= {541, 821, 863, 97, 887, 433, 907, 797, 409, 293, 631, 521, 431, 853, 53, 809,
                             37, 211, 569, 67, 593, 587, 353, 911, 881, 701, 137, 823, 463, 691, 919, 937,
                             991, 577, 41, 547, 787, 727, 523, 233, 347, 331, 673, 43, 599, 223, 23, 967,
                             257, 839, 337, 29, 769, 3, 263, 709, 163, 983, 659, 83, 127, 877, 277, 367,
                             79, 509, 107}; */

public:
    void readSTable1();
    void readSTable2();
    void calcHash(uint8_t* hash_);
    void readWithPadding(uint8_t* data, uint8_t len);
    void calculatePrimesSTable1();
    void calculatePrimesSTable2();
    int checkIfPrime(int n);
    int checkSubblock(uint8_t subblock, int conversion);
    float genNextElem1();
    float genNextElem2();
    LochaHash(float u, float x1, int coeff_n1, float x2, int coeff_n2);

};

#endif // LOCHAHASH_H_INCLUDED
