#include <iostream>
#include <fstream>
#include <string>
#include "DirectMapped.h"

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

    while (infile >> instructionType >> std::hex >> addr)
    {
        for (int i = 0; i < (int)dm.cacheSizes.size(); i++)
        {
            dm.processInstruction(dm.cacheSizes[i], addr);
        }

        memoryAccesses++;
    }

    for (int i = 0; i < (int)dm.cacheSizes.size(); i++)
    {
        outfile << dm.cacheHits[i] << "," << memoryAccesses << ";";
        if (i == (int)dm.cacheSizes.size() - 1)
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
