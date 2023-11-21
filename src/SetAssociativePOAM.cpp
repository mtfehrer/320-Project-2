#include "SetAssociativePOAM.h"
#include <cmath>
#include <iostream>

using namespace std;

void SetAssociativePOAM::processInstructionPOAM(int ways, unsigned long long addr)
{
    currentTime++;

    int cacheLinesInEachWay = totalCacheLines / ways;
    int indexBits = log2(cacheLinesInEachWay);

    unsigned int index = (addr >> offsetBits) & (cacheLinesInEachWay - 1);
    unsigned int tag = addr >> (offsetBits + indexBits);

    pair<bool, int> val = searchForMatchPOAM(ways, index, tag, true);
    bool found = val.first;
    int LRUWayIndex = val.second;

    if (found == false)
    {
        replaceLRU(LRUWayIndex, ways, index, tag);

        // next line prefetching

        currentTime++;

        addr += (1 << offsetBits);

        index = (addr >> offsetBits) & (cacheLinesInEachWay - 1);
        tag = addr >> (offsetBits + indexBits);

        val = searchForMatchPOAM(ways, index, tag, false);
        found = val.first;
        LRUWayIndex = val.second;

        if (found == false)
        {
            replaceLRU(LRUWayIndex, ways, index, tag);
        }
    }
}

pair<bool, int> SetAssociativePOAM::searchForMatchPOAM(int ways, unsigned int cacheIndex, unsigned int tag, bool updateHits)
{
    pair<bool, int> res(false, -1);
    unsigned long long smallestTime = currentTime;
    for (int i = 0; i < ways; i++)
    {
        if (cacheMap[ways][i][cacheIndex].validBit == 1 && cacheMap[ways][i][cacheIndex].tag == tag)
        {
            if (updateHits)
            {
                cacheHits[ways]++;
            }
            res.first = true;
            cacheMap[ways][i][cacheIndex].lastUsedTime = currentTime;
            break;
        }
        if (cacheMap[ways][i][cacheIndex].lastUsedTime < smallestTime)
        {
            smallestTime = cacheMap[ways][i][cacheIndex].lastUsedTime;
            res.second = i;
        }
    }

    return res;
}