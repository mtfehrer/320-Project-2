#pragma once
#include <stdlib.h>
#include <map>
#include <string>
#include <vector>
#include "CacheEntryStructs.h"

using namespace std;

class FullyAssociative
{
public:
    FullyAssociative();
    void processInstruction(unsigned long long addr);
    void LRUReplacement(unsigned int tag);
    void updateTreePath();
    int getLeftIndex(int curIndex);
    int getRightIndex(int curIndex);
    vector<cacheEntry> cache;
    int tree[511];
    int cacheHits;
    int offsetBits;
    int indexBits;
    int totalCacheLines;
};