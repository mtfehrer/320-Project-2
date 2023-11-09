#include "DirectMapped.h"
#include <cmath>
#include <iostream>

using namespace std;

DirectMapped::DirectMapped()
{
    for (int i = 0; i < 32; i++)
    {
        validBit1KB[i] = 0;
        tag1KB[i] = 0;
    }
    cacheHits1KB = 0;
}

void DirectMapped::processInstruction1KB(char instructionType, unsigned long long addr)
{
    // int addressBits = 32;
    int offsetBits = 5;
    int indexBits = 5;
    // int tagBits = addressBits - offsetBits - indexBits;

    // unsigned int offset = addr & ((int)pow(2, offsetBits) - 1);
    // unsigned int index = (addr >> offsetBits) & ((int)pow(2, indexBits) - 1);
    unsigned int index = (addr >> offsetBits) & 31;
    unsigned int tag = addr >> (offsetBits + indexBits);

    if (instructionType == 'S')
    {
        tag1KB[index] = tag;
        validBit1KB[index] = 1;
    }
    else if (instructionType == 'L')
    {
        unsigned int validBit = validBit1KB[index];
        unsigned int tagInCache = tag1KB[index];

        if (validBit == 1 && tagInCache == tag)
        {
            cacheHits1KB++;
        }
    }
}