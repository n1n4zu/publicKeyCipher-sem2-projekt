#ifndef PUBLICKEYCIPHER_H
#define PUBLICKEYCIPHER_H

#include <vector>
#include <algorithm>

using namespace std;

class PublicKeyCipher {
public:
    static vector<int> encryptMessage(const vector<char>& message, const pair<int, int>& key, int blockSize);
    static vector<char> decryptMessage(const vector<int>& encryptedBlocks, int messageLength, const pair<int, int>& key, int blockSize);
private:
    static int powMod(int base, int exp, int mod);
};

#endif //PUBLICKEYCIPHER_H
