#include <pthread.h>
#include <stdio.h>
#include <thread>
#include <mutex>
// разобрано на семе 199
enum {
    NUM_OPS = 1000000,
    NUM_THREADS = 3,
    NUM_DELTA = 100
};

volatile double array[NUM_THREADS];
std::mutex m;

void func (int index) {
    for (int i = 0; i < NUM_OPS; i++) {
        // RAII
        // m.lock();
        {
            std::lock_guard<std::mutex> lk(m);
            // (C-style), static_cast
            array[index] += static_cast<double>(80 + 20 * index);
            array[(index+1)%3] -= static_cast<double>(90 + 20 * index);
        }
        //m.unlock();
        if (i % 50 == 49) {
            sched_yield();
        }
    }
}

int main() {
    std::thread threads[NUM_THREADS];
    // std::vector<std::thread>threads;

    for (int i = 0; i < NUM_THREADS; i++) {
        // threads.emplace_back(func, i)
        threads[i] = std::thread(func, i);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        printf("%.10g\n", array[i]);
    }
    return 0;
}