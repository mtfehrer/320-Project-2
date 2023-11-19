#pragma once

struct cacheEntry
{
    unsigned int validBit;
    unsigned int tag;
    cacheEntry(unsigned int v, unsigned int t) : validBit(v), tag(t){};
};

struct cacheEntryLRU
{
    unsigned int validBit;
    unsigned int tag;
    unsigned long long lastUsedTime;
    cacheEntryLRU(unsigned int v, unsigned int t) : validBit(v), tag(t), lastUsedTime(0){};
};