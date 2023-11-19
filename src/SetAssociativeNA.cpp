#include "SetAssociativeNA.h"
#include <cmath>
#include <iostream>

using namespace std;

void SetAssociativeNA::processInstructionNA(int ways, unsigned long long addr, char instructionType)
{
    currentTime++;

    int cacheLinesInEachWay = totalCacheLines / ways;
    int indexBits = log2(cacheLinesInEachWay);

    unsigned int index = (addr >> offsetBits) & (cacheLinesInEachWay - 1);
    unsigned int tag = addr >> (offsetBits + indexBits);

    vector<int> validBits;
    vector<unsigned int> tagsInCache;

    pair<bool, int> val = searchForMatch(ways, index, tag);
    bool found = val.first;
    int LRUWayIndex = val.second;

    if (found == false && instructionType != 'S')
    {
        replaceLRU(LRUWayIndex, ways, index, tag);
    }
}