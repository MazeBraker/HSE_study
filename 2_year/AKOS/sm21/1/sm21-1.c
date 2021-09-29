#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t threads[10];

void* ptrthread10(void* ptr) {
    int sink = (int)(intptr_t)ptr;
    if (sink != 0) {
        pthread_join(threads[sink - 1], NULL);
    }
    printf("%d\n", sink);
    fflush(stdout);
    return NULL;
}


int main(int argc, const char *argv[]) {
    for (int i = 0; i != 10; ++i) {
        pthread_create(&threads[i], NULL, ptrthread10, (void *)(intptr_t) i);
    }
    pthread_join(threads[9], NULL);
    return 0;
}