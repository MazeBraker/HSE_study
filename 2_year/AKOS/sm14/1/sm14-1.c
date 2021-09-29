#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main(int argc, char ** argv) {
    double ans = 0;

    if (argc != 2) {
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);

    if (fd < 0)
        return 1;

    off_t size = lseek(fd, 0, SEEK_END);

    if (size == -1) {
        close(fd);
        return 1;
    }

    double * mapp = (double *) mmap(NULL , size, PROT_READ, MAP_PRIVATE, fd, 0);
    size_t cnt = size / sizeof(double);

    for (size_t i = 0; i < cnt; ++i){
        ans += mapp[i];
    }
    printf("%a\n", (double) ans / cnt);
    munmap(mapp, size);
    close(fd);
    return 0;
}