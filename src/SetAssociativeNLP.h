#pragma once
#include <stdlib.h>
#include <map>
#include <string>
#include <vector>
#include "SetAssociative.h"

using namespace std;

class SetAssociativeNLP : public SetAssociative
{
public:
    SetAssociativeNLP() : SetAssociative(){};
    void processInstructionNLP(int sizeInKB, unsigned long long addr);
};