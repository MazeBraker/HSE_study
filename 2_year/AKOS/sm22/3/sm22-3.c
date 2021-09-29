#include <limits.h>
#include <pthread.h>
#include <sched.h>
#include <stdatomic.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct Item {
    struct Item *next;
    long long value;
};

struct Item *_Atomic head = NULL;

void *thread_gen(void *ptr) {
    long start = (long) ptr;

    for (int i = 0; i < 1000; ++i) {
        struct Item *tmp = malloc(sizeof(tmp));
        tmp->next = atomic_exchange(&head, tmp);
        tmp->value = start + i;
        sched_yield();
    }

    return NULL;
}

int main() {
    pthread_t sinks[100];

    pthread_attr_t atr;
    pthread_attr_init(&atr);
    pthread_attr_setstacksize(&atr, PTHREAD_STACK_MIN);

    for (int i = 0; i < 100; ++i) {
        pthread_create(&sinks[i], &atr, thread_gen, (void *) ((long) i * 1000)); //(void*)(intptr_t)i
    }
    pthread_attr_destroy(&atr);

    for (int i = 0; i < 100; ++i) {
        pthread_join(sinks[i], NULL);
    }

    while (head) {
        struct Item *t = head;
        printf("%lld\n", head->value);
        head = head->next;
        free(t);
    }
    return 0;
}