#include <utility>
#include <random>
#ifndef ZKPDISCRETELOG_H_INCLUDED
#define ZKPDISCRETELOG_H_INCLUDED

class ZKPDiscreteLog {
private:
    int modulo;
    int gen;
    int secret;
    std::random_device rd;
    std::mt19937 genRandom;

    int randomInt(int min, int max);
    int modPow(int base, int exp, int mod) const;

public:
    ZKPDiscreteLog(int modulo, int gen, int secret);
    std::pair<int, int> commitment();
    int challenge();
    int response(int challenge, int r);
    bool verify(int commitment, int challenge, int response, int y);
    int getY() const;
};


#endif // ZKPDISCRETELOG_H_INCLUDED
