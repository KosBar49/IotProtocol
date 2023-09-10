#include "LochaHash.h"
#include <iostream>
#include <cctype>
#include <math.h>


using namespace std;

LochaHash::LochaHash(float u_, float x_1, int coeff_n_1, float x_2, int coeff_n_2)
{
    u = u_;
    x1 = x_1;
    coeff1 = (int)pow(10, coeff_n_1);
    x2 - x_2;
    coeff2 = (int)pow(10, coeff_n_2);
}

//generating Stables by pseudo-random primes
void LochaHash::readSTable1(){

    for ( int i =0; i < 96; i++){
        cout << sTable1[i] << endl;
    }

}

void LochaHash::readSTable2(){

    for ( int i =0; i < 63; i++){
        cout << sTable2[i] << endl;
    }

}

float LochaHash::genNextElem1()
{
    x1 = u*x1*(1 - x1);// - x1*x1*u;
}

float LochaHash::genNextElem2()
{
    x2 = u*x2*(1 - x2);// - x2*x2*u;
}

int LochaHash::checkIfPrime(int n){
    int sqrt_n = (int)sqrt(n) + 1;
    int primeno = 0;
    int p = 0;
    if ( n > 1){
        for (int i = 2; i < sqrt_n; i++){
            if ( n % i  == 0){
                primeno = 1;
                break;
            }
        }
        if (primeno == 0){
            p = n;
        }
    }
    return p;
}

void LochaHash::calculatePrimesSTable1(){
    int c = 0;
    int prime;
    while (c < 96){

        prime = (int)(x1 * coeff1);
        prime = ( 1024  + (prime % 1024) ) % 1024;
        prime = checkIfPrime(prime);
        if (prime != 0 & prime < 1000){
            sTable1[c] = prime;
            c += 1;
        }
        genNextElem1();
    }
}

void LochaHash::calculatePrimesSTable2(){
    int c = 0;
    int prime;
    while (c < 63){

        prime = (int)(x2 * coeff2);
        prime = ( 1024  + (prime % 1024) ) % 1024;
        prime = checkIfPrime(prime);
        if (prime != 0 & prime < 1000){
            sTable2[c] = prime;
            c += 1;
        }
        genNextElem2();
    }
}

void LochaHash::readWithPadding(uint8_t* dataToHash, uint8_t len){

    for (int i = 0; i < len; i++){
        data[i] = dataToHash[i];
    }
    for (int i = len; i < 64; i++){
        data[i] = 0;
    }
}

int LochaHash::checkSubblock(uint8_t subblock, int conversion){
    int pk;
    int convCoeff = pow(2.0,16.0) - 1;
    if( subblock != 0 ){
        pk =  int(subblock) - 31;
    }else{
        pk = 1;
    }
    conversion = sTable1[pk] * conversion;

    if (conversion > convCoeff){
        conversion = conversion % (int)pow(2.0, 16.0);
    }
    return conversion;
}

void intToHex(int n, uint8_t* subHex){
    uint8_t c;
    int i = 2;
    while (n != 0) {
        int temp = 0;
        temp = n % 16;
        if (temp < 10) {
            c = (char)(temp + 48);
            if (isalpha(c)){
                c = c + 32;
            }
            subHex[i] = c;
        }
        else {
            c = (char)(temp + 55 );
            if (isalpha(c)){
                c = c + 32;
            }
            subHex[i] = c;
        }
        i = i - 1;
        n = n / 16;
    }
}

int hexToDec(uint8_t* hex)
{
    int result = 0;
    for (int i=0; i<3; i++) {
        if (hex[i]>=48 && hex[i]<=57)
        {
            result += (hex[i]-48)*pow(16,3-i-1);
        } else if (hex[i]>=65 && hex[i]<=70) {
            result += (hex[i]-55)*pow(16,3-i-1);
        } else if (hex[i]>=97 && hex[i]<=102) {
            result += (hex[i]-87)*pow(16,3-i-1);
        }
    }
    return result;
}

void LochaHash::calcHash(uint8_t* hash_){
    int conversion1 = 1;
    int conversion2Part1 = 0;
    int conversion2Part2 = 0;
    int conversion2Part3 = 7;
    int afterConversion = 0;
    uint8_t subHex[] = "000";
    char temp;
    int hexDecimal;
    for (int j=0; j < 8; j++){
        for (int k = 0; k < 8; k ++ ){
            conversion1 = checkSubblock(data[8*j+k], conversion1);
        }
        conversion2Part1 = conversion1 % 67;
        if ( ( (data[1] >> 7) & 0X01) == 0 ){
           conversion2Part2 =  conversion2Part1;
        }
        else{
            conversion2Part2 = 67 - conversion2Part1;
        }
        conversion2Part3 = ( conversion2Part3 + ( conversion2Part1 + conversion1 ) % 256 );
        afterConversion = ( conversion1 % conversion2Part3) + conversion1 + sTable2[conversion2Part2-1];
        hexDecimal = hexToDec(subHex);
        afterConversion = ( afterConversion % 255 ) + ((int)data[j*8] % 127) + (int)data[j*8+2] + hexDecimal;
        intToHex(afterConversion, subHex);
        hash_[j*3] = subHex[0];
        hash_[j*3+1] = subHex[1];
        hash_[j*3+2] = subHex[2];
        temp = subHex[1];
        subHex[0] = '0';
        subHex[1] = subHex[2];
        subHex[2] = temp;
    }
}
