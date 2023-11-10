#pragma once
#include <stdlib.h>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct cacheEntry
{
    unsigned int validBit;
    unsigned int tag;
    unsigned long long lastUsedTime;
    cacheEntry(unsigned int v, unsigned int t) : validBit(v), tag(t), lastUsedTime(0){};
};

class SetAssociative
{
public:
    SetAssociative();
    void processInstruction(int sizeInKB, unsigned long long addr);
    vector<int> associativitySizes;
    // {2: [[e1, e2, e3], [e1, e2, e3]], 4: [[e1, e2, e3], [e1], [e1, e2], [e1, e2, e3]]}
    map<int, vector<vector<cacheEntry>>> cacheMap;
    map<int, int> cacheHits;
    int offsetBits;
    int totalCacheLines;
    unsigned long long currentTime;
};