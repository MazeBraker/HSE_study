#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
// разобранно на семе 199

uint64_t last_prime = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

int is_prime(uint64_t n) {
    if (n == 1 || (n % 2) == 0) {
        return 0;
    }
    if (n == 2) {
        return 1;
    }
    for (int32_t i = 3; (int64_t) i * i <= n; i += 2) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

void* func(void* ptr) {
    uint64_t base = *(uint64_t*)ptr;
    while(1) {
        if (is_prime(base)) {
            pthread_mutex_lock(&m);
            last_prime = base;
            pthread_cond_signal(&c);
            pthread_mutex_unlock(&m);
        }
        ++base;
    }
} 

int main() {
    uint64_t base;
    int32_t count;
    scanf("%"SCNu64" %"SCNd32, &base, &count);
    
    pthread_t thread_id;

    pthread_create(&thread_id, NULL, func, &base);

    uint64_t prev_prime = 0;

    for (int i = 0; i < count; i++) {
        pthread_mutex_lock(&m);
        while (last_prime == prev_prime) {
            pthread_cond_wait(&c, &m);
        }
        pthread_mutex_unlock(&m);

        prev_prime = last_prime;

        printf("%" PRIu64 "\n", last_prime);
    }

    return 0;
}