#include <atomic>
#include <iostream>
#include <thread>
#include <chrono>
#include <fmt/core.h>
#include <mutex>
#include <condition_variable>

int main() {
    const int num_iterations = 10;

    std::mutex mtx;
    std::condition_variable cv;
    bool turn_for_thread1 = true;  // true = thread1's turn, false = thread2's turn

    // Thread 1: prints "1"
    std::thread thread1([&]() {
        for (int i = 0; i < num_iterations; ++i) {
            std::unique_lock<std::mutex> lock(mtx);

            // Wait until it's thread1's turn
            cv.wait(lock, [&] { return turn_for_thread1; });

            fmt::print("1 ");

            // Switch turn to thread2
            turn_for_thread1 = false;
            cv.notify_one();
        }
    });

    // Thread 2: prints "2"
    std::thread thread2([&]() {
        for (int i = 0; i < num_iterations; ++i) {
            std::unique_lock<std::mutex> lock(mtx);

            // Wait until it's thread2's turn
            cv.wait(lock, [&] { return !turn_for_thread1; });

            fmt::print("2 ");

            // Switch turn to thread1
            turn_for_thread1 = true;
            cv.notify_one();
        }
    });

    // Wait for both threads to complete
    thread1.join();
    thread2.join();

    fmt::print("\nBoth threads completed!\n");

    return 0;
}