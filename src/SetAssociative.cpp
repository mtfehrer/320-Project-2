#include "SetAssociative.h"
#include <cmath>
#include <iostream>

using namespace std;

SetAssociative::SetAssociative()
{
    offsetBits = 5;
    currentTime = 0;
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
    currentTime++;

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
            found = true;
            break;
        }
    }

    if (found == false)
    {
        // find lru element
        int LRUWayIndex = -1;
        unsigned long long smallestTime = currentTime;
        for (int i = 0; i < ways; i++)
        {
            if (cacheMap[ways][i][index].lastUsedTime < smallestTime)
            {
                smallestTime = cacheMap[ways][i][index].lastUsedTime;
                LRUWayIndex = i;
            }
        }

        // replace lru element
        cacheMap[ways][LRUWayIndex][index].tag = tag;
        cacheMap[ways][LRUWayIndex][index].validBit = 1;
        cacheMap[ways][LRUWayIndex][index].lastUsedTime = currentTime;
    }
}
