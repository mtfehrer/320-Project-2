#pragma once
#include <stdlib.h>
#include <map>
#include <string>
#include <vector>
#include "SetAssociative.h"

using namespace std;

class SetAssociativeNA : public SetAssociative
{
public:
    SetAssociativeNA() : SetAssociative(){};
    void processInstructionNA(int sizeInKB, unsigned long long addr, char instructionType);
};