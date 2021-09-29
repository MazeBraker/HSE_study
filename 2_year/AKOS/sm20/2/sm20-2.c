#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

volatile unsigned int last = 0, count = 0;

// по условию
void handler(int sn) {
    if (last) {
        printf("%u\n", last);
        fflush(stdout);
    }
    if (++count == 8) {
        exit(0);
    }
}

// классический алгоритм до корня
int prime(unsigned int n) {
    if (n < 2) {
        return 0;
    }

    for (unsigned i = 2; i * i <= n; ++i) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

int main() {
    unsigned int low, high;

    scanf("%u %u", &low, &high);

    struct sigaction sa = {
            .sa_handler = handler,
            .sa_flags = SA_RESTART
    };

    sigemptyset(&sa.sa_mask);
    sigaction(SIGVTALRM, &sa, NULL);

    struct itimerval it = {};

    it.it_value.tv_sec = 0;
    it.it_interval.tv_sec = 0;

    it.it_value.tv_usec = 100000;
    it.it_interval.tv_usec = 100000;

    setitimer(ITIMER_VIRTUAL, &it, NULL);

    for (unsigned int i = low; i < high; ++i){
        if (prime(i)) {
            last = i;
        } else {
            last = last;
        }
    }

    if (count != 8) {
        printf("-1\n");
        fflush(stdout);
    }
    return 0;
}