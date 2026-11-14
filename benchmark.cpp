#include "benchmark.h"
#include "adjacent_ops.h"

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>

using namespace std;

#ifndef BUILD_OPT_LEVEL
#ifdef __OPTIMIZE__
#define BUILD_OPT_LEVEL "optimized (level not passed)"
#else
#define BUILD_OPT_LEVEL "-O0"
#endif
#endif

namespace
{
    struct Measurement
    {
        double ms;
        long long result;
    };

    template <class Func>
    Measurement measure(Func&& func, int repeats)
    {
        vector<double> times;
        times.reserve(repeats);
        long long result = 0;

        for (int i = 0; i < repeats; ++i)
        {
            auto start = chrono::steady_clock::now();
            result = func();
            auto stop = chrono::steady_clock::now();
            times.push_back(chrono::duration<double, milli>(stop - start).count());
        }

        sort(times.begin(), times.end());
        return {times[times.size() / 2], result};
    }

    void printHeader(const string& firstColumn)
    {
        cout << left << setw(20) << firstColumn
             << right << setw(15) << "Time" << setw(10) << "Result" << '\n';
    }

    void printRow(const string& name, const Measurement& m)
    {
        cout << left << setw(20) << name
             << right << setw(12) << fixed << setprecision(3) << m.ms << " ms"
             << setw(10) << m.result << '\n';
    }

    void printBestKRatio(size_t bestK, unsigned hwThreads)
    {
        if (hwThreads == 0)
        {
            cout << "Best K / hardware threads: unknown (hardware_concurrency() returned 0)\n";
            return;
        }

        cout << "Best K / hardware threads = " << bestK << " / " << hwThreads
             << " = " << setprecision(2) << static_cast<double>(bestK) / hwThreads << '\n';
    }
}

void printBuildInfo()
{
    cout << "Build: optimization " << BUILD_OPT_LEVEL << ", parallel backend for policies: ";
#if defined(_PSTL_PAR_BACKEND_TBB)
    cout << "TBB (par/par_unseq run in parallel)\n\n";
#else
    cout << "serial (no TBB: par/par_unseq run sequentially)\n\n";
#endif
}

void benchmarkLibrary(const vector<int>& seq, int repeats)
{
    cout << "--- Library: adjacent_difference + max_element (median of " << repeats << " runs) ---\n";
    printHeader("Variant");

    printRow("no policy", measure([&] { return maxAdjacentDifference(seq); }, repeats));
    printRow("execution::seq", measure([&] { return maxAdjacentDifference(execution::seq, seq); }, repeats));
    printRow("execution::par", measure([&] { return maxAdjacentDifference(execution::par, seq); }, repeats));
    printRow("execution::par_unseq", measure([&] { return maxAdjacentDifference(execution::par_unseq, seq); }, repeats));
    printRow("execution::unseq", measure([&] { return maxAdjacentDifference(execution::unseq, seq); }, repeats));
}

void benchmarkOwn(const vector<int>& seq, const vector<size_t>& ks, int repeats)
{
    const unsigned hwThreads = thread::hardware_concurrency();

    cout << "\n--- Own algorithm: K threads, each runs sequential adjacent_difference ---\n";
    cout << "Hardware threads: " << hwThreads << ", median of " << repeats << " runs\n";
    printHeader("K");

    double bestMs = 0;
    size_t bestK = 0;

    for (size_t k : ks)
    {
        if (k >= seq.size())
            break;

        Measurement m = measure([&] { return maxAdjacentDifferenceParallel(seq, k); }, repeats);
        printRow(to_string(k), m);

        if (bestK == 0 || m.ms < bestMs)
        {
            bestMs = m.ms;
            bestK = k;
        }
    }

    cout << "Best K = " << bestK << " (" << bestMs << " ms)\n";
    printBestKRatio(bestK, hwThreads);
}
