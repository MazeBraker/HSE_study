/* -*- mode: c; c-basic-offset: 4 -*- */

#include <dirent.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

static const char pattern[] = "#!/bin/python3\n";

int main(int argc, char *argv[])
{
    int count = 0;

    DIR *d = opendir(argv[1]);
    if (!d) {
        fprintf(stderr, "cannot open directory '%s'\n", argv[1]);
        exit(1);
    }
    struct dirent *dd;
    while ((dd = readdir(d))) {
        char path[PATH_MAX];
        if (snprintf(path, sizeof(path), "%s/%s", argv[1], dd->d_name) >= sizeof(path)) {
            fprintf(stderr, "path is too long\n");
            continue;
        }

        struct stat stb;
        if (stat(path, &stb) < 0 || access(path, X_OK) < 0) {
            continue;
        }
        if (!S_ISREG(stb.st_mode) || stb.st_uid != 0 || (stb.st_mode & 04000) == 0) {
            continue;
        }
        if (stb.st_size < sizeof(pattern) - 1) {
            continue;
        }
        int fd = open(path, O_RDONLY, 0);
        if (fd < 0) {
            continue;
        }
        char buf[sizeof(pattern) - 1];
        if (read(fd, buf, sizeof(buf)) != sizeof(buf)) {
            close(fd);
            continue;
        }
        close(fd);
        count += (memcmp(pattern, buf, sizeof(buf)) == 0);
    }

    printf("%d\n", count);
}
