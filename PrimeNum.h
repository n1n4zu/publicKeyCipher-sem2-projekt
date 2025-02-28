#ifndef PRIMENUM_H
#define PRIMENUM_H

#include <cmath>
#include <random>

using namespace std;

class PrimeNum {
public:
    static bool isPrimeTrialDiv(int num);
    static long long generateLargePrime(int keySize);
};

#endif //PRIMENUM_H
