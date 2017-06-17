#include "monitor.h"


void fs_monitor_time(const tsTimeInfo *fp_time_info);

/**
 * @brief Every one second check if some script needs to be runned and
 *        create new thread for it.
 * @param fp_time_info    The information about the current time.
 */
void fs_monitor_time(const tsTimeInfo *fp_time_info)
{
    tsScriptData* pScriptData = NULL;
    //! Hold the previous second.
    static int prev_sec       = 0;
    int        scriptIndex    = 0;
    int        scriptsCount   = 0;

    //! On null parameter received.
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

            //! Get scripts count.
            scriptsCount = ScriptsList_GetCount();

            //! For each script in the list.
            for(scriptIndex = 0; scriptIndex < scriptsCount; scriptIndex++)
            {
                //! Get the script by index fro the list.
                pScriptData = ScriptsList_GetByIndex(scriptIndex);

                if (pScriptData != NULL)
                {
                    //! Check the time of execution.
                    if ((pScriptData->hour   == fp_time_info->hours) &&
                        (pScriptData->minute == fp_time_info->minutes) &&
                        (pScriptData->second == fp_time_info->seconds))
                    {
                        //! Create the new thread where the script will be executed.
                        //create_new_thread(pScriptData->script_name,
                          //                scriptIndex);

                        printf("Create new thread for %s, index %d\n", pScriptData->script_name, scriptIndex);
                    }
                }
            }

            //! Store current second as previous
            prev_sec = fp_time_info->seconds;
        }
    }
}

/**
 * @brief Start monitoring time.
 */
void Monitor_Start(void)
{
    tsTimeInfo timeinfo = { 0, 0, 0 };
    int retVal          = 0;

    //! Initialize the list with scripts.
    retVal = ScriptsList_Init();

    if (retVal != 0)
    {
        LOG_WRITE(eLogLevel_Issue,
                  "ScriptsList_Init failed, return %d", retVal);
    }
    else
    {
        //! Infinite loop.
        while (1)
        {
            //! Getting current time.
            timeinfo = TimeManager_GetCurrentTime();

            //! Check for needed call to script.
            fs_monitor_time(&timeinfo);
        }
    }

    //! Free the allocated memory.
    ScriptsList_Destroy();
}
