#include "monitor.h"


void fs_monitorTime(const tsTimeInfo *fp_pTimeInfo);

/**
 * @brief Every one second check if some script needs to be runned and
 *        create new thread for it.
 * @param fp_pTimeInfo    The information about the current time.
 */
void fs_monitorTime(const tsTimeInfo *fp_pTimeInfo)
{
    tsScriptData *pScriptData   = NULL;
    //! Hold the previous second.
    static int   previousSecond = 0;
    int          scriptIndex    = 0;
    int          scriptsCount   = 0;

    //! On null parameter received.
    if (fp_pTimeInfo == NULL)
    {
        LOG_WRITE(eLogLevel_Error, "%s", "fp_pTimeInfo is NULL");
    }
    else
    {
        //! In order to check scripts once every second.
        if (previousSecond != fp_pTimeInfo->second)
        {
            //! TODO: This stay for debug.
            printf("Hour %d, min %d, sec %d\n", fp_pTimeInfo->hour, fp_pTimeInfo->minute, fp_pTimeInfo->second);

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
                    if ((pScriptData->hour   == fp_pTimeInfo->hour) &&
                        (pScriptData->minute == fp_pTimeInfo->minute) &&
                        (pScriptData->second == fp_pTimeInfo->second))
                    {
                        //! Execute the script.
                        Execute_Script(pScriptData->name,
                                       scriptIndex);

                        printf("Create new thread for %s, index %d\n", pScriptData->name, scriptIndex);
                    }
                }
            }

            //! Store current second as previous
            previousSecond = fp_pTimeInfo->second;
        }
    }
}

/**
 * @brief Start monitoring time.
 */
void Monitor_Start(void)
{
    tsTimeInfo sTimeinfo = { 0, 0, 0 };
    int listInitRetValue = 0;

    //! Initialize the list with scripts.
    listInitRetValue = ScriptsList_Init();

    if (listInitRetValue != 0)
    {
        LOG_WRITE(eLogLevel_Issue,
                  "ScriptsList_Init failed, return %d", listInitRetValue);
    }
    else
    {
        //! Infinite loop.
        while (1)
        {
            //! TODO: Think of some logic to check if after 1 second the time is changed.
            //! Maybe Timer Manager?

            //! Getting current time.
            sTimeinfo = TimeManager_GetCurrentTime();

            //! Check for needed call to script.
            fs_monitorTime(&sTimeinfo);
        }
    }

    //! Free the allocated memory.
    ScriptsList_Destroy();
}
