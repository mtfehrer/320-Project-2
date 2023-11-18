#include <iostream>
#include <fstream>
#include <string>
#include "DirectMapped.h"
#include "SetAssociative.h"
#include "FullyAssociative.h"
#include "SetAssociativeNoAllocation.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cout << "Need two arguments" << endl;
        exit(0);
    }
    ifstream infile(argv[1]);
    ofstream outfile(argv[2]);

    char instructionType;
    unsigned long long addr;
    int memoryAccesses = 0;
    DirectMapped dm = DirectMapped();
    SetAssociative sa = SetAssociative();
    FullyAssociative fa = FullyAssociative();
    SetAssociativeNoAllocation sana = SetAssociativeNoAllocation();

    while (infile >> instructionType >> std::hex >> addr)
    {
        for (int i = 0; i < (int)dm.cacheSizes.size(); i++)
        {
            dm.processInstruction(dm.cacheSizes[i], addr);
        }

        for (int i = 0; i < (int)sa.associativitySizes.size(); i++)
        {
            sa.processInstruction(sa.associativitySizes[i], addr);
        }

        fa.processInstruction(addr);

        for (int i = 0; i < (int)sana.associativitySizes.size(); i++)
        {
            sana.processInstruction(sana.associativitySizes[i], addr);
        }

        memoryAccesses++;
    }

    for (int i = 0; i < (int)dm.cacheSizes.size(); i++)
    {
        outfile << dm.cacheHits[dm.cacheSizes[i]] << "," << memoryAccesses << ";";
        if (i == (int)dm.cacheSizes.size() - 1)
        {
            outfile << endl;
        }
        else
        {
            outfile << " ";
        }
    }

    for (int i = 0; i < (int)sa.associativitySizes.size(); i++)
    {
        outfile << sa.cacheHits[sa.associativitySizes[i]] << "," << memoryAccesses << ";";
        if (i == (int)sa.associativitySizes.size() - 1)
        {
            outfile << endl;
        }
        else
        {
            outfile << " ";
        }
    }

    outfile << fa.cacheHits << "," << memoryAccesses << ";" << endl;

    for (int i = 0; i < (int)sana.associativitySizes.size(); i++)
    {
        outfile << sana.cacheHits[sana.associativitySizes[i]] << "," << memoryAccesses << ";";
        if (i == (int)sana.associativitySizes.size() - 1)
        {
            outfile << endl;
        }
        else
        {
            outfile << " ";
        }
    }

    return 0;
}
