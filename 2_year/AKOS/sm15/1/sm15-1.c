#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t s_pid = fork();
    if (s_pid < 0) {
        exit(1);
    }
    if (!s_pid) {
        pid_t g_pid = fork();
        if (g_pid < 0) {
            exit(1);
        } else {
            if (g_pid == 0) {
                printf("3 ");
                exit(0);
            } else {
                wait(NULL);
                printf("2 ");
                exit(0);
            }
        }
    }
    wait(NULL);
    printf("1\n");
    exit(0);
}