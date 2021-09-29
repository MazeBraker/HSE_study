#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>

// по конспекту 12 лекции
// 2020-10-23 2
int main(int argc, char *argv[])
{
    struct tm *timeinfo;
    int i, year = 0, month = 0, day = 0, coupon_time = 0;
    // FILE *f = fopen(argv[1], "r");
    if (scanf("%d-%d-%d %d", &year, &month, &day, &coupon_time) != 4) {
        //fprintf(stderr, "problem\n");
        exit(1);
    }

    for (i = 1; i <= coupon_time * 2; ++i) {
        time_t rawtime = 0;
        timeinfo = localtime(&rawtime);  // timeinfo = localtime(&rawtime);
        timeinfo->tm_year = year - 1900; // корректируем год
        timeinfo->tm_mon = month - 1; // корректируем значение месяца
        timeinfo->tm_mday = day;
        timeinfo->tm_isdst = -1;
//      timeinfo->tm_hour = 12; // сами выставляем удобное значение, так как часы не учитываются
//      timeinfo->tm_min = 0;
//      timeinfo->tm_sec= 0;
        // printf("%d", tm_);
        // обработка купонов engeneering
        timeinfo->tm_year += i / 2;
        timeinfo->tm_mon += 6 * (i % 2);

        mktime(timeinfo);
        // воскресенье
        if (timeinfo->tm_wday != 0) {
            if (timeinfo->tm_wday == 6) {  // суббота
                timeinfo->tm_mday += 2;
            }
        } else {
            timeinfo->tm_mday += 1;
        }
        mktime(timeinfo);  // определить день недели
        // выводим в формате год 4 цифры итд
        printf("%04d-%02d-%02d\n", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);
    }
    return 0;
}