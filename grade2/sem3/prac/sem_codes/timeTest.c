#include <time.h>
#include <stdio.h>

enum
{
    NUM_OF_PARAMETERS = 6
};

int
main()
{
    int secs, mins, hours, days, months, years;
    
    while(scanf("%d%d%d%d%d%d", &secs, &mins, &hours, &days, &months, &years) == NUM_OF_PARAMETERS)
    {
        struct tm data;

        data.tm_sec = secs;
        data.tm_min = mins;
        data.tm_hour = hours;
        data.tm_mday = days;
        data.tm_mon = months - 1;
        data.tm_year = years - 1900;
        data.tm_isdst = -1;

        time_t resData = mktime(&data);

        printf("%ld: %d-%d-%d-%d-%d-%d\n",
               resData, data.tm_sec, data.tm_min, data.tm_hour,
               data.tm_mday, data.tm_mon + 1, data.tm_year + 1900);
            










    }

}
