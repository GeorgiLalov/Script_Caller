#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <time.h>

//! Info for the current time.
typedef struct
{
    int seconds;
    int minutes;
    int hours;
} tsTimeInfo;

tsTimeInfo TimeManager_GetCurrentTime(void);
void TimeManager_GetFormattedTime(char *fp_dest_time,
                                  int  fp_buffer_size);

#endif // TIME_MANAGER_H
