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
        dm.processInstruction(instructionType, addr);

        memoryAccesses++;
    }

    outfile << dm.cacheHits1 << "," << memoryAccesses << ";";
    outfile << dm.cacheHits4 << "," << memoryAccesses << ";";
    outfile << dm.cacheHits16 << "," << memoryAccesses << ";";
    outfile << dm.cacheHits32 << "," << memoryAccesses << ";" << endl;

    return 0;
}
