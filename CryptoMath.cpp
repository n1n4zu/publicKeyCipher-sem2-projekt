#include "CryptoMath.h"
#include <stdexcept>

int CryptoMath::gcd(int a, int b) {
    while (a != 0) {
        int temp = a;
        a = b % a;
        b = temp;
    }
    return b;
}

long long CryptoMath::findModInverse(long long a, long long m) {
    if (gcd(a, m) != 1) {
        throw invalid_argument("a and m must be coprime.");
    }

    long long u1 = 1, u2 = 0, u3 = a;
    long long v1 = 0, v2 = 1, v3 = m;

    while (v3 != 0) {
        long long q = u3 / v3;
        long long t1 = u1 - q * v1;
        long long t2 = u2 - q * v2;
        long long t3 = u3 - q * v3;
        u1 = v1;
        u2 = v2;
        u3 = v3;
        v1 = t1;
        v2 = t2;
        v3 = t3;
    }

    return u1 % m;
}
