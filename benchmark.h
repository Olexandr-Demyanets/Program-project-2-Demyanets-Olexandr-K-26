#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <cstddef>
#include <vector>

void printBuildInfo();

void benchmarkLibrary(const std::vector<int>& seq, int repeats);

void benchmarkOwn(const std::vector<int>& seq, const std::vector<std::size_t>& ks, int repeats);

#endif
