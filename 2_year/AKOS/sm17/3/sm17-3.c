#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, const char *argv[]) {
    int fd[2];
    if (pipe(fd) < 0) {
        exit(1);
    }

    int file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0600);

    pid_t cmd1, cmd2, cmd3;
    if ((cmd3 = fork()) == -1) {

        exit(EXIT_FAILURE);
    } else if (cmd3 == 0) {
        // cmd3
        close(STDIN_FILENO);
        dup2(fd[0], STDIN_FILENO);
        close(STDOUT_FILENO);
        dup2(file, STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp(argv[3], argv[3], NULL);
        exit(1);
    }
    close(fd[0]);

    if ((cmd1 = fork()) == -1) {
        /* failed to create a new process */
        exit(1);
    } else if (cmd1 == 0) {
        // cmd1
        close(STDOUT_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        execlp(argv[1], argv[1], NULL);

        exit(1);
    }
    wait(NULL);

    if ((cmd2 = fork()) == -1) {
        exit(1);
    } else if (cmd2 == 0) {
        // cmd2
        close(STDOUT_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        execlp(argv[2], argv[2], NULL);

        exit(1);
    }
    close(fd[1]);

    while (wait(NULL) > 0) {}
    return 0;
}
