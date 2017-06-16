#include "monitor.h"



#include "log_write.h"
#include "time_manager.h"
#include "scripts_file_reader.h"
#include "scripts_list_management.h"
#include "script_executioner.h"

void monitor_time(const tsTimeInfo *fp_time_info);
void start_monitoring(void);

void start_monitoring(void)
{
    tsTimeInfo timeinfo;

    //! Infinite loop.
    while (1)
    {
        //! Getting current time.
        timeinfo = TimeManager_GetCurrentTime();

        //! Check for needed call to script.
        monitor_time(&timeinfo);
    }
}


/**
 * @brief Every one second check if some script needs to be runned and
 *        create new thread for it.
 * @param fp_time_info    The information about the current time.
 */
void monitor_time(const tsTimeInfo *fp_time_info)
{
    tsScriptData* pScriptData = NULL;
    //! Hold the previous second.
    static int prev_sec     = 0;
    int        scriptIndex  = 0;
    int        scriptsCount = 0;

    if (fp_time_info == NULL)
    {
        LOG_WRITE(eLogLevel_Error, "%s", "fp_time_info is NULL");
    }
    else
    {
        //! In order to check scripts once every second.
        if (prev_sec != fp_time_info->seconds)
        {
            //! TODO: This stay for debug.
            printf("Hour %d, min %d, sec %d\n", fp_time_info->hours, fp_time_info->minutes, fp_time_info->seconds);

            scriptsCount = ScriptsList_GetCount();

            //! Through every available script.
            for(scriptIndex = 0; scriptIndex < scriptsCount; scriptIndex++)
            {
                pScriptData = ScriptsList_GetByIndex(scriptIndex);

                if (pScriptData != NULL)
                {
                    //! Check the time of execution.
                    if ((pScriptData->hour   == fp_time_info->hours) &&
                        (pScriptData->minute == fp_time_info->minutes) &&
                        (pScriptData->second == fp_time_info->seconds))
                    {
                        //! Create the new thread where the script will be executed.
                        create_new_thread(pScriptData->script_name,
                                          scriptIndex);
                    }
                }
            }

            //! Store current second as previous
            prev_sec = fp_time_info->seconds;
        }
    }
}
