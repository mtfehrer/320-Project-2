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

        for (int j = 0; j < associativitySizes[i]; j++)
        {
            vector<cacheEntrySA> v;
            for (int k = 0; k < entriesInEachWay; k++)
            {
                v.push_back(cacheEntrySA(0, 0));
            }
            cacheMap[associativitySizes[i]].push_back(v);
        }

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

    pair<bool, int> val = searchForMatch(ways, index, tag);
    bool found = val.first;
    int LRUWayIndex = val.second;

    if (found == false)
    {
        replaceLRU(LRUWayIndex, ways, index, tag);
    }
}

pair<bool, int> SetAssociative::searchForMatch(int ways, unsigned int cacheIndex, unsigned int tag)
{
    pair<bool, int> res(false, -1);
    unsigned long long smallestTime = currentTime;
    for (int i = 0; i < ways; i++)
    {
        if (cacheMap[ways][i][cacheIndex].validBit == 1 && cacheMap[ways][i][cacheIndex].tag == tag)
        {
            cacheHits[ways]++;
            res.first = true;
        }
        if (cacheMap[ways][i][cacheIndex].lastUsedTime < smallestTime)
        {
            smallestTime = cacheMap[ways][i][cacheIndex].lastUsedTime;
            res.second = i;
        }
    }

    return res;
}

void SetAssociative::replaceLRU(int LRUWayIndex, int ways, unsigned int cacheIndex, unsigned int tag)
{
    cacheMap[ways][LRUWayIndex][cacheIndex].tag = tag;
    cacheMap[ways][LRUWayIndex][cacheIndex].validBit = 1;
    cacheMap[ways][LRUWayIndex][cacheIndex].lastUsedTime = currentTime;
}