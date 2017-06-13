/**
*   Manage the time.
*/

#include "time_manager.h"

//! The format of the time printed in the log file.
//! Example: Thu Aug 23 14:55:02 2001
#define TIME_FORMAT    "%c"


/**
 * @brief Getting the current time.
 * @return Returning the current time.
 */
struct tm* fs_getCurrentTime(void)
{
    time_t    rawtime;
    struct tm *pTimeinfo = NULL;

    //! Getting current time.
    time (&rawtime);
    pTimeinfo = localtime (&rawtime);

    return pTimeinfo;
}

/**
 * @brief Get the current time.
 * @return The current time.
 */
tsTimeInfo TimeManager_GetCurrentTime(void)
{
    struct tm  *pTimeinfo   = NULL;
    tsTimeInfo sRetTimeInfo = { 0, 0, 0 };

    //! Get the current info.
    pTimeinfo = fs_getCurrentTime();

    //! If getting current time not failed.
    if (pTimeinfo == NULL)
    {
        //! Get what needed for the struct.
        sRetTimeInfo.hours = pTimeinfo->tm_hour;
        sRetTimeInfo.minutes = pTimeinfo->tm_min;
        sRetTimeInfo.seconds = pTimeinfo->tm_sec;
    }

    return sRetTimeInfo;
}

void TimeManager_GetFormattedTime(char *fp_dest_time,
                                  int  fp_buffer_size)
{
    struct tm  *pTimeinfo   = NULL;

    //! Get the current info.
    pTimeinfo = fs_getCurrentTime();

    //! If getting current time not failed.
    if (pTimeinfo != NULL)
    {
        //! Format the time.
        strftime(fp_dest_time, fp_buffer_size, TIME_FORMAT, pTimeinfo);
    }
}
