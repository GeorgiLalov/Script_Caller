#include "script_executioner.h"

//! The folder where are the scripts.
#define SCRIPTS_FOLDER    "scripts/"

//! The key word for calling python scripts from the console.
#define PYTHON_COMMAND    "python "

//! TODO: Calculate them.

#define BUFFER_NAME_MAX_LENGTH    120


static pthread_t fs_pthreads[MAX_COUNT_OF_SCRIPTS];

void* phread_start_point(void *fp_argv);
//! TODO: Change to execute_script and move to .h
void create_new_thread(const char *fp_script_name,
                       int        fp_script_index);
                       
/**
 * @brief Start point of a new thread.
 *        Every script is called by different thread, because system() function
 *        is waiting the script to end.
 * @param fp_argv    The script name.
 * @return NULL
 */
void* phread_start_point(void* fp_argv)
{
    char *script_name = (char*) fp_argv;
    char ex_command_buffer[BUFFER_NAME_MAX_LENGTH] = { '\0' };

    if (script_name == NULL)
    {
        LOG_WRITE(eLogLevel_Error, "%s", "script_name is NULL");
    }
    else
    {
        //! Create the full command that is going to be printed on the console.
        //! Should be something like: "python scripts/backup_monitor.py"
        strcat(ex_command_buffer, PYTHON_COMMAND);
        strcat(ex_command_buffer, SCRIPTS_FOLDER);
        strcat(ex_command_buffer, script_name);

        LOG_WRITE(eLogLevel_Info, "Executing script: %s", ex_command_buffer);

        //! TODO: Check ret value for error.
        system(ex_command_buffer);
    }

    return NULL;
}

/**
 * @brief Creating a new thread for a script.
 * @param fp_script_name    The name of the script.
 * @param fp_script_index   The index of the script.
 */
void create_new_thread(const char *fp_script_name,
                       int        fp_script_index)
{
    if (fp_script_name == NULL)
    {
        LOG_WRITE(eLogLevel_Error, "%s", "fp_script_name is NULL");
    }
    else if (fp_script_index < 0 ||
             fp_script_index >= MAX_COUNT_OF_SCRIPTS)
    {
        LOG_WRITE(eLogLevel_Error, 
                  "Receive invalid script index, fp_script_index %d",
                  fp_script_index);
    }
    else
    {
        //! Create the new thread.
        pthread_create(&(fs_pthreads[fp_script_index]), NULL,
                       phread_start_point, (void *) fp_script_name);
    }
}
/*

*/
