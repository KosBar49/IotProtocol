#include <iostream>
#include <random>
#include <utility>
#include "ZKPDiscreteLog.h"
#ifndef ZKPDISCRETELOG_H_INCLUDED
#define ZKPDISCRETELOG_H_INCLUDED


class ZKPDiscreteLog {
private:
    int modulo;
    int gen;
    int secret;
    std::random_device rd;
    std::mt19937 genRandom;

    int randomInt(int min, int max) {
        std::uniform_int_distribution<> distrib(min, max);
        return distrib(genRandom);
    }

    int modPow(int base, int exp, int mod) const {
        int result = 1;
        base = base % mod;
        while (exp > 0) {
            if (exp % 2 == 1)
                result = (result * base) % mod;
            exp = exp >> 1;
            base = (base * base) % mod;
        }
        return result;
    }

public:
    ZKPDiscreteLog(int modulo, int gen, int secret)
        : modulo(modulo), gen(gen), secret(secret), genRandom(rd()) {}

    std::pair<int, int> commitment() {
        int r = randomInt(0, modulo - 1);
        int commitment = modPow(gen, r, modulo);
        return {r, commitment};
    }

    int challenge() {
        return randomInt(1, modulo - 1);
    }

    int response(int challenge, int r) {
        return (secret * challenge + r) % (modulo - 1);
    }

    bool verify(int commitment, int challenge, int response, int y) {
        return modPow(gen, response, modulo) == (modPow(y, challenge, modulo) * commitment) % modulo;
    }

    int getY() const {
        return modPow(gen, secret, modulo);
    }
};


#endif // ZKPDISCRETELOG_H_INCLUDED
