#include <atomic>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

int main() {
    const int num_iterations = 10;

    std::mutex mtx;
    std::condition_variable cv;
    int current_thread = 1;  // 1, 2, or 3 - indicates which thread should print next

    // Thread 1: prints "1"
    std::thread thread1([&]() {
        for (int i = 0; i < num_iterations; ++i) {
            std::unique_lock<std::mutex> lock(mtx);

            // Wait until it's thread1's turn
            cv.wait(lock, [&] { return current_thread == 1; });

            std::cout << "1 ";

            // Switch turn to thread2
            current_thread = 2;
            cv.notify_all();
        }
    });

    // Thread 2: prints "2"
    std::thread thread2([&]() {
        for (int i = 0; i < num_iterations; ++i) {
            std::unique_lock<std::mutex> lock(mtx);

            // Wait until it's thread2's turn
            cv.wait(lock, [&] { return current_thread == 2; });

            std::cout << "2 ";

            // Switch turn to thread3
            current_thread = 3;
            cv.notify_all();
        }
    });

    // Thread 3: prints "3"
    std::thread thread3([&]() {
        for (int i = 0; i < num_iterations; ++i) {
            std::unique_lock<std::mutex> lock(mtx);

            // Wait until it's thread3's turn
            cv.wait(lock, [&] { return current_thread == 3; });

            std::cout << "3 ";

            // Switch turn back to thread1
            current_thread = 1;
            cv.notify_all();
        }
    });

    // Wait for all threads to complete
    thread1.join();
    thread2.join();
    thread3.join();

    std::cout << "\nAll three threads completed!\n";

    return 0;
}