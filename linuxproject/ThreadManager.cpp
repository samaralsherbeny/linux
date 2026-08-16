#include "ThreadManager.h"
#include <thread>
#include <vector>
#include <iostream>
#include <mutex>
#include <algorithm>
#include <stdexcept>

void ThreadManager::multiThreadExample(int threadCount) const {
    if (threadCount < 1 || threadCount > 32) {
        std::cerr << "Choose between 1 and 32 threads.\n";
        return;
    }

    constexpr long long N = 1000000;
    std::vector<long long> partial(static_cast<size_t>(threadCount), 0);
    std::vector<std::thread> threads;

    long long block = N / threadCount;
    for (int i = 0; i < threadCount; ++i) {
        long long start = i * block + 1;
        long long end = (i == threadCount - 1) ? N : (i + 1) * block;
        threads.emplace_back([&, i, start, end]() {
            long long sum = 0;
            for (long long x = start; x <= end; ++x) sum += x;
            partial[static_cast<size_t>(i)] = sum;
        });
    }

    for (auto& t : threads) t.join();

    long long total = 0;
    for (long long value : partial) total += value;

    long long expected = N * (N + 1) / 2;
    std::cout << "\n=== Multi-threaded Example ===\n";
    std::cout << "Threads: " << threadCount << '\n';
    std::cout << "Sum 1.." << N << " = " << total << '\n';
    std::cout << "Expected = " << expected << '\n';
    std::cout << "Result: " << (total == expected ? "correct" : "incorrect") << '\n';
}
