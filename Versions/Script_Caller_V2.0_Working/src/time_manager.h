#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

#include <time.h>

//! Info for the current time.
typedef struct
{
    int second;
    int minute;
    int hour;
} tsTimeInfo;

tsTimeInfo TimeManager_GetCurrentTime(void);
void       TimeManager_GetFormattedTime(char       *fp_pDestinationTime,
                                        const int  fp_bufferSize,
                                        const char *fp_pTimeFormat);

#endif // TIME_MANAGER_H
