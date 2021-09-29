#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    FILE * input = fopen(argv[1], "r");

    time_t go = 0;

    int y, mo, d, h, m, s;

    struct tm* time_now;
    time_t rawtime;
    time(&rawtime);

    while (fscanf(input, " %d/%d/%d %d:%d:%d ", &y, &mo, &d, &h, &m, &s) != EOF) {
        time_now = localtime(&rawtime);
        time_now->tm_mon = mo - 1;
        time_now->tm_year = y - 1900;
        time_now->tm_isdst = -1;
        time_now->tm_sec = s;
        time_now->tm_min = m;
        time_now->tm_hour = h;
        time_now->tm_mday = d;
        time_t end = mktime(time_now);
        if (go != 0)
            printf("%ld\n", end - go);
        go = end;
    }

    fclose(input);
}