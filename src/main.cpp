#include <iostream>
#include <fstream>
#include <string>
#include "DirectMapped.h"
#include "SetAssociative.h"
#include "FullyAssociative.h"
#include "SetAssociativeNA.h"

using namespace std;

void printDirectMappedData(ofstream &outfile, DirectMapped &dm, int memoryAccesses);
void printSetAssociativityData(ofstream &outfile, SetAssociative &sa, int memoryAccesses);

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
    SetAssociativeNA sana = SetAssociativeNA();

    while (infile >> instructionType >> std::hex >> addr)
    {
        for (int i = 0; i < (int)dm.cacheSizes.size(); i++)
        {
            dm.processInstruction(dm.cacheSizes[i], addr);
        }

        for (int i = 0; i < (int)sa.associativitySizes.size(); i++)
        {
            sa.processInstruction(sa.associativitySizes[i], addr);
            sana.processInstructionNA(sana.associativitySizes[i], addr, instructionType);
        }

        fa.processInstruction(addr);

        memoryAccesses++;
    }

    printDirectMappedData(outfile, dm, memoryAccesses);

    printSetAssociativityData(outfile, sa, memoryAccesses);

    outfile << fa.cacheHits << "," << memoryAccesses << ";" << endl;

    printSetAssociativityData(outfile, sana, memoryAccesses);

    return 0;
}

void printDirectMappedData(ofstream &outfile, DirectMapped &dm, int memoryAccesses)
{
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
}

void printSetAssociativityData(ofstream &outfile, SetAssociative &sa, int memoryAccesses)
{
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
}