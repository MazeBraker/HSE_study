#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    int cond, N;
    pid_t previous_n = getpid();
    while (scanf("%d", &N) != EOF) {
        pid_t pid = fork();
        if (pid < 0) {
            exit(1);
        } else if (pid != 0) {
            //waitpid(pid, &cond, 0);
            wait(&cond);
            if (!cond) {
                printf("%d\n", N);
                exit(0);
            }
            if (getpid() == previous_n) {
                printf("-1\n");
                exit(0);
            }
            exit(1);
        } else {
            continue;
        }
    }
    exit(0);
}