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
        dm.processInstruction1KB(instructionType, addr);

        memoryAccesses++;
    }

    outfile << dm.cacheHits1KB << "," << memoryAccesses << ";" << endl;

    return 0;
}
