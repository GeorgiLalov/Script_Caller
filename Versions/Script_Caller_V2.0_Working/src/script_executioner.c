#include "script_executioner.h"

//! The folder where are the scripts.
#define SCRIPTS_FOLDER        "scripts/"

//! The key word for calling python scripts from the console.
#define PYTHON_COMMAND        "python "

//! TODO: Calculate it.
#define COMMAND_MAX_LENGTH    120

//! Array with thread ID's, they are assigned to scripts
//!  by the index of the scripts.
static pthread_t fs_pthreads[MAX_COUNT_OF_SCRIPTS];

void* fs_phreadStartPoint(void *fp_argv);

/**
 * @brief Start point of a new thread.
 *        Every script is called by different thread, because system() function
 *        is waiting the script to end.
 * @param fp_argv    The script name.
 * @return NULL
 */
void* fs_phreadStartPoint(void* fp_argv)
{
    int  systemRetValue                    = 0;
    char *pScriptName                      = (char*) fp_argv;
    char commandBuffer[COMMAND_MAX_LENGTH] = { '\0' };

    //! On argument error.
    if (pScriptName == NULL)
    {
        LOG_WRITE(eLogLevel_Error, "%s", "pScriptName is NULL");
    }
    else
    {
        //! Create the full command that is going to be printed on the console.
        //! Should be something like: "python scripts/backup_monitor.py"
        strcat(commandBuffer, PYTHON_COMMAND);
        strcat(commandBuffer, SCRIPTS_FOLDER);
        strcat(commandBuffer, pScriptName);

        LOG_WRITE(eLogLevel_Info, "Executing script: %s", commandBuffer);

        //! Execute the command on the console.
        systemRetValue = system(commandBuffer);

        LOG_WRITE(eLogLevel_Info, "Script %s return %d",
                  commandBuffer, systemRetValue);
    }

    return NULL;
}

/**
 * @brief Creating a new thread for a script and execute it.
 * @param fp_pScriptName    The name of the script.
 * @param fp_scriptIndex    The index of the script.
 */
void Execute_Script(const char *fp_pScriptName,
                    const int  fp_scriptIndex)
{
    //! If script name is null.
    if (fp_pScriptName == NULL)
    {
        LOG_WRITE(eLogLevel_Error, "%s", "fp_script_name is NULL");
    }
    //! If index is not in the bounds.
    else if (fp_scriptIndex < 0 ||
             fp_scriptIndex >= MAX_COUNT_OF_SCRIPTS)
    {
        LOG_WRITE(eLogLevel_Error, 
                  "Receive invalid script index, fp_script_index %d",
                  fp_scriptIndex);
    }
    else
    {
        //! Create the new thread.
        pthread_create(&(fs_pthreads[fp_scriptIndex]), NULL,
                       fs_phreadStartPoint, (void *) fp_pScriptName);
    }
}
