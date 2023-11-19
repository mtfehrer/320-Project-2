#include "SetAssociativeNLP.h"
#include <cmath>
#include <iostream>

using namespace std;

void SetAssociativeNLP::processInstructionNLP(int ways, unsigned long long addr)
{
    currentTime++;

    int cacheLinesInEachWay = totalCacheLines / ways;
    int indexBits = log2(cacheLinesInEachWay);

    unsigned int index = (addr >> offsetBits) & (cacheLinesInEachWay - 1);
    unsigned int tag = addr >> (offsetBits + indexBits);

    pair<bool, int> val = searchForMatch(ways, index, tag);
    bool found = val.first;
    int LRUWayIndex = val.second;

    if (found == false)
    {
        replaceLRU(LRUWayIndex, ways, index, tag);
    }

    // second part

    currentTime++;

    // this doesn't wrap around which could be problematic
    if ((int)index != cacheLinesInEachWay - 1)
    {
        index++;
    }

    tag = addr >> (offsetBits + indexBits);

    val = searchForMatch(ways, index, tag);
    found = val.first;
    LRUWayIndex = val.second;

    if (found == false)
    {
        replaceLRU(LRUWayIndex, ways, index, tag);
    }
}