#include <signal.h>
#include <stdio.h>
#include <unistd.h>
// разобрано на семинаре 199
enum { MAXNUM = 5 };
volatile sig_atomic_t cnt = 0;
void signal_handler(int signal)
{
    if (cnt < MAXNUM - 1) {
        printf("%d\n", cnt);
        fflush(stdout);
    }
    cnt++;
}


int main() {
    sigset_t new, old;
    sigemptyset(&new);
    sigaddset(&new, SIGINT);
    sigprocmask(SIG_BLOCK, &new, &old);

    printf("%d\n", getpid());
    fflush(stdout);

    struct sigaction sa, old_sa;
    sa.sa_handler = signal_handler;
    sa.sa_flags = SA_RESTART;

    sigaction(SIGINT, &sa, &old_sa);

    while(1) {
        sigsuspend(&old);
        if (cnt >= MAXNUM) {
            sigaction(SIGINT, &old_sa, NULL);
            break;
        }
    }
    sigprocmask(SIG_UNBLOCK, &new, &old);
    return 0;
}