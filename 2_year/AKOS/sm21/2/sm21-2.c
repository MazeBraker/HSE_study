#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void* ptrthread_rev(void* ptr) {
    int nsink;
    if (scanf("%d", &nsink) != 1){
        return NULL;
    }

    pthread_t childt;
    pthread_create(&childt, NULL, ptrthread_rev, NULL);
    pthread_join(childt, NULL);
    printf("%d\n", nsink);
    return NULL;
}


int main(int argc, const char *argv[]) {
    pthread_t childt;
    pthread_create(&childt, NULL, ptrthread_rev, NULL);
    pthread_join(childt, NULL);
    return 0;
}