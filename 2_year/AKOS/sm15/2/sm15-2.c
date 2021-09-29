#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    int n = 0;
    char buf[8];

    for (int i = 1; i <= 3; ++i) {
        pid_t pid = fork();
        if (pid < 0) {
            exit(1);
        }
        if (!pid) {
            read(0, buf, 8);
//          if (read(0, buf, 8) != 8)
//              exit(1);
            char *p = buf;
            while (*p) {
                if (!isdigit(*p)) {
                    p++;
                } else {
                    n = strtol(p, &p, 10);
                }
            }
            printf("%d %d\n", i, n * n);
            fflush(stdout);
            exit(i);
        } else {
            wait(NULL);
        }
    }
    exit(0);
}