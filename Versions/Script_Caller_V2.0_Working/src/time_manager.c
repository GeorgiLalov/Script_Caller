/**
*   Manage the time.
*/

#include "time_manager.h"


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
    pTimeinfo = localtime(&rawtime);

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
    if (pTimeinfo != NULL)
    {
        //! Get what needed for the struct.
        sRetTimeInfo.hour   = pTimeinfo->tm_hour;
        sRetTimeInfo.minute = pTimeinfo->tm_min;
        sRetTimeInfo.second = pTimeinfo->tm_sec;
    }

    return sRetTimeInfo;
}

/**
 * @brief Get time in specific format.
 * @param fp_pDestinationTime    The string where formatted time
 *                               will be saved.
 * @param fp_bufferSize          The size of destination time.
 * @param fp_pTimeFormat         The requested format of the time.
 */
void TimeManager_GetFormattedTime(char       *fp_pDestinationTime,
                                  const int  fp_bufferSize,
                                  const char *fp_pTimeFormat)
{
    struct tm *pTimeinfo = NULL;

    //! Get the current info.
    pTimeinfo = fs_getCurrentTime();

    //! If getting current time not failed.
    if (pTimeinfo != NULL)
    {
        //! Format the time.
        strftime(fp_pDestinationTime, fp_bufferSize,
                 fp_pTimeFormat, pTimeinfo);
    }
}
