#include <stdio.h>
#include <time.h>
#include <errno.h>

enum
{
    START_YEAR = 1900,
    INFO_MIN = 14,
    INFO_HOUR = 11,
    INFO_MDAY = 26,
    INFO_MON = 5,
    INFO_YEAR = 2021,
    FULLMOON_MIN = 44,
    FULLMOON_HOUR = 12,
    FULLMOON_MDAY = 29,
    DAY_CHECK = 256,
    MONDAY_COUNTER = 4
};

int
change_data(struct tm *ttime, int up)
{
    int pom, res;
    if (up) {
        pom = 1;
    } else {
        pom = -1;
    }
    ttime->tm_min += pom * FULLMOON_MIN;
    ttime->tm_hour += pom * FULLMOON_HOUR;
    ttime->tm_mday += pom * FULLMOON_MDAY;
    errno = 0;
    res = timegm(ttime);
    if (res == -1 && errno) {
        fprintf(stderr, "Error, cannot convert data to time_t\n");
        return 1;
    }
    return 0;
}

int
main(void)
{
    int input_year = 0;
    int monday_cnt = 0;
    time_t res = 0;
    if (scanf("%d", &input_year) != 1) {
        fprintf(stderr, "Error in data reading\n");
        return 1;
    }
    struct tm ttime;
    ttime.tm_sec = 0;
    ttime.tm_min = INFO_MIN;
    ttime.tm_hour = INFO_HOUR;
    ttime.tm_mday = INFO_MDAY;
    ttime.tm_mon = INFO_MON - 1;
    ttime.tm_year = INFO_YEAR - START_YEAR;
    ttime.tm_isdst = -1;
    errno = 0;
    res = timegm(&ttime);
    if (res == -1 && errno) {
        fprintf(stderr, "Error, cannot convert data to time_t\n");
        return 1;
    }
    while (ttime.tm_year + START_YEAR != START_YEAR) {
        res = change_data(&ttime, 0);
        if (res) {
            fprintf(stderr, "Error while going to the past\n");
            return 1;
        }
    }

    while (ttime.tm_year + START_YEAR != input_year) {
        res = change_data(&ttime, 1);
        if (res) {
            fprintf(stderr, "Error while going from past to our year\n");
            return 1;
        }
    }

    while (ttime.tm_yday < DAY_CHECK) {
        res = change_data(&ttime, 1);
        if (res) {
            fprintf(stderr, "Error while going by moon to day 256\n");
            return 1;
        }
    }

    while (monday_cnt != MONDAY_COUNTER) {
        ttime.tm_mday++;
        errno = 0;
        res = timegm(&ttime);
        if (res == -1 && errno) {
            fprintf(stderr, "Error, cannot convert data to time_t\n");
            return 1;
        }
        if (ttime.tm_wday == 1) {
            monday_cnt++;
        }
    }
    printf("%04d-%02d-%02d\n", ttime.tm_year + START_YEAR, ttime.tm_mon + 1, ttime.tm_mday);
    return 0;
}
