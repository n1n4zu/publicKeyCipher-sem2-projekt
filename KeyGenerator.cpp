#include "KeyGenerator.h"
#include "CryptoMath.h"
#include "PrimeNum.h"
#include <algorithm>
#include <fstream>
#include <string>

pair<pair<long long, long long>, pair<long long, long long>> KeyGenerator::generateKey(int keySize) {
    long long p, q, n, phi, e = 65537, d;

    do {
        p = PrimeNum::generateLargePrime(keySize / 2);
        q = PrimeNum::generateLargePrime(keySize / 2);
        n = p * q;
        phi = (p - 1) * (q - 1);
        d = CryptoMath::findModInverse(e, phi);
    } while (d == -1);

    return {{n, e}, {n, d}};
}

void KeyGenerator::makeKeyFiles(const string &name, int keySize) {
    if (name.empty()) {
        throw runtime_error("Key name cannot be empty.");
    }

    if (ifstream(name + ".pub") || ifstream(name)) {
        throw runtime_error("File already exists.");
    }

    auto keys = generateKey(keySize);
    auto publicKey = keys.first;
    auto privateKey = keys.second;

    ofstream pubFile(name + ".pub");
    if (!pubFile) {
        throw runtime_error("Could not open public key file.");
    }
    pubFile << keySize << "," << publicKey.first << "," << publicKey.second;
    pubFile.close();

    ofstream privFile(name);
    if (!privFile) {
        throw runtime_error("Could not open private key file.");
    }
    privFile << keySize << "," << privateKey.first << "," << privateKey.second;
    privFile.close();
}