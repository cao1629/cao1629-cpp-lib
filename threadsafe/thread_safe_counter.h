#ifndef THREAD_SAFE_COUNTER_H
#define THREAD_SAFE_COUNTER_H

#include <mutex>
#include <atomic>

namespace threadsafe {

// Thread-safe counter using mutex for protection
template <typename T = int>
class ThreadSafeCounter {
public:
    ThreadSafeCounter(T initial_value = T{}) : value_(initial_value) {}

    // Copy constructor
    ThreadSafeCounter(const ThreadSafeCounter& other) {
        std::lock_guard<std::mutex> lock(other.mutex_);
        value_ = other.value_;
    }

    // Assignment operator
    ThreadSafeCounter& operator=(const ThreadSafeCounter& other) {
        if (this != &other) {
            std::lock(mutex_, other.mutex_);
            std::lock_guard<std::mutex> lock1(mutex_, std::adopt_lock);
            std::lock_guard<std::mutex> lock2(other.mutex_, std::adopt_lock);
            value_ = other.value_;
        }
        return *this;
    }

    // Increment operations
    T operator++() {  // Pre-increment
        std::lock_guard<std::mutex> lock(mutex_);
        return ++value_;
    }

    T operator++(int) {  // Post-increment
        std::lock_guard<std::mutex> lock(mutex_);
        return value_++;
    }

    // Decrement operations
    T operator--() {  // Pre-decrement
        std::lock_guard<std::mutex> lock(mutex_);
        return --value_;
    }

    T operator--(int) {  // Post-decrement
        std::lock_guard<std::mutex> lock(mutex_);
        return value_--;
    }

    // Add operation
    T operator+=(T delta) {
        std::lock_guard<std::mutex> lock(mutex_);
        value_ += delta;
        return value_;
    }

    // Subtract operation
    T operator-=(T delta) {
        std::lock_guard<std::mutex> lock(mutex_);
        value_ -= delta;
        return value_;
    }

    // Get current value
    T get() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return value_;
    }

    // Set value
    void set(T new_value) {
        std::lock_guard<std::mutex> lock(mutex_);
        value_ = new_value;
    }

    // Reset to zero (or default value)
    void reset(T reset_value = T{}) {
        std::lock_guard<std::mutex> lock(mutex_);
        value_ = reset_value;
    }

    // Exchange value atomically
    T exchange(T new_value) {
        std::lock_guard<std::mutex> lock(mutex_);
        T old_value = value_;
        value_ = new_value;
        return old_value;
    }

private:
    mutable std::mutex mutex_;
    T value_;
};

// Lock-free atomic counter for better performance with integral types
template <typename T = int>
class AtomicCounter {
    static_assert(std::is_integral_v<T>, "AtomicCounter only supports integral types");

public:
    AtomicCounter(T initial_value = T{}) : value_(initial_value) {}

    // Copy constructor
    AtomicCounter(const AtomicCounter& other) : value_(other.value_.load()) {}

    // Assignment operator
    AtomicCounter& operator=(const AtomicCounter& other) {
        value_.store(other.value_.load());
        return *this;
    }

    // Increment operations
    T operator++() {  // Pre-increment
        return value_.fetch_add(1) + 1;
    }

    T operator++(int) {  // Post-increment
        return value_.fetch_add(1);
    }

    // Decrement operations
    T operator--() {  // Pre-decrement
        return value_.fetch_sub(1) - 1;
    }

    T operator--(int) {  // Post-decrement
        return value_.fetch_sub(1);
    }

    // Add operation
    T operator+=(T delta) {
        return value_.fetch_add(delta) + delta;
    }

    // Subtract operation
    T operator-=(T delta) {
        return value_.fetch_sub(delta) - delta;
    }

    // Get current value
    T get() const {
        return value_.load();
    }

    // Set value
    void set(T new_value) {
        value_.store(new_value);
    }

    // Reset to zero (or default value)
    void reset(T reset_value = T{}) {
        value_.store(reset_value);
    }

    // Exchange value atomically
    T exchange(T new_value) {
        return value_.exchange(new_value);
    }

    // Compare and swap
    bool compare_exchange_weak(T& expected, T desired) {
        return value_.compare_exchange_weak(expected, desired);
    }

    bool compare_exchange_strong(T& expected, T desired) {
        return value_.compare_exchange_strong(expected, desired);
    }

private:
    std::atomic<T> value_;
};

} // namespace threadsafe

#endif // THREAD_SAFE_COUNTER_H
