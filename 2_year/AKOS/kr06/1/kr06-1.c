//partial 50
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc <= 1) return 0;
    int fd = open(argv[1], O_RDONLY);
    struct stat fileinfo;
    if (fd == -1 || fstat(fd, &fileinfo) == -1 || fileinfo.st_size == 0) {
        exit(0);
    }

    long long maxx = 0;
    size_t size = fileinfo.st_size, left = 0, right = size + 1;
    while (right - left > 1) {
        size_t m = (right + left) / 2;
        void *map = mmap(0, m, PROT_READ, MAP_PRIVATE, fd, 0);
        if (map != MAP_FAILED) {
            left = m;
        } else {
            right = m;
        }
    }
    size_t cur = 0;
    while (cur < size) {
        if (size - cur >= left) {}
        else {
            left = size - cur;
        }
        void *map = mmap(0, left, PROT_READ, MAP_PRIVATE, fd, cur);
        cur += left;
        char *data = map;
        int flag = 0;
        while (flag < left) {
            int res = 0, more = 1, shift = 0, val = 0;
            while (more) {
                val = (*data) & 0b1111111;
                res = res | (val << shift);
                shift += 7;
                ++flag;
                more = ((*data++) & 10000000) >> 7;
            }
            if (res % 3 == 0) {
                if (res > maxx) {
                    maxx = res;
                }
            }
        }
    }
    if (maxx == 0){
        return 0;
    }
    printf("%lld\n", maxx);
    close(fd);
    return 0;
}