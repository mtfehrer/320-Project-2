#include "DirectMapped.h"
#include <cmath>
#include <iostream>

using namespace std;

DirectMapped::DirectMapped()
{
    cacheSizes = {1, 4, 16, 32};
    for (int i = 0; i < cacheSizes.size(); i++)
    {
        cacheEntries[cacheSizes[i]].push_back(cacheEntry(0, 0));
        cacheHits[cacheSizes[i]] = 0;
    }
}

void DirectMapped::processInstruction(char instructionType, unsigned long long addr)
{
    // int addressBits = 32;
    int offsetBits = 5;
    int indexBits = 5;
    // int tagBits = addressBits - offsetBits - indexBits;

    // unsigned int offset = addr & ((int)pow(2, offsetBits) - 1);
    // unsigned int index = (addr >> offsetBits) & ((int)pow(2, indexBits) - 1);
    unsigned int index = (addr >> offsetBits) & 31;
    unsigned int tag = addr >> (offsetBits + indexBits);

    unsigned int validBit = validBit1KB[index];
    unsigned int tagInCache = tag1KB[index];

    if (validBit == 1 && tagInCache == tag)
    {
        cacheHits1KB++;
    }
    else
    {
        tag1KB[index] = tag;
        validBit1KB[index] = 1;
    }
}