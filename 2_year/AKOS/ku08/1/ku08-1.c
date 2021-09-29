#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>

#include <unistd.h>

volatile int cnt = 0, flag1 = 0, flag2 = 0;

void handler(int signal) {
    if (signal == SIGUSR1) {
        flag1 = 1;
        cnt += 2;
    }
    if (signal == SIGUSR2) {
        flag2 = 1;
        cnt -= 3;
    }if (flag1){
        printf("%d %d\n", signal, cnt-=2);
        cnt+=2;
        flag1 = 0;
    }if (flag2){
        printf("%d %d\n", signal, cnt+=3);
        cnt -= 3;
        flag2 = 0;
    }

    // printf("%d %d\n", signal, cnt);
    fflush(stdout);
    if (cnt < 0) {
        exit(0);
    }
}


int main() {
    struct sigaction ss = {
            .sa_flags = SA_RESTART,
            .sa_handler = handler
    };
    // 18 лек
    sigemptyset(&ss.sa_mask);
    sigaction(SIGUSR1, &ss, NULL);
    sigaction(SIGUSR2, &ss, NULL);

    printf("%d\n", getpid());
    fflush(stdout);
    while (1) {
        pause();
    }
    return 0;
}