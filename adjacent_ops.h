#ifndef ADJACENT_OPS_H
#define ADJACENT_OPS_H

#include <algorithm>
#include <cstddef>
#include <execution>
#include <numeric>
#include <vector>

void requireAdjacentPair(const std::vector<int>& seq);

int maxAdjacentDifference(const std::vector<int>& seq);

int maxAdjacentDifferenceParallel(const std::vector<int>& seq, std::size_t k);

template <class Policy>
int maxAdjacentDifference(Policy&& policy, const std::vector<int>& seq)
{
    requireAdjacentPair(seq);

    std::vector<int> diff(seq.size());
    std::adjacent_difference(policy, seq.begin(), seq.end(), diff.begin());

    return *std::max_element(policy, diff.begin() + 1, diff.end());
}

#endif
