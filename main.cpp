#include <iostream>
#include <math.h>
#include <chrono>
#include "ChaoticCipher.h"
#include "SlimChaotic.h"
#include "LochaHash.h"
#include "ChaoticPrng.h"
#include "DoubleMap.h"
#include <fstream>
#include <bitset>

using namespace std;

void writeUint8ToBinaryFileCustom(const string& filename){
    ChaoticPrng prng;
    char newline = '\n';
    // Open the file in binary mode
    ifstream file(filename);
    if (file.good()){
        file.close();
        remove(filename.c_str());
    }
    ofstream outFile(filename, ios::binary | ios::app);
    uint8_t val[8];
    string binaryString;

    for (int j = 0; j <= 1000; j++) {
        cout << j << endl;
        for(int i = 0; i < 25000; i++ ){
            double f = prng.double_map.nextElem();
            memcpy(&val, &f, 8);
            for(int u = 0; u < 5; u++){
                bitset<8> binary(val[u]);
                binaryString = binary.to_string();
                outFile.write(binaryString.c_str(), binaryString.size());
            }
        }
        outFile.write(&newline, sizeof(newline) );
    }

    if (outFile.good()) {
        std::cout << "Binary data written to file successfully." << std::endl;
    } else {
        std::cerr << "Error: Failed to write data to the file." << std::endl;
    }

    // Close the file
    outFile.close();

}

void writeUint8ToBinaryFile(const string& filename){
    ChaoticPrng prng;
    char newline = '\n';
    // Open the file in binary mode
    ifstream file(filename);
    if (file.good()){
        file.close();
        remove(filename.c_str());
    }
    ofstream outFile(filename, ios::binary | ios::app);
    uint8_t value;
    string binaryString;
    for (int j = 0; j <= 1000; j++) {
        cout << j << endl;
        for(int i = 0; i < 125000; i++ ){
            value = prng.genElemDoubleTent();
            bitset<8> binary(value);
            binaryString = binary.to_string();
            outFile.write(binaryString.c_str(), binaryString.size());
        }
        outFile.write(&newline, sizeof(newline) );
    }

    if (outFile.good()) {
        std::cout << "Binary data written to file successfully." << std::endl;
    } else {
        std::cerr << "Error: Failed to write data to the file." << std::endl;
    }

    // Close the file
    outFile.close();

}

void writeMapResultTofile(int map_type, const string &filename){
    ifstream file(filename);
    if (file.good()){
        file.close();
        remove(filename.c_str());
    }
    ofstream outFile(filename, ios::binary | ios::app);
    string result;
    int result_int;
    ChaoticPrng prng;

    for (int i= 0; i < 100000; i ++ ){

        if (map_type == 0){
            result_int = (int)prng.genElemDouble();
        }
        else if (map_type == 1) {
            result_int = (int)prng.genElemLog();
        }
        else if (map_type == 2) {
            result_int = (int)prng.genElemDoubleTent();
        }
        else{
            result_int = (int)prng.genElemLm();
        }
        result = to_string(result_int);
        outFile.write(result.c_str(), result.size());
        outFile.write("\n", 1);
    }
    outFile.close();

}

void writeMapResultToFileTry(const string &filename){

    ifstream file(filename);
    if (file.good()){
        file.close();
        remove(filename.c_str());
    }
    ofstream outFile(filename, ios::binary | ios::app);
    string result;
    int result_int;
    uint8_t val[8];
    ChaoticPrng prng;

    for (int i= 0; i < 20000; i ++ ){
        double f = prng.double_tent_map.nextElem();
        memcpy(&val, &f, 8);
        for (int j= 0; j < 5; j++){
            result_int = (int)val[j];
            result = to_string(result_int);
            outFile.write(result.c_str(), result.size());
            outFile.write("\n", 1);
        }

    }
    outFile.close();
}

int main()
{
    uint8_t data[] = "Hello world! Hello world!";
    uint8_t data_slim[] = "Hello world! Hello world!";
    uint8_t hash_[24];

    ChaoticCipher cipher(3.9, 0.7521);
    SlimChaotic slim(3.9, 0.7521);
    ChaoticPrng prng;
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
    cout << endl;
    cout << locha.checkIfPrime(7) << endl;

    uint8_t elem;

    // section with generation the random integer numbers
    auto start = std::chrono::high_resolution_clock::now();
    cout << "Tent generation" << endl;
    for (int i = 0; i < 24; i++ ){

        cout << (int)prng.genElemTent() << endl;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Time taken by genElemTent: " << duration << " microseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    cout << "Log generation" << endl;
    for (int i = 0; i < 24; i++ ){

        cout << (int)prng.genElemLog() << endl;
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Time taken by genElemLog: " << duration << " microseconds" << std::endl;

    cout << "Double generation" << endl;

    start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 24; i++ ){

        cout << (int)prng.genElemDouble() << endl;
    }


    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Time taken by genElemLm: " << duration << " microseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    prng.genElemLogNorm(100);
    end = std::chrono::high_resolution_clock::now();

    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Time taken by genElemLogNorm: " << duration << " microseconds" << std::endl;

    writeUint8ToBinaryFileCustom("tent_seq");

    //writeMapResultTofile(2, "tent_5_chart");
    //writeMapResultTofile(1, "log_map");
    writeMapResultToFileTry("tent_seq_map");
    return 0;
}
