#ifndef CRYPTOMATH_H
#define CRYPTOMATH_H

using namespace std;

class CryptoMath {
public:
    static int gcd(int a, int b);
    static long long findModInverse(long long a, long long m);
};

#endif //CRYPTOMATH_H
