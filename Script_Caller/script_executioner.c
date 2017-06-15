#include "script_executioner.h"
/*

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "log_write.h"

//! The folder where are the scripts.
#define SCRIPTS_FOLDER    "scripts/"

//! The key word for calling python scripts from the console.
#define PYTHON_COMMAND    "python "

//! TODO: Calculate them.

#define BUFFER_NAME_MAX_LENGTH    120



pthread_t backupMonitor_pthread;


void *phread_start_point(void* fp_argv);
void create_new_thread(const char *fp_script_name,
                       pthread_t  *fp_pthread_id);
void monitor_time(const struct tm *fp_time_info);
void start_monitoring(void);

void start_monitoring(void)
{
    time_t    rawtime;
    struct tm *timeinfo = NULL;
    //struct tm timeinfo = {1, 10, 12, 0, 0, 0, 0, 0, 0, 0, NULL};
    //monitor_time(&timeinfo);

    //! Infinite loop.
    while (1)
    {
        //! Getting current time.
        time (&rawtime);
        timeinfo = localtime (&rawtime);

        //! Check for needed call to script.
        monitor_time(timeinfo);
    }
}

/**
 * @brief Start point of a new thread.
 *        Every script is called by different thread, because system() function
 *        is waiting the script to end.
 * @param fp_argv    The script name.
 * @return NULL
 *
void *phread_start_point(void* fp_argv)
{
    char *script_name = (char*) fp_argv;
    char ex_command_buffer[BUFFER_NAME_MAX_LENGTH] = { '\0' };

    if (script_name == NULL)
    {
        printf("script_name is NULL\n");

        exit(1);
    }
    else
    {
        //! Create the full command that is going to be printed on the console.
        //! Should be something like: "python scripts/backup_monitor.py"
        strcat(ex_command_buffer, PYTHON_COMMAND);
        strcat(ex_command_buffer, SCRIPTS_FOLDER);
        strcat(ex_command_buffer, script_name);

        printf("Executing script: %s\n", ex_command_buffer);

        //! TODO: Check ret value for error.
        system(ex_command_buffer);
    }

    return NULL;
}

/**
 * @brief Creating a new thread for a script.
 * @param fp_script_name    The name of the script.
 * @param fp_pthread_id     The ID of the thread.
 *
void create_new_thread(const char *fp_script_name,
                       pthread_t  *fp_pthread_id)
{
    if (fp_script_name == NULL)
    {
        printf("fp_script_name is NULL\n");

        exit(1);
    }
    else if (fp_pthread_id == NULL)
    {
        printf("fp_pthread_id is NULL\n");

        exit(1);
    }
    else
    {
        //! Create the new thread.
        pthread_create(fp_pthread_id, NULL,
                       phread_start_point, (void *) fp_script_name);
    }
}

/**
 * @brief Every one second check if some script needs to be runned and
 *        create new thread for it.
 * @param fp_time_info    The information about the current time.
 *
void monitor_time(const struct tm *fp_time_info)
{
    //! Hold the previous second.
    static int prev_sec = 0;
    int        index    = 0;

    if (fp_time_info == NULL)
    {
        printf("fp_time_info is NULL\n");

        exit(1);
    }
    else
    {
        //! In order to check scripts once every second.
        if (prev_sec != fp_time_info->tm_sec)
        {
            printf("Hour %d, min %d, sec %d\n", fp_time_info->tm_hour, fp_time_info->tm_min, fp_time_info->tm_sec);

            //! Through every available script.
            for(index = 0; index < fs_count_of_scripts_for_execution; index++)
            {
                //! Check the time of execution.
                if ((fs_scripts_for_execution[index].hour   == fp_time_info->tm_hour) &&
                    (fs_scripts_for_execution[index].minute == fp_time_info->tm_min) &&
                    (fs_scripts_for_execution[index].second == fp_time_info->tm_sec))
                {
                    //! Create the new thread where the script will be executed.
                    create_new_thread(fs_scripts_for_execution[index].script_name,
                                      fs_scripts_for_execution[index].pthread_id);
                }
            }

            //! Store current second as previous
            prev_sec = fp_time_info->tm_sec;
        }
    }
}
*/
