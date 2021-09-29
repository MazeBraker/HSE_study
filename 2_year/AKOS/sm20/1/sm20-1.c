#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/eventfd.h>
#include <sys/timerfd.h>
#include <sys/signalfd.h>

// разобранно на семинаре 199
int main() {
    long long secs;
    int nansecs;
    if (scanf("%lld %d", &secs, &nansecs) != 2) {
        fprintf(stderr, "error in reading values\n");
        exit(1);
    }
    if (0 >= nansecs || nansecs >= 1000000000) {
        fprintf(stderr, "error in nanosecond value %d\n", nansecs);
        exit(1);
    }
    if ((time_t) secs != secs) {
        fprintf(stderr, "error in second value %lld\n", secs);
        exit(1);
    }

    sigset_t s1;
    sigemptyset(&s1);
    sigaddset(&s1, SIGALRM);
    sigprocmask(SIG_BLOCK, &s1, NULL);
    int sfd = signalfd(-1, &s1, 0);

    struct timeval now;
    gettimeofday(&now, NULL);

    secs *= 1000ll;
    secs += nansecs / 1000000;
    // стандартное преобразование
    long long now_ms = now.tv_sec * 1000ll + now.tv_usec / 1000;
    // по условию
    if (secs <= now_ms) {
        return 0;
    }
    secs -= now_ms;

    struct itimerval itimer = {};
    itimer.it_value.tv_sec = secs / 1000;
    itimer.it_value.tv_usec = (secs % 1000) * 1000ll;
    setitimer(ITIMER_REAL, &itimer, NULL);

    struct signalfd_siginfo info;
    // костыль для этой задачи
    if (read(sfd, &info, sizeof(info)) != sizeof(info)) {
        fprintf(stderr, "error in reading\n");
        exit(1);
    }
    return 0;
}