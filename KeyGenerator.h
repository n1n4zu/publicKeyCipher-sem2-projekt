#ifndef KEYGENERATOR_H
#define KEYGENERATOR_H

#include <algorithm>
#include <vector>
#include <string>

using namespace std;

class KeyGenerator {
public:
    static pair<pair<long long, long long>, pair<long long, long long> > generateKey(int keySize);
    static void makeKeyFiles(const string &name, int keySize = 4096);
};

#endif //KEYGENERATOR_H
