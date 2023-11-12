#include "FullyAssociative.h"

using namespace std;

FullyAssociative::FullyAssociative()
{
    offsetBits = 5;
    // set add nodes in binary tree

    for (int i = 0; i < (int)cacheSizes.size(); i++)
    {
        cacheHits[cacheSizes[i]] = 0;

        int entries = (cacheSizes[i] * 1024) / 32;
        for (int j = 0; j < entries; j++)
        {
            cacheEntries[cacheSizes[i]].push_back(cacheEntry(0, 0));
        }
    }
}

void FullyAssociative::processInstruction(int sizeInKB, unsigned long long addr)
{
    int entries = (sizeInKB * 1024) / 32;
    int indexBits = log2(entries);

    unsigned int index = (addr >> offsetBits) & (entries - 1);
    unsigned int tag = addr >> (offsetBits + indexBits);

    unsigned int validBit = cacheEntries[sizeInKB][index].validBit;
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