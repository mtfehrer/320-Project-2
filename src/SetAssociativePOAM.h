#pragma once
#include <stdlib.h>
#include <map>
#include <string>
#include <vector>
#include "SetAssociative.h"

using namespace std;

class SetAssociativePOAM : public SetAssociative
{
public:
    SetAssociativePOAM() : SetAssociative(){};
    void processInstructionPOAM(int sizeInKB, unsigned long long addr);
    pair<bool, int> searchForMatchPOAM(int ways, unsigned int cacheIndex, unsigned int tag, bool updateHits);
};