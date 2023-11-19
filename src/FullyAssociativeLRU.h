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
    bool searchForMatch(unsigned int tag);
    int findLRU();
    void replaceLRU(unsigned int cacheIndex, unsigned int tag);
    vector<cacheEntryLRU> cache;
    int cacheHits;
    int offsetBits;
    int indexBits;
    int totalCacheLines;
    unsigned long long currentTime;
};