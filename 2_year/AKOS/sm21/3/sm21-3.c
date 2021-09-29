#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

void * ptrthread_sum(void *ptr) {
    int num;
    long long * sum =(long long *)ptr;
    *sum = 0;
    while (scanf("%d", &num) == 1) {
        *sum += (long long)num; // на всякий
        sched_yield();
    }

    return NULL;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    int n = strtol(argv[1], NULL, 10); //atoi(argv[1]);

    pthread_t sink[n]; //(pthread_t *) calloc(n, sizeof(*sink));
    long long par_sum[n];

    pthread_attr_t atr;
    pthread_attr_init(&atr);
    pthread_attr_setstacksize(&atr,  PTHREAD_STACK_MIN);

    for (int i = 0; i < n; ++i)
        pthread_create(&sink[i], &atr, ptrthread_sum, par_sum + i);

    pthread_attr_destroy(&atr);

    long long res = 0;

    for (int i = 0; i < n; ++i) {
        pthread_join(sink[i], NULL);
        res += par_sum[i];
    }

    printf("%lld\n", res);
    fflush(stdout);
    return 0;
}