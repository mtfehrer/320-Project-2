#pragma once
#include <stdlib.h>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct cacheEntry
{
    unsigned int validBit;
    unsigned int tag;
    cacheEntry(unsigned int v, unsigned int t) : validBit(v), tag(t){};
};

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