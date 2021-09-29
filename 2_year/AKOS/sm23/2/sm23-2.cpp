#include <thread>
#include <future>
#include <exception>
#include <iostream>
#include <vector>
#include <future>
// разобрано на семе 199
int is_prime(uint64_t n) {
    if (n == 2) {
        return 1;
    }
    if (n == 1 || (n % 2) == 0) {
        return 0;
    }
    for (int32_t i = 3; (int64_t) i * i <= n; i += 2) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

void func(uint64_t low, uint64_t high, 
    std::vector<std::promise<uint64_t>>&promises) {

    size_t index = 0;
    for (uint64_t i = low; i <= high; i++) {
        if (is_prime(i)) {
            promises[index].set_value(i);
            if (promises.size() - 1 == index) {
                return;
            }
            index++;
        }
    }
    try {
        throw high;
    } catch (...) {
        promises[index].set_exception(std::current_exception());
    }
}

int main() {
    uint64_t low, high;
    int32_t count;
    std::cin >> low >> high >> count;
    
    std::vector<std::promise<uint64_t>> promises(count);
    std::thread th(func, low, high, std::ref(promises));
    try {
        for (int i = 0; i < count; i++) {
            std::future<uint64_t> f = promises[i].get_future();
            std::cout << f.get() << std::endl;
        }
        
    } catch(uint64_t e) {
        std::cout << e << std::endl;
    }
    th.join();
    return 0;
}