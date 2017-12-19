#pragma once
#include <queue>
#include <mutex>
#include <iostream>

template <typename T>
class ThreadQueue {
private:
    std::queue<T> queue;
    std::mutex mutex;
public:

    void Push(T const &data) {
        std::unique_lock<std::mutex> lock (mutex);
        queue.push(data);
        lock.unlock();
    }

    bool IsEmpty() {
        std::unique_lock<std::mutex> lock (mutex);
        return queue.empty();
    }

    bool Pop(T &popped_value) {
        std::unique_lock<std::mutex> lock (mutex);
        if (queue.empty()) {
            return false;
        } else {
            popped_value = queue.front();
            queue.pop();
            return true;
        }
    }
};