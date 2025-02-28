#include "PrimeNum.h"

bool PrimeNum::isPrimeTrialDiv(int num) {
    if (num < 2) return false;
    for (int i = 2; i <= sqrt(num); ++i) {
        if (num % i == 0) return false;
    }
    return true;
}

long long PrimeNum::generateLargePrime(int keySize) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<long long> dis(0, 1LL << (keySize - 1));

    long long num;
    do {
        num = dis(gen);
    } while (!isPrimeTrialDiv(num));

    return num;
}