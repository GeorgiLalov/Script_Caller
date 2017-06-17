/**
* @about Calling scripts at a specific time.
*
*/
#include <stdio.h>

//#include "log_write.h"
//#include "scripts_file_reader.h"
//#include "scripts_list_management.h"
#include "monitor.h"

/**
 * @brief Main Entry Point
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    //LOG_WRITE(eLogLevel_Info, "%s %s\n", "Null parameter reseive", "again");

    /*int scriptsCount = 0;
    int scriptIndex = 0;
    tsScriptData *pScriptData = NULL;

    while (1)
    {
        ScriptsList_Init();

        scriptsCount = ScriptsList_GetCount();

        //! Through every available script.
        for(scriptIndex = 0; scriptIndex < scriptsCount; scriptIndex++)
        {
            pScriptData = ScriptsList_GetByIndex(scriptIndex);

            if (pScriptData != NULL)
            {
                printf("hour %d min %d sec %d name %s\n",
                pScriptData->hour, pScriptData->minute,
                pScriptData->second, pScriptData->script_name);
            }
        }

        ScriptsList_Destroy();
    }*/

    Monitor_Start();

    //start_monitoring();

    return 0;
}
