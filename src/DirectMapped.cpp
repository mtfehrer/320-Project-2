#include "DirectMapped.h"
#include <cmath>

using namespace std;

DirectMapped::DirectMapped()
{
    cache1KB = (int *)calloc(1, 1000);
    cacheHits1KB = 0;
}

void DirectMapped::processInstruction1KB(char instructionType, unsigned long long addr)
{
    int addressBits = 32;
    int offsetBits = 5;
    int indexBits = 5;
    // int tagBits = addressBits - offsetBits - indexBits;

    // int offset = addr & ((int)pow(2, offsetBits) - 1);
    int index = (addr >> offsetBits) & ((int)pow(2, indexBits) - 1);
    int tag = addr >> (offsetBits + indexBits);

    if (instructionType == 'S')
    {
        // set tag
        cache1KB[index] = (tag << (addressBits - 1 - 1));
        // set valid bit to 1
        cache1KB[index] |= (1 << (addressBits - 1));
    }
    else if (instructionType == 'L')
    {
        int validBit = cache1KB[index] & (1 << (addressBits - 1));
        int tagInCache = (cache1KB[index] << 1) >> (offsetBits + indexBits);

        if (validBit == 1 and tagInCache == tag)
        {
            cacheHits1KB++;
        }
    }
}