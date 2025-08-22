#include "thread_safe_counter.h"
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

using namespace threadsafe;

void test_mutex_counter() {
    std::cout << "Testing ThreadSafeCounter (mutex-based):\n";

    ThreadSafeCounter<int> counter(0);
    const int num_threads = 4;
    const int increments_per_thread = 1000;

    std::vector<std::thread> threads;

    auto start = std::chrono::high_resolution_clock::now();

    // Create threads that increment the counter
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&counter, increments_per_thread]() {
            for (int j = 0; j < increments_per_thread; ++j) {
                ++counter;
            }
        });
    }

    // Wait for all threads to complete
    for (auto& t : threads) {
        t.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Expected: " << num_threads * increments_per_thread << std::endl;
    std::cout << "Actual: " << counter.get() << std::endl;
    std::cout << "Time: " << duration.count() << " microseconds\n\n";
}

void test_atomic_counter() {
    std::cout << "Testing AtomicCounter (lock-free):\n";

    AtomicCounter<int> counter(0);
    const int num_threads = 4;
    const int increments_per_thread = 1000;

    std::vector<std::thread> threads;

    auto start = std::chrono::high_resolution_clock::now();

    // Create threads that increment the counter
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&counter, increments_per_thread]() {
            for (int j = 0; j < increments_per_thread; ++j) {
                ++counter;
            }
        });
    }

    // Wait for all threads to complete
    for (auto& t : threads) {
        t.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Expected: " << num_threads * increments_per_thread << std::endl;
    std::cout << "Actual: " << counter.get() << std::endl;
    std::cout << "Time: " << duration.count() << " microseconds\n\n";
}

void test_operations() {
    std::cout << "Testing various operations:\n";

    AtomicCounter<int> counter(10);

    std::cout << "Initial value: " << counter.get() << std::endl;
    std::cout << "Pre-increment: " << ++counter << std::endl;
    std::cout << "Post-increment: " << counter++ << std::endl;
    std::cout << "Current value: " << counter.get() << std::endl;
    std::cout << "Add 5: " << (counter += 5) << std::endl;
    std::cout << "Subtract 3: " << (counter -= 3) << std::endl;
    std::cout << "Exchange with 100: " << counter.exchange(100) << std::endl;
    std::cout << "Final value: " << counter.get() << std::endl;

    counter.reset();
    std::cout << "After reset: " << counter.get() << std::endl;
}

int main() {
    test_mutex_counter();
    test_atomic_counter();
    test_operations();

    return 0;
}
