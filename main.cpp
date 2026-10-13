// Compiler: g++ 15.2.0 (MSYS2 UCRT64), C++20
#include "benchmark.h"
#include "sequence_io.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    const vector<size_t> lengths = {1000, 100'000, 10'000'000};
    const vector<size_t> ks = {1, 2, 3, 4, 6, 8, 12, 16, 24, 32, 64, 128, 256, 512, 1024};
    const int repeats = 5;

    printBuildInfo();

    for (size_t len : lengths)
    {
        string filename = "sequence_" + to_string(len) + ".txt";
        vector<int> seq = readSequenceFromFile(filename);

        cout << "========== Length " << len << " (file " << filename << ") ==========\n";
        benchmarkLibrary(seq, repeats);
        benchmarkOwn(seq, ks, repeats);
        cout << '\n';
    }

    return 0;
}
