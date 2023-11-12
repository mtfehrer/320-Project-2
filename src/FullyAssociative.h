#pragma once
#include <stdlib.h>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr){};
};

struct cacheEntryFA
{
    unsigned int validBit;
    unsigned int tag;
    cacheEntryFA(unsigned int v, unsigned int t) : validBit(v), tag(t){};
};

class FullyAssociative
{
public:
    FullyAssociative();
    void processInstruction(unsigned long long addr);
    vector<cacheEntryFA> cache;
    TreeNode root;
    int cacheHits;
    int offsetBits;
    int indexBits;
    int totalCacheLines;
};