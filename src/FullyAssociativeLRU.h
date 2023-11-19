#pragma once
#include <stdlib.h>
#include <map>
#include <string>
#include <vector>
#include "CacheEntryStructs.h"

using namespace std;

class FullyAssociativeLRU
{
public:
    FullyAssociativeLRU();
    void processInstruction(unsigned long long addr);
    void LRUReplacement(unsigned int tag);
    vector<cacheEntry> cache;
    int cacheHits;
    int offsetBits;
    int indexBits;
    int totalCacheLines;
    unsigned long long currentTime;
};