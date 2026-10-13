#include "sequence_io.h"

#include <fstream>
#include <random>
#include <stdexcept>

using namespace std;

vector<int> generateSequence(size_t length, int minVal, int maxVal)
{
    vector<int> result(length);

    random_device r;
    seed_seq seeds{r(), r(), r(), r(), r(), r()};
    mt19937 engine(seeds);
    uniform_int_distribution<int> dist(minVal, maxVal);

    for (size_t i = 0; i < length; ++i)
        result[i] = dist(engine);

    return result;
}

void saveSequenceToFile(const vector<int>& seq, const string& filename)
{
    ofstream out(filename);
    if (!out)
        throw runtime_error("Cannot open file for writing: " + filename);

    out << seq.size() << "\n";
    for (int value : seq)
        out << value << "\n";
}

vector<int> readSequenceFromFile(const string& filename)
{
    ifstream in(filename);
    if (!in)
        throw runtime_error("Cannot open file for reading: " + filename);

    size_t n = 0;
    in >> n;
    vector<int> result;
    result.reserve(n);

    for (size_t i = 0; i < n; ++i)
    {
        int x;
        in >> x;
        result.push_back(x);
    }

    return result;
}

