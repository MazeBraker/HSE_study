#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>

int mysys(const char *str)
{
    int new_proc, stat;

    if ((new_proc = fork()) >= 0) {

        if (new_proc == 0) {
            execlp("/bin/sh", "sh", "-c", str, NULL);
            _exit(127);
        }

        waitpid(new_proc, &stat, 0);
        if (WIFSIGNALED(stat)) {
            return WTERMSIG(stat) + 128;
        }

        if (WIFEXITED(stat) && (WEXITSTATUS(stat) >= 0) && (WEXITSTATUS(stat) <= 127)) {
            return WEXITSTATUS(stat);
        }
        return 0;
    } else {
        _exit(-1);
    }
}