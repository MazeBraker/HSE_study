#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int check_proc(const char *cmd) {
    int stat, pid;
    if ((pid = fork()) != 0) {
        if (pid < 0) {
            _exit(1);
        }
    } else {
        execlp(cmd, cmd, NULL);
        _exit(1);
    }
    waitpid(pid, &stat, 0);
//    wait(&stat);
//    if(WIFEXITED(stat) && (WEXITSTATUS(stat) == 0)) {
//        return 0;
//    } else {
//        return 1;
//    }
    return WEXITSTATUS(stat) == 0 && WIFEXITED(stat);
}

int main(int argc, char **argv) {
    if (argc != 4) {
        _exit(1);
    }
    if (check_proc(argv[1]) || check_proc(argv[2])) {
        return check_proc(argv[3]) == 0;
    } else {
        _exit(1);
    }
}