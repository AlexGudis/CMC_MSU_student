#include <stdio.h>
#include <time.h>
#include <errno.h>

enum
{
    DAY_SEC = 86400
};

int
main(void)
{
    int year;
    scanf("%d", &year);
    struct tm info;
    info.tm_sec = 0;
    info.tm_min = 0;
    info.tm_hour = 0;
    info.tm_mday = 1;
    info.tm_mon = 0;
    info.tm_year = year - 1900;
    info.tm_isdst = -1;
    int ans = 0;
    time_t time;
    errno = 0;
    time = timegm(&info); // time in sec of 01.01.year
    if (time == -1 && errno) {
        fprintf(stderr, "Error in timegm\n");
        return 1;
    }
    while (info.tm_year == year - 1900) {
        //printf("data dd:mm:yyyy %02d:%02d:%04d\n", info.tm_mday, info.tm_mon + 1, info.tm_year + 1900);
        if (info.tm_wday == 0 || info.tm_wday == 6 ||
            (info.tm_wday != 0 && info.tm_wday != 6 &&
             (info.tm_yday + 1 == 1 || info.tm_yday + 1 == 2 || info.tm_yday + 1 == 4 || info.tm_yday + 1 == 8 ||
              info.tm_yday + 1 == 16 || info.tm_yday + 1 == 32 || info.tm_yday + 1 == 64 || info.tm_yday + 1 == 128 ||
              info.tm_yday + 1 == 256))) {
            ans++;
        }
        info.tm_mday++;
        timegm(&info);
        //time += DAY_SEC;
        //gmtime_r(&time, &info);
    }
    printf("%d\n", ans);
}
