#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char * argv[]) {
    long long cnt = 0;
    struct stat line;
//     struct stat {
//     mode_t st_mode; /* тип файла и режим (права доступа) */
//     ino_t st_ino; /* номер индексного узла */
//     dev_t st_dev; /* номер устройства (файловой системы) */
//     dev_t st_rdev; /* номер устройства для специальных файлов */
//     nlink_t st_nlink; /* количество ссылок */
//     uid_t st_uid; /* идентификатор пользователя владельца */
//     gid_t st_gid; идентификатор группы владельца
//     off_t st_size; /* размер в байтах, для обычных файлов */
//     time_t st_atime; /* время последнего обращения к файлу */
//     time_t st_mtime; /* время последнего изменения файла */
//     time_t st_ctime; /* время последнего изменения флагов состояния файла */
//     blksize_t st_blksize; /* оптимальный размер блока ввода вывода */
//     blkcnt_t st_blocks; /* количество занятых дисковых блоков */
// };
    for (int i = 1; i != argc; ++i) {

        int num = lstat(argv[i], &line);
        //файл существует
        if (num < 0)
            continue;
        //S_ISREG(st_mode) Обычный файл S_ISLNK(st_mode) Символическая ссылка
        if (S_ISREG(line.st_mode) && !S_ISLNK(line.st_mode)){
            if (line.st_nlink == 1) {
                //единственный файл
                cnt += line.st_size;
                }
            }
    }

    printf("%llu\n", cnt);
    return 0;
}
