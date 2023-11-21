#include <cmath>
#include <iostream>
#include "FullyAssociativePLRU.h"
#include "CacheEntryStructs.h"

using namespace std;

FullyAssociativePLRU::FullyAssociativePLRU()
{
    offsetBits = log2(32);
    totalCacheLines = (16 * 1024) / 32;
    cacheHits = 0;

    int currentIndex = 0;
    for (int i = 0; i < 511; i++)
    {
        if (i < 255)
        {
            tree.push_back(node(0, 0));
        }
        else
        {
            tree.push_back(node(0, currentIndex));
            currentIndex += 2;
        }
    }

    for (int i = 0; i < totalCacheLines; i++)
    {
        cache.push_back(cacheEntry(0, 0));
    }
}

void FullyAssociativePLRU::processInstruction(unsigned long long addr)
{
    unsigned int tag = addr >> offsetBits;

    if (searchForMatch(tag) == true)
    {
        updateTreePath();
    }
    else
    {
        LRUReplacement(tag);
        updateTreePath();
    }
}

bool FullyAssociativePLRU::searchForMatch(unsigned int tag)
{
    for (int i = 0; i < totalCacheLines; i++)
    {
        if (cache[i].validBit == 1 && cache[i].tag == tag)
        {
            cacheHits++;
            return true;
        }
    }

    return false;
}

void FullyAssociativePLRU::LRUReplacement(unsigned int tag)
{
    int currentIndex = 0;
    int height = log2(512);
    int currentDepth = 1;

    while (currentDepth < height)
    {
        if (tree[currentIndex].val == 0)
        {
            currentIndex = getRightIndex(currentIndex);
        }
        else
        {
            currentIndex = getLeftIndex(currentIndex);
        }

        currentDepth++;
    }

    cache[tree[currentIndex].index + tree[currentIndex].val].tag = tag;
    cache[tree[currentIndex].index + tree[currentIndex].val].validBit = 1;
}

void FullyAssociativePLRU::updateTreePath()
{
    int currentIndex = 0;
    int next;

    while (currentIndex != -1)
    {
        next = (tree[currentIndex].val == 0) ? getLeftIndex(currentIndex) : getRightIndex(currentIndex);

        tree[currentIndex].val = (tree[currentIndex].val == 0) ? 1 : 0;

        currentIndex = next;
    }
}

int FullyAssociativePLRU::getLeftIndex(int curIndex)
{
    if (curIndex >= 255 && curIndex <= 510)
    {
        return -1;
    }
    return (curIndex * 2) + 1;
}

int FullyAssociativePLRU::getRightIndex(int curIndex)
{
    if (curIndex >= 255 && curIndex <= 510)
    {
        return -1;
    }
    return (curIndex * 2) + 2;
}