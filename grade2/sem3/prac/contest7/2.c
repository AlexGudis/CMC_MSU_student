#include <stdio.h>
#include <time.h>
#include <errno.h>

enum
{
    START_YEAR = 1900,
    THURSDAY_WDAY = 4,
    SECOND_THURSDAY = 2,
    FORTH_THURSDAY = 4,
    THREE_DIV = 3
};

int
main(void)
{
    int input_year = 0;
    int check_thursday = 0;
    int m_before = 0;
    int res = 0;
    if (scanf("%d", &input_year) != 1) {
        fprintf(stderr, "Error in data reading\n");
        return 1;
    }
    struct tm ttime;
    ttime.tm_sec = 0;
    ttime.tm_min = 0;
    ttime.tm_hour = 0;
    ttime.tm_mday = 1;
    ttime.tm_mon = 0;
    ttime.tm_year = input_year - START_YEAR;
    ttime.tm_isdst = -1;

    errno = 0;
    res = timegm(&ttime);
    if (res == -1 && errno) {
        fprintf(stderr, "Error, cannot convert data to time_t\n");
        return 1;
    }

    while (ttime.tm_year + START_YEAR != input_year + 1) {
        if (ttime.tm_wday == THURSDAY_WDAY) {
            check_thursday++;
            if ((check_thursday == SECOND_THURSDAY || check_thursday == FORTH_THURSDAY) &&
                ttime.tm_mday % THREE_DIV != 0) {
                printf("%d %d\n", ttime.tm_mon + 1, ttime.tm_mday);
            }
        }

        m_before = ttime.tm_mon;
        ttime.tm_mday++;
        errno = 0;
        res = timegm(&ttime);
        if (res == -1 && errno) {
            fprintf(stderr, "Error, cannot convert data to time_t\n");
            return 1;
        }

        if (m_before != ttime.tm_mon) {
            check_thursday = 0;
        }
    }
    return 0;
}
