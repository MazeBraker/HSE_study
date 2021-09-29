#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

void matrix(int32_t *data, int rows, int cols) {
    int32_t i = 1;

    int m_col = 0, m_row = 0, M_col = cols, M_row = rows;

    while (M_col > m_col && M_row > m_row) {
        for (int h = m_col; h < M_col; ++h) {
            long long k = m_row * cols + h;
            data[k] = i++;
        }
        if (++m_row < M_row) {
            for (int v = m_row; v < M_row; ++v) {
                long long k1 = v * cols + (M_col - 1);
                data[k1] = i++;
            }
            
            if (--M_col > m_col) {
                for (int h = M_col; h > m_col; --h)
                    data[(M_row - 1) * cols + h - 1] = i++;

                if (--M_row > m_row) {
                    for (int v = M_row - 1; v > m_row - 1; --v)
                        data[v * cols + m_col] = i++;
                    ++m_col;
                } else break;
            } else break;
        } else {
            break;
        }
    }
}

int main(int argc, char **argv) {
    if (argc < 4) {
        fprintf(stderr, "not argv\n");
        return 1;
    }
    //int rows = strtoul(argv[2], NULL, 10);
    //int rows = strtol(argv[2], NULL, 10);
    int rows = atoi(argv[2]);
    int cols = atoi(argv[3]);

    if (sscanf(argv[2], "%d", &rows) != 1) {
        fprintf(stderr, "error rows\n");
        return 1;
    }
    if (sscanf(argv[3], "%d", &cols) != 1) {
        fprintf(stderr, "error columns\n");
        return 1;
    }

    int64_t size = rows * cols * sizeof(int32_t);

    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, (mode_t) 0600);
    //int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC);
    if (fd < 0) {
        return 1;
    }
    struct stat buf;
    if (fstat(fd, &buf) == -1) {
        return 1;
    }
    if (fd == -1 || lseek(fd, (long long) size * sizeof(int) - 1, SEEK_SET) == -1 || write(fd, "", 1) == -1) {
        exit(0);
    }
    ftruncate(fd, size);

    int32_t *matrixx = mmap(NULL, size, PROT_WRITE, MAP_SHARED, fd, 0);
    //void *map = mmap(0, filesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    matrix(matrixx, rows, cols);

    munmap(matrixx, size);

    close(fd);
    return 0;
}