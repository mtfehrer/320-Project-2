#include "SetAssociative.h"
#include <cmath>
#include <iostream>

using namespace std;

SetAssociative::SetAssociative()
{
    offsetBits = 5;
    totalCacheLines = (16 * 1024) / 32;
    associativitySizes = {2, 4, 8, 16};

    for (int i = 0; i < (int)associativitySizes.size(); i++)
    {
        int entriesInEachWay = totalCacheLines / associativitySizes[i];

        vector<cacheEntry> v;
        for (int j = 0; j < entriesInEachWay; j++)
        {
            v.push_back(cacheEntry(0, 0));
        }
        cacheMap[associativitySizes[i]].push_back(v);

        cacheHits[associativitySizes[i]] = 0;
    }
}

void SetAssociative::processInstruction(int ways, unsigned long long addr)
{
    int cacheLinesInEachWay = totalCacheLines / ways;
    int indexBits = log2(cacheLinesInEachWay);

    unsigned int index = (addr >> offsetBits) & (cacheLinesInEachWay - 1);
    unsigned int tag = addr >> (offsetBits + indexBits);

    vector<int> validBits;
    vector<unsigned int> tagsInCache;

    // search for validBits and tags in cache
    bool found = false;
    for (int i = 0; i < ways; i++)
    {
        if (cacheMap[ways][i][index].validBit == 1 && cacheMap[ways][i][index].tag == tag)
        {
            cacheHits[ways]++;
        }
    }

    unsigned int validBit = cacheMap[ways][index].validBit;
    unsigned int tagInCache = cacheEntries[sizeInKB][index].tag;

    if (validBit == 1 && tagInCache == tag)
    {
        cacheHits[sizeInKB]++;
    }
    else
    {
        cacheEntries[sizeInKB][index].tag = tag;
        cacheEntries[sizeInKB][index].validBit = 1;
    }
}
