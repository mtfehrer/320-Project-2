#include <queue>
#include <cmath>
#include "FullyAssociativePLRU.h"
#include "CacheEntryStructs.h"

using namespace std;

FullyAssociativePLRU::FullyAssociativePLRU()
{
    offsetBits = log2(32);
    totalCacheLines = (16 * 1024) / 32;
    indexBits = log2(totalCacheLines);
    cacheHits = 0;

    for (int i = 0; i < 511; i++)
    {
        tree[i] = 1;
    }

    for (int i = 0; i < totalCacheLines; i++)
    {
        cache.push_back(cacheEntry(0, 0));
    }
}

void FullyAssociativePLRU::processInstruction(unsigned long long addr)
{
    unsigned int index = (addr >> offsetBits) & (totalCacheLines - 1);
    unsigned int tag = addr >> (offsetBits + indexBits);

    unsigned int validBitInCache = cache[index].validBit;
    unsigned int tagInCache = cache[index].tag;

    if (validBitInCache == 1 && tagInCache == tag)
    {
        cacheHits++;
    }
    else
    {
        LRUReplacement(tag);
    }

    updateTreePath();
}

void FullyAssociativePLRU::LRUReplacement(unsigned int tag)
{
    int currentIndex = 0;
    int indexToReplace = 0;
    int height = log2(512);
    int currentDepth = 1;

    while (currentDepth < height)
    {
        if (tree[currentIndex] == 0)
        {
            currentIndex = getRightIndex(currentIndex);
            indexToReplace += (1 << (height - currentDepth - 1));
        }
        else
        {
            currentIndex = getLeftIndex(currentIndex);
        }

        currentDepth++;
    }

    cache[indexToReplace + tree[currentIndex]].tag = tag;
    cache[indexToReplace + tree[currentIndex]].validBit = 1;
}

void FullyAssociativePLRU::updateTreePath()
{
    int currentIndex = 0;
    int next;

    while (currentIndex != -1)
    {
        next = (tree[currentIndex] == 0) ? getLeftIndex(currentIndex) : getRightIndex(currentIndex);

        tree[currentIndex] = (tree[currentIndex] == 0) ? 1 : 0;

        currentIndex = next;
    }
}

int FullyAssociativePLRU::getLeftIndex(int curIndex)
{
    int index = (curIndex * 2) + 1;
    return (index < 512) ? index : -1;
}

int FullyAssociativePLRU::getRightIndex(int curIndex)
{
    int index = (curIndex * 2) + 2;
    return (index < 512) ? index : -1;
}