/**
*   Logging messages to log file.
*/

#include "log_write.h"

//! Name of the log file where messages will be saved.
#define LOG_FILE_NAME                "log.txt"

//! Maximum length of the message text added to the log file.
#define MESSAGE_TEXT_MAX_LENGTH      200

//! Maximum length of the error type string.
#define LOG_ERROR_TYPE_MAX_LENGTH    10

//! Maximum length of the formatted time string.
//! Enough to store "Thu Aug 23 14:55:02 2001"
#define FORMATTED_TIME_MAX_LENGTH    30

//! Append writing mode to file.
#define APPEND_MODE                  "a"

//! Define strings of log levels.
static char log_level_string[eLogLevel_UpperBound][LOG_ERROR_TYPE_MAX_LENGTH] =
{
    { "INFO" },
    { "ERROR" },
    { "ISSUE" },
    { "FATAL" }
};

/**
 * @brief Write log message to the log file.
 * @param fp_fileName        The file from where the log_write was called.
 * @param fp_lineNumber      The line number from where the log_write was called.
 * @param fp_functionName    The function name from where the log_write was called.
 * @param fp_log_level       What level is the log.
 * @param fp_format          The format of the message.
 */
void Log_Write(const char *fp_fileName,
               int        fp_lineNumber,
               const char *fp_functionName,
               teLogLevel fp_log_level,
               char       *fp_format,
               ...)
{
    va_list argptr;
    FILE    *pFileForWriting                          = NULL;
    char    message_text[MESSAGE_TEXT_MAX_LENGTH]     = { '\0' };
    char    formatted_time[FORMATTED_TIME_MAX_LENGTH] = { '\0' };

    //! Initialize the variable arguments.
    va_start(argptr, fp_format);

    //! Copy the formatted variable arguments as message text.
    vsprintf(message_text, fp_format, argptr);

    //! Free the memory for the variable arguments.
    va_end(argptr);

    //! Open file stream for writing.
    pFileForWriting = fopen(LOG_FILE_NAME, APPEND_MODE);

    //! If there is no problem with opening file for writing.
    if (pFileForWriting != NULL)
    {
        //! Get the formatted time.
        TimeManager_GetFormattedTime(formatted_time,
                                     FORMATTED_TIME_MAX_LENGTH);

        //! Format the destination log and append to file.
        fprintf(pFileForWriting, "%s :: log level %s :: (in file:%s func:%s line:%d) %s",
                formatted_time, log_level_string[fp_log_level], fp_fileName, fp_functionName,
                fp_lineNumber, message_text);

        //! Close the file stream.
        fclose(pFileForWriting);
    }
}


