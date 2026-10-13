#include "adjacent_ops.h"

#include <stdexcept>
#include <thread>

using namespace std;

namespace
{
    using Iter = vector<int>::const_iterator;

    int maxDifferenceInRange(Iter first, Iter last)
    {
        vector<int> diff(last - first);
        adjacent_difference(first, last, diff.begin());

        return *max_element(diff.begin() + 1, diff.end());
    }
}

void requireAdjacentPair(const vector<int>& seq)
{
    if (seq.size() < 2)
        throw invalid_argument("Need at least 2 elements to compute difference");
}

int maxAdjacentDifference(const vector<int>& seq)
{
    requireAdjacentPair(seq);

    return maxDifferenceInRange(seq.begin(), seq.end());
}

int maxAdjacentDifferenceParallel(const vector<int>& seq, size_t k)
{
    requireAdjacentPair(seq);

    size_t pairs = seq.size() - 1;
    k = clamp(k, size_t{1}, pairs);

    size_t base = pairs / k;
    size_t rem = pairs % k;

    vector<int> partial(k);
    vector<thread> threads;
    threads.reserve(k);

    size_t first = 0;
    for (size_t j = 0; j < k; ++j)
    {
        size_t count = base + (j < rem ? 1 : 0);
        size_t last = first + count + 1;

        threads.emplace_back([&seq, &partial, j, first, last]()
        {
            partial[j] = maxDifferenceInRange(seq.begin() + first, seq.begin() + last);
        });

        first = last - 1;
    }

    for (auto& t : threads)
        t.join();

    return *max_element(partial.begin(), partial.end());
}
