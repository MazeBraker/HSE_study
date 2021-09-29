#include <time.h>
#include <stdio.h>
#include <inttypes.h>

int main() {
    int32_t days_from_now;
    time_t fak, now;

    while (scanf("%"SCNd32, &days_from_now) != EOF) {
        time(&now);
        if (__builtin_mul_overflow(days_from_now, 24 * 60 * 60, &fak) ||
            __builtin_add_overflow(now, fak, &now)) {
            printf("OVERFLOW\n");
            continue;
        }

        struct tm *localTime = localtime(&now);
        // {  int tm_sec;         /* seconds,  range 0 to 59          */
        //    int tm_min;         /* minutes, range 0 to 59           */
        //    int tm_hour;        /* hours, range 0 to 23             */
        //    int tm_mday;        /* day of the month, range 1 to 31  */
        //    int tm_mon;         month, range 0 to 11            
        //    int tm_year;        /* The number of years since 1900   */
        //    int tm_wday;        /* day of the week, range 0 to 6    */
        //    int tm_yday;        /* day in the year, range 0 to 365  */
        //    int tm_isdst;       /* daylight saving time             */   
        // }; 

        char buf[30];
        //https://www.tutorialspoint.com/c_standard_library/c_function_strftime.htm
        //https://coderoad.ru/997946/Как-получить-текущее-время-и-дату-в-C
        strftime(buf, 30, "%Y-%m-%d", localTime);

        printf("%s\n", buf);
    }
}