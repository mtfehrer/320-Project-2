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
    root = new TreeNode();
    int totalDepth = log2(totalCacheLines);
    int queueSize;

    queue<TreeNode *> q;
    q.push(root);
    int depth = 0;
    while (q.size() > 0)
    {
        queueSize = q.size();
        for (int i = 0; i < queueSize; i++)
        {
            TreeNode *node = q.front();
            q.pop();
            (*node).val = 1;
            (*node).left = new TreeNode();
            (*node).right = new TreeNode();
            if (depth < totalDepth - 1)
            {
                q.push((*node).left);
                q.push((*node).right);
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
        LRUReplacement(tag);
    }

    updateTreePath(index);
}

void FullyAssociative::LRUReplacement(unsigned int tag)
{
    TreeNode *currentNode = root;

    while ((*currentNode).left != nullptr && (*currentNode).right != nullptr)
    {
        if ((*currentNode).val == 0)
        {
            currentNode = (*currentNode).right;
        }
        else
        {
            currentNode = (*currentNode).left;
        }
    }

    cache[(*currentNode).index + (*currentNode).val].tag = tag;
    cache[(*currentNode).index + (*currentNode).val].validBit = 1;
}

void FullyAssociative::updateTreePath(unsigned int index)
{
    unsigned int m;
    int l = 0;
    int r = totalCacheLines - 1;
    TreeNode *currentNode = root;

    while (currentNode != nullptr)
    {
        m = (l + r) / 2;
        if (index < m)
        {
            (*currentNode).val = 0;
            currentNode = (*currentNode).left;
            r = m;
        }
        else
        {
            (*currentNode).val = 1;
            currentNode = (*currentNode).right;
            l = m;
        }
    }
}