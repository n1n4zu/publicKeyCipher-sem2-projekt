#ifndef PUBLICKEYCIPHER_H
#define PUBLICKEYCIPHER_H

#include <vector>
#include <utility> // dla std::pair

using namespace std;

class PublicKeyCipher {
public:
    static vector<long long> encryptMessage(const vector<char>& message, const pair<long long, long long>& key, int blockSize);
    static vector<char> decryptMessage(const vector<long long>& encryptedBlocks, int messageLength, const pair<long long, long long>& key, int blockSize);

private:
    static long long powMod(long long base, long long exp, long long mod);
};

#endif //PUBLICKEYCIPHER_H