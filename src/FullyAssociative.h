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
    cacheEntryFA(unsigned int v, unsigned int t) : validBit(v), tag(t){};
};

class FullyAssociative
{
public:
    FullyAssociative();
    void processInstruction(unsigned long long addr);
    void LRUReplacement(unsigned int tag);
    void updateTreePath();
    int getLeftIndex(int curIndex);
    int getRightIndex(int curIndex);
    vector<cacheEntryFA> cache;
    int tree[511];
    int cacheHits;
    int offsetBits;
    int indexBits;
    int totalCacheLines;
};