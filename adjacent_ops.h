#ifndef ADJACENT_OPS_H
#define ADJACENT_OPS_H

#include <algorithm>
#include <cstddef>
#include <execution>
#include <numeric>
#include <vector>

void requireAdjacentPair(const std::vector<int>& seq);

inline constexpr auto difference = [](int current, int previous)
{
    return static_cast<long long>(current) - previous;
};

long long maxAdjacentDifference(const std::vector<int>& seq);

long long maxAdjacentDifferenceParallel(const std::vector<int>& seq, std::size_t k);

template <class Policy>
long long maxAdjacentDifference(Policy&& policy, const std::vector<int>& seq)
{
    requireAdjacentPair(seq);

    std::vector<long long> diff(seq.size());
    std::adjacent_difference(policy, seq.begin(), seq.end(), diff.begin(), difference);

    return *std::max_element(policy, diff.begin() + 1, diff.end());
}

#endif
