#pragma once
#include <stdlib.h>

class DirectMapped
{
public:
    DirectMapped();
    void processInstruction1KB(char instructionType, unsigned long long addr);
    unsigned int *cache1KB;
    int cacheHits1KB;
};