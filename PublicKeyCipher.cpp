#include "PublicKeyCipher.h"

int PublicKeyCipher::powMod(int base, int exp, int mod) {
    int result = 1;
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

vector<int> PublicKeyCipher::encryptMessage(const vector<char>& message, const pair<int, int>& key, int blockSize) {
    int n = key.first;
    int e = key.second;
    vector<int> encryptedBlocks;

    for (size_t i = 0; i < message.size(); i += blockSize) {
        int block = 0;
        for (size_t j = 0; j < blockSize && i + j < message.size(); ++j) {
            block += static_cast<unsigned char>(message[i + j]) * (1 << (8 * j));
        }
        encryptedBlocks.push_back(powMod(block, e, n));
    }

    return encryptedBlocks;
}

vector<char> PublicKeyCipher::decryptMessage(const vector<int>& encryptedBlocks, int messageLength, const pair<int, int>& key, int blockSize) {
    int n = key.first;
    int d = key.second;
    vector<char> decryptedMessage;

    for (int block : encryptedBlocks) {
        int decryptedBlock = powMod(block, d, n);
        for (int i = 0; i < blockSize; ++i) {
            if (decryptedMessage.size() < messageLength) {
                decryptedMessage.push_back(static_cast<char>(decryptedBlock % 256));
                decryptedBlock /= 256;
            }
        }
    }

    return decryptedMessage;
}