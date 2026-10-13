// Compiler: g++ 15.2.0 (MSYS2 UCRT64), C++20
#include "sequence_io.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    const vector<size_t> lengths = {1000, 100'000, 10'000'000};
    const int minVal = -1000, maxVal = 1000;

    for (size_t len : lengths)
    {
        string filename = "sequence_" + to_string(len) + ".txt";
        saveSequenceToFile(generateSequence(len, minVal, maxVal), filename);
        cout << "Saved " << filename << '\n';
    }

    return 0;
}
