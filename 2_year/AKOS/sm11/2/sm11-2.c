#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

enum {
    BUFFER_SIZE = 4096
};

void copy_file(int in_fd, int out_fd) {
    char buf[BUFFER_SIZE];
    ssize_t read_cnt;
    ssize_t write_cnt;

    while ((read_cnt = read(in_fd, buf, BUFFER_SIZE)) > 0) {
        write_cnt = write(out_fd, buf, read_cnt);

        while (read_cnt > write_cnt) {
            write_cnt += write(out_fd, buf + write_cnt, read_cnt - write_cnt);
        }
    }
}