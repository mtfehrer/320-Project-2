#pragma once
#include <stdlib.h>

class DirectMapped
{
public:
    DirectMapped();
    void processInstruction1KB(char instructionType, unsigned long long addr);
    unsigned int validBit1KB[32];
    unsigned int tag1KB[32];
    int cacheHits1KB;
};