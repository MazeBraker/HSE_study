#include <fcntl.h>
#include <inttypes.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

volatile sig_atomic_t exit_f = 0, flag1 = 0, count2 = 0;
// void handler(int signal_num)
void term(int s) {
    exit_f = 1;
}

void usr1(int s) {
    flag1 = 1;
}

void usr2(int s) {
    ++count2;
}


int main() {
    signal(SIGTERM, term);
    signal(SIGUSR1, usr1);
    signal(SIGUSR2, usr2);
    sigset_t block, unblock;
    sigemptyset(&block);
    sigemptyset(&unblock);
    sigaddset(&block, SIGTERM);
    sigaddset(&block, SIGUSR1);
    sigaddset(&block, SIGUSR2);
    sigprocmask(SIG_BLOCK, &block, NULL);
    int cnt = 0;
    printf("%d\n", getpid());
    fflush(stdout);
    while (true) {
        if (exit_f || flag1) {}
        else {
            sigsuspend(&unblock);
        }
        if (exit_f) {
            exit(0);
        }
        if (flag1) {
            printf("%d %d\n", cnt++, count2);
            fflush(stdout); //сбрасывать буфер
            flag1 = 0;
        }
    }
}
