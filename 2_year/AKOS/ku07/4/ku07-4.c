#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>


int main(int argc, char* argv[]) {
    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    int rows = strtol(argv[2], NULL, 10);
    int cols = strtol(argv[3], NULL, 10);
    // размер матрицы
    size_t size = rows * cols * sizeof(double);
    // t
    if (ftruncate(fd, size) != -1) {

        void *add = mmap(NULL, size, PROT_WRITE, MAP_SHARED, fd, 0);
        if (add == MAP_FAILED) {
            // failed to mmap
            exit(1);
        }
        double (*mat)[cols] = add;
        double a, b;
        for (int i = 0; i != rows; ++i) {
            for (int j = 0; j != cols; ++j) {
                a = sin((double) i);
                b = cos((double) j / 2);
                mat[i][j] = 2 * a + 4 * b;
            }
        }
        //отражает файлы или устройства в памяти
        munmap(add, size);
        close(fd);
        return 0;
    } else {
        // не получилось truncate файл то есть открыть или отобразить
        exit(1);
    }
}