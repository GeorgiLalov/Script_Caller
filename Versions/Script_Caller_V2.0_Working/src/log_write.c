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

//! The format of the time printed in the log file.
//! Example: Thu Aug 23 14:55:02 2001
#define TIME_FORMAT                  "%c"

//! Define strings of log levels.
static char fs_logLevelString[eLogLevel_UpperBound][LOG_ERROR_TYPE_MAX_LENGTH] =
{
    { "INFO" },
    { "WARNING" },
    { "ERROR" },
    { "ISSUE" }
};

/**
 * @brief Write log message to the log file.
 * @param fp_pFileName        The file from where the log_write was called.
 * @param fp_lineNumber       The line number from where the log_write was called.
 * @param fp_pFunctionName    The function name from where the log_write was called.
 * @param fp_eLogLevel        What level is the log.
 * @param fp_pFormat          The format of the message.
 */
void Log_Write(const char *fp_pFileName,
               const int  fp_lineNumber,
               const char *fp_pFunctionName,
               teLogLevel fp_eLogLevel,
               char       *fp_pFormat,
               ...)
{
    va_list varArgPtr;
    FILE    *pFileForWriting                         = NULL;
    char    messageText[MESSAGE_TEXT_MAX_LENGTH]     = { '\0' };
    char    formattedTime[FORMATTED_TIME_MAX_LENGTH] = { '\0' };

    //! Initialize the variable arguments.
    va_start(varArgPtr, fp_pFormat);

    //! Copy the formatted variable arguments as message text.
    vsprintf(messageText, fp_pFormat, varArgPtr);

    //! Free the memory for the variable arguments.
    va_end(varArgPtr);

    //! Open file stream for writing.
    pFileForWriting = fopen(LOG_FILE_NAME, APPEND_MODE);

    //! If there is no problem with opening file for writing.
    if (pFileForWriting != NULL)
    {
        //! Get the formatted time.
        TimeManager_GetFormattedTime(formattedTime,
                                     FORMATTED_TIME_MAX_LENGTH,
                                     TIME_FORMAT);

        //! Format the destination log and append to file.
        fprintf(pFileForWriting, "%s :: log level %s :: (in file:%s func:%s line:%d) %s\n",
                formattedTime, fs_logLevelString[fp_eLogLevel], fp_pFileName,
                fp_pFunctionName, fp_lineNumber, messageText);

        //! Close the file stream.
        fclose(pFileForWriting);
    }
}


