#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>
#include <limits.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    DIR *dir = opendir(argv[1]);

    if (dir != NULL) {
        struct dirent *entry;
        struct stat buf;
        unsigned long long sum = 0;
        char path[PATH_MAX + 1];
        while ((entry = readdir(dir))) {
            snprintf(path, sizeof(path), "%s/%s", argv[1], entry->d_name);
            if (stat(path, &buf) >= 0) {
                if (S_ISREG(buf.st_mode)) {
                    if (getuid() == buf.st_uid && isupper(entry->d_name[0])) {
                        sum += buf.st_size;
                    }
                }
            }
        }

        printf("%llu\n", sum);
        closedir(dir);
    } else {
        printf("0\n");
        return 0;
    }
}
