#include <queue>
#include <cmath>
#include "FullyAssociative.h"

using namespace std;

FullyAssociative::FullyAssociative()
{
    offsetBits = log2(32);
    totalCacheLines = (16 * 1024) / 32;
    indexBits = log2(totalCacheLines);
    cacheHits = 0;
    root = TreeNode();
    int totalDepth = log2(totalCacheLines);
    int queueSize;

    queue<TreeNode> q;
    q.push(root);
    int depth = 0;
    while (q.size() > 0)
    {
        queueSize = q.size();
        for (int i = 0; i < queueSize; i++)
        {
            TreeNode node = q.front();
            q.pop();
            node.val = 1;
            TreeNode l = TreeNode();
            TreeNode r = TreeNode();
            node.left = &l;
            node.right = &r;
            if (depth < totalDepth - 1)
            {
                q.push(l);
                q.push(r);
            }
        }
        depth += 1;
    }

    for (int i = 0; i < totalCacheLines; i++)
    {
        cache.push_back(cacheEntryFA(0, 0));
    }
}

void FullyAssociative::processInstruction(unsigned long long addr)
{
    unsigned int index = (addr >> offsetBits) & (totalCacheLines - 1);
    unsigned int tag = addr >> (offsetBits + indexBits);

    unsigned int validBitInCache = cache[index].validBit;
    unsigned int tagInCache = cache[index].tag;

    if (validBitInCache == 1 && tagInCache == tag)
    {
        cacheHits++;
    }
    else
    {
        cache[index].tag = tag;
        cache[index].validBit = 1;
    }
}