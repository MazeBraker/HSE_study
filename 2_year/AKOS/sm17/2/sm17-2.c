#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
//семинар 199
int main(int argc, char** argv) {
    int fd[2];
    if (pipe(fd) == -1) {
       exit(1);
    } // fd[0] чтение, fd[1] запись
    //printf("%d %d\n", fd[0], fd[1]);

    pid_t  parent = fork();
    if (parent < 0) {
        exit(1);
    } 

    if (parent) {
        // parent
        close(fd[0]);
        int32_t val;
        while(scanf("%d", &val) == 1) {
            write(fd[1], &val, sizeof(val)); // sizeof(val)=4
        }
        close(fd[1]);

        while(wait(NULL) != -1) {}
        exit(0);

    }
    // child
    close(fd[1]);

    pid_t grandparent = fork();
    if (grandparent < 0) {
        exit(1);
    } 

    if (!grandparent) {
        // grandson
        int32_t val;
        int64_t sum = 0;
        while(read(fd[0], &val, sizeof(val)) == sizeof(val)) {
            sum += val;
        }
        printf("%lld", sum);
        fflush(stdout);
        close(fd[0]);
        exit(0);
    } else {
        // child
        close(fd[0]);
        while(wait(NULL) != -1) {}
        exit(0);
    }

    return 0;   
}