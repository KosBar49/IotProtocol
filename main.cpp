#include <iostream>
#include <math.h>
#include "ChaoticCipher.h"
#include "SlimChaotic.h"
#include "LochaHash.h"

using namespace std;

int main()
{
    uint8_t data[] = "Hello world! Hello world!";
    uint8_t data_slim[] = "Hello world! Hello world!";
    uint8_t hash_[24];

    ChaoticCipher cipher(3.9, 0.7521);
    SlimChaotic slim(3.9, 0.7521);

    LochaHash locha(1.5437, -0.325, 8, -0.333, 7);

    //encrypt data
    cipher.cipherDataMantissa(data, sizeof(data));
    slim.cipherDataComplex(data_slim, sizeof(data));

    //show encrypted
    cout << "---NN model---" << endl;
    cipher.showData(data, sizeof(data));
    cout << "---Slim model---" << endl;
    slim.showData(data_slim, sizeof(data_slim));

    //decrypt data
    cipher.setX(0.7521);
    slim.setX(0.7521);
    cipher.cipherDataMantissa(data, sizeof(data));
    slim.cipherDataComplexDecrypt(data_slim, sizeof(data_slim));

    //show decrypted
    cout << "---NN model---" << endl;
    cipher.showData(data, sizeof(data));
    cout << "---Slim model---" << endl;
    slim.showData(data_slim, sizeof(data_slim));


    locha.calculatePrimesSTable1();
    locha.calculatePrimesSTable2();
    locha.readSTable1();
    locha.readSTable2();

    //cipher.cipherDataNorm(data, sizeof(data));

    locha.readWithPadding(data, sizeof(data));
    locha.calcHash(hash_);
    for (int i=0; i < 24; i++){
        cout << hash_[i];
        cout << "";
    }
    //cout << endl;
    //cout << locha.checkIfPrime(7) << endl;

    return 0;


}
