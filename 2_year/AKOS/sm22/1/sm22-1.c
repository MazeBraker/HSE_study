#include <pthread.h>
#include <stdio.h>
// разобрано на семинаре 199
enum {
    NUM_OPS = 1000000,
    NUM_THREADS = 3,
    NUM_MINUS = 100
};

volatile double array[NUM_THREADS];
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void* func_m (void* arg) {
    int index = *(int*)arg;
    //printf("%d\n", index);
    for (int i = 0; i < NUM_OPS; i++) {
        pthread_mutex_lock(&m);
        array[index] += (double)(NUM_MINUS * (index + 1));
        array[(index+1)%3] -= (double)(NUM_MINUS * (index + 1) + 1);
        pthread_mutex_unlock(&m);
        if (i % 50 == 49) {
            sched_yield();
        }
    }
    return NULL;
}

int main() {
    pthread_t thread_id[NUM_THREADS];
    int ids[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        ids[i] = i;
        pthread_create(&thread_id[i], NULL, func_m, &ids[i]);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(thread_id[i], NULL);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        printf("%.10g\n", array[i]);
    }
    return 0;
}