#pragma once

class DirectMapped
{
public:
    DirectMapped();
    void processInstruction(char instructionType, unsigned long long addr);
    int cacheHits1;
    int cacheHits4;
    int cacheHits16;
    int cacheHits32;
};