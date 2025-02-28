#include "PublicKeyCipher.h"
#include <stdexcept>
#include <iostream>

long long PublicKeyCipher::powMod(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp = exp >> 1;
    }
    return result;
}

vector<long long> PublicKeyCipher::encryptMessage(const vector<char>& message, const pair<long long, long long>& key, int blockSize) {
    long long n = key.first;
    long long e = key.second;
    vector<long long> encryptedBlocks;

    for (size_t i = 0; i < message.size(); i += blockSize) {
        long long block = 0;
        for (size_t j = 0; j < blockSize && i + j < message.size(); ++j) {
            block += static_cast<unsigned char>(message[i + j]) * (1LL << (8 * j));
        }
        encryptedBlocks.push_back(powMod(block, e, n));
    }

    return encryptedBlocks;
}

vector<char> PublicKeyCipher::decryptMessage(const vector<long long>& encryptedBlocks, int messageLength, const pair<long long, long long>& key, int blockSize) {
    long long n = key.first;
    long long d = key.second;
    vector<char> decryptedMessage;

    for (long long block : encryptedBlocks) {
        long long decryptedBlock = powMod(block, d, n);
        for (int i = 0; i < blockSize; ++i) {
            if (decryptedMessage.size() < messageLength) {
                decryptedMessage.push_back(static_cast<char>(decryptedBlock % 256));
                decryptedBlock /= 256;
            }
        }
    }

    return decryptedMessage;
}