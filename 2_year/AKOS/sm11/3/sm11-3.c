#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

//struct FileContent {
//    ssize_t size;
//    char *data;
//};

struct FileContent error(struct FileContent *result) {
    if (result->data != NULL) {
        free(result->data);
    }
    result->data = NULL;
    result->size = -1;

    return *result;
}

struct FileContent read_file(int fd) {
    struct FileContent result;
    result.size = 0;
    result.data = NULL;

    char buf[4096];
    int realsz;
    while ((realsz = read(fd, buf, 4096)) != 0) {
        if (realsz < 0) {
            return error(&result);
        }
        char *tmpmem = realloc(result.data, result.size + realsz);
        if (tmpmem != NULL) {
            result.data = tmpmem;
            memcpy(result.data + result.size, buf, realsz);
            result.size += realsz;
        } else {
            return error(&result);
        }
    }
    char *tmpmem = realloc(result.data, result.size + 1);
    if (tmpmem != NULL) {
        result.data = tmpmem;
        result.data[result.size] = '\0';
        return result;
    } else {
        return error(&result);
    }
}