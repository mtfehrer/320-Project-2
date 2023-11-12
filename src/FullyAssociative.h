#pragma once
#include <stdlib.h>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct cacheEntryFA
{
    unsigned int validBit;
    unsigned int tag;
    unsigned long long lastUsedTime;
    cacheEntryFA(unsigned int v, unsigned int t) : validBit(v), tag(t), lastUsedTime(0){};
};

class FullyAssociative
{
public:
    FullyAssociative();
    void processInstruction(int sizeInKB, unsigned long long addr);
    void replaceLRU(int LRUWayIndex, int ways, unsigned int cacheIndex, unsigned int tag);
    pair<bool, int> searchForMatch(int ways, unsigned int cacheIndex, unsigned int tag);
    vector<int> associativitySizes;
    map<int, vector<vector<cacheEntryFA>>> cacheMap;
    map<int, int> cacheHits;
    int offsetBits;
    int totalCacheLines;
    unsigned long long currentTime;
};