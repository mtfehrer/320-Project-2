#pragma once
#include <stdlib.h>
#include <map>
#include <string>
#include <vector>
#include "CacheEntryStructs.h"

using namespace std;

class SetAssociative
{
public:
    SetAssociative();
    void processInstruction(int sizeInKB, unsigned long long addr);
    void replaceLRU(int LRUWayIndex, int ways, unsigned int cacheIndex, unsigned int tag);
    pair<bool, int> searchForMatch(int ways, unsigned int cacheIndex, unsigned int tag);
    vector<int> associativitySizes;
    // {2: [[e1, e2, e3], [e1, e2, e3]], 4: [[e1, e2, e3], [e1], [e1, e2], [e1, e2, e3]]}
    map<int, vector<vector<cacheEntryLRU>>> cacheMap;
    map<int, int> cacheHits;
    int offsetBits;
    int totalCacheLines;
    unsigned long long currentTime;
};