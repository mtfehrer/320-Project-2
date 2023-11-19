#pragma once
#include <stdlib.h>
#include <map>
#include <string>
#include <vector>
#include "CacheEntryStructs.h"

using namespace std;

class FullyAssociativePLRU
{
public:
    FullyAssociativePLRU();
    void processInstruction(unsigned long long addr);
    bool searchForMatch(unsigned int tag);
    void LRUReplacement(unsigned int tag);
    void updateTreePath();
    int getLeftIndex(int curIndex);
    int getRightIndex(int curIndex);
    vector<cacheEntry> cache;
    int tree[511];
    int cacheHits;
    int offsetBits;
    int totalCacheLines;
};