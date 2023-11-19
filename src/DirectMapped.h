#pragma once
#include <stdlib.h>
#include <map>
#include <string>
#include <vector>
#include "CacheEntryStructs.h"

using namespace std;

class DirectMapped
{
public:
    DirectMapped();
    void processInstruction(int sizeInKB, unsigned long long addr);
    vector<int> cacheSizes;
    map<int, vector<cacheEntry>> cacheEntries;
    map<int, int> cacheHits;
    int offsetBits;
};