#include <queue>
#include <cmath>
#include "FullyAssociativeLRU.h"
#include "CacheEntryStructs.h"

using namespace std;

FullyAssociativeLRU::FullyAssociativeLRU()
{
    offsetBits = log2(32);
    totalCacheLines = (16 * 1024) / 32;
    indexBits = log2(totalCacheLines);
    cacheHits = 0;

    for (int i = 0; i < totalCacheLines; i++)
    {
        cache.push_back(cacheEntryLRU(0, 0));
    }
}

void FullyAssociativeLRU::processInstruction(unsigned long long addr)
{
    unsigned int tag = addr >> (offsetBits + indexBits);

    if (searchForMatch(tag) == false)
    {
        replaceLRU(findLRU(), tag);
    }
}

bool FullyAssociativeLRU::searchForMatch(unsigned int tag)
{
    for (int i = 0; i < totalCacheLines; i++)
    {
        if (cache[i].validBit == 1 && cache[i].tag == tag)
        {
            cacheHits++;
            cache[i].lastUsedTime = currentTime;
            return true;
        }
    }

    return false;
}

int FullyAssociativeLRU::findLRU()
{
    int res = 0;
    unsigned long long smallestTime = currentTime;

    for (int i = 0; i < totalCacheLines; i++)
    {
        if (cache[i].lastUsedTime < smallestTime)
        {
            smallestTime = cache[i].lastUsedTime;
            res = i;
        }
    }

    return res;
}

void FullyAssociativeLRU::replaceLRU(unsigned int cacheIndex, unsigned int tag)
{
    cache[cacheIndex].tag = tag;
    cache[cacheIndex].validBit = 1;
    cache[cacheIndex].lastUsedTime = currentTime;
}