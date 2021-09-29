//1 test
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>


pthread_t ids[5];
pthread_t ids2[5];

void *fuck1(void *arg)
{
    pause();
    return NULL;
}
volatile int fuck = 0;

void *fuck2(void *arg)
{
    int serial = (int) (intptr_t) arg;
    while (!fuck)
        continue;

    if (serial == 4) {
        pthread_join(ids2[2], NULL);
    } else if (serial == 2) {
        pthread_join(ids2[3], NULL);
    } else if (serial == 3) {
        pthread_join(ids2[1], NULL);
    } else if (serial == 1) {
        pthread_join(ids2[4], NULL);
    }

    printf("%d\n", serial);
    fflush(stdout);

    return NULL;
}

int main()
{
    for (int i = 1; i <= 4; ++i) {
        pthread_create(&ids2[i], NULL, fuck1, NULL);
    }
    for (int i = 1; i <= 4; ++i) {
        pthread_create(&ids[i], NULL, fuck2, (void *) (intptr_t) i);
    }
    for (int i = 1; i <= 4; ++i) {
        pthread_cancel(ids2[i]);
    }
    fuck = 1;
    pthread_join(ids[1], NULL);
    return 0;
}