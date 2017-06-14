/**
*   Logging messages to log file.
*/

#include "log_write.h"

//! Name of the log file where messages will be saved.
#define LOG_FILE_NAME    "log.txt"

//! Maximum length of the message added to the log file.
#define LOG_MESSAGE_MAX_LENGTH    300

#define LOG_ERROR_STRING_MAX_LENGTH    10

//! Append writing mode to file.
#define APPEND_MODE    "a"

static char log_level_string[eLogLevel_UpperBound][LOG_ERROR_STRING_MAX_LENGTH] =
{
    { "INFO" },
    { "ERROR" },
    { "ISSUE" },
    { "FATAL" }
};

/**
 * @brief Writes logs to the log file.
 * @param fp_debug_lvl
 * @param fp_format
 */
void Log_Write(teLogLevel fp_log_level, char *fp_format, ...)
{
    char destination_log[LOG_MESSAGE_MAX_LENGTH] = { '\0' };
    char message_log[200]   = { '\0' };
    char formatted_time[100] = { '\0' };
    va_list argptr;
    FILE *pFileForWriting = NULL;

    va_start(argptr, fp_format);
    vsprintf(message_log, fp_format, argptr);
    va_end(argptr);

    //! Open file stream for writing.
    pFileForWriting = fopen(LOG_FILE_NAME, APPEND_MODE);

    //! If there is no problem with opening file for writing.
    if (pFileForWriting != NULL)
    {
        //! Get the formatted time
        TimeManager_GetFormattedTime(formatted_time, 100);

        //! format the destination log and append to file.
        fprintf(pFileForWriting, "%s :: log level %s :: %s", formatted_time, log_level_string[fp_log_level], message_log);

        //! Close the file stream.
        fclose(pFileForWriting);
    }
}


