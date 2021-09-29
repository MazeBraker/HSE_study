//partial 3
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv) {
    struct stat stat1;
    unsigned long long cnt = 0;

    for (int i = 1; i < argc; ++i) {
        int fd = open(argv[i], O_RDONLY);

        if (fd != -1) {
            if (fstat(fd, &stat1) == -1) {
                close(fd);
                printf("-1\n");
                continue;
            }
            if (!stat1.st_size) {
                printf("0\n");
                continue;
            }
            void *mapped = mmap(NULL, stat1.st_size, PROT_READ, MAP_SHARED, fd, 0);
            if (mapped == MAP_FAILED) {
                printf("-1\n");
                close(fd);
                continue;
            }
            char *mapp = (char *) mapped;

            for (long j = 0; j < stat1.st_size; ++j) {
                if (mapp[j] == '\n')
                    ++cnt;
            }
            //buf.st_size / sizeof(char)
            if (mapp[stat1.st_size - 1] != '\n') {
                ++cnt;
            }
            printf("%llu\n", cnt);
            munmap(mapped, stat1.st_size);
            close(fd);
        } else {
            printf("-1\n");
        }
    }
    return 0;
}