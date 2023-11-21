#pragma once
#include <stdlib.h>
#include <map>
#include <string>
#include <vector>
#include "CacheEntryStructs.h"

using namespace std;

struct node
{
    int val;
    int index;
    node(int v, int i) : val(v), index(i){};
};

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
    vector<node> tree;
    int cacheHits;
    int offsetBits;
    int totalCacheLines;
};