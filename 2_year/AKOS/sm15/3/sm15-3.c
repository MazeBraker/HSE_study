#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int N;
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) {
        int pid = fork();
        if (pid < 0) {
            exit(1);
        } else if (!pid) {
            printf("%d", i);
            if (i != N) {
                printf(" ");
            } else {
                printf("\n");
            }
            exit(0);
        }
        wait(NULL);
    }
    // for (int i = 1; i <= N; ++i) {
    //     wait(NULL);
    // }
    wait(NULL);
    exit(0);
}