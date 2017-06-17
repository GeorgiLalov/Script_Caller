/**
*    Providing API for reading the file with scripts.
*    Define helper functions to read from file in order for the
*    list manager to create the list with scripts.
*
*    File structure:
*    On the first line: number of scripts in the file.
*
*    For every script:
*
*    hour
*    minute
*    second
*    script name
*/

#include "scripts_file_reader.h"

//! Location and name of the file with scripts.
#define SCRIPTS_FILE_NAME    "scripts/scripts.txt"

//! Name is written on one line.
//! TODO: Not good logic here.
#define LINE_MAX_LENGTH      SCRIPT_NAME_MAX_LENGTH

//! Reading mode from file.
#define READ_MODE            "r"

#define NEW_LINE_CHAR        '\n'

static FILE *fs_pFileForReading       = NULL;
//! The number of scripts to be readed in future.
//! Used to determine where is the end of file.
static int  fs_unreadedScriptsCount   = 0;

/**
 * @brief Removing the new line character from the end of the string.
 * @param fp_pBuffer         The string.
 * @param fp_bufferLength    The size of the string.
 */
void fs_removeNewLineChar(char      *fp_pBuffer,
                          const int fp_bufferLength)
{
    int letterIndex = 0;

    //! If buffer is invalid pointer.
    if (fp_pBuffer == NULL)
    {
        LOG_WRITE(eLogLevel_Error,
                  "%s", "fp_pBuffer is null");
    }
    else
    {
        //! For each letter in the string.
        for (letterIndex = 0; letterIndex < fp_bufferLength; letterIndex++)
        {
            //! If the letter is new line character.
            if (fp_pBuffer[letterIndex] == NEW_LINE_CHAR)
            {
                //! Put termining null character instead.
                fp_pBuffer[letterIndex] = '\0';

                break;
            }
        }
    }
}

/**
 * @brief Read scripts count from the file.
 *        Should be written on the first line.
 * @return The scripts count.
 */
int Reader_GetScriptsCount(void)
{
    int  scriptsCount          = 0;
    char line[LINE_MAX_LENGTH] = { '\0' };

    //! Try to open the file for reading.
    fs_pFileForReading = fopen(SCRIPTS_FILE_NAME,
                               READ_MODE);

    //! If file didn't opened.
    if (fs_pFileForReading == NULL)
    {
        LOG_WRITE(eLogLevel_Error, "Error opening file %s for reading",
                  SCRIPTS_FILE_NAME);
    }
    else
    {
        //! Read the first line, it should be number.
        fgets(line, LINE_MAX_LENGTH, fs_pFileForReading);

        //! Convert string to int.
        scriptsCount = atoi(line);

        //! Copy to unreaded count.
        fs_unreadedScriptsCount = scriptsCount;
    }

    //! Return the scripts count.
    return scriptsCount;
}

/**
 * @brief Read script from the file.
 *        Scripts are written in the pattern:
 *        hour
 *        minute
 *        second
 *        script name
 * @return The readed script.
 */
tsScriptData Reader_GetNextScript(void)
{
    tsScriptData sScriptData           = { 0, 0, 0, { '\0' } };
    char         line[LINE_MAX_LENGTH] = { '\0' };

    //! If file is not opened for reading..
    if (fs_pFileForReading == NULL)
    {
        LOG_WRITE(eLogLevel_Error, "File %s is not opened for reading",
                  SCRIPTS_FILE_NAME);
    }
    //! If we should't read.
    else if (fs_unreadedScriptsCount <= 0)
    {
        LOG_WRITE(eLogLevel_Error, "Unreaded count is %d",
                  fs_unreadedScriptsCount);
    }
    else
    {
        //! Read line from the file.
        fgets(line, LINE_MAX_LENGTH, fs_pFileForReading);

        //! Convert string to int, get hour.
        sScriptData.hour = atoi(line);

        //! Read line from the file.
        fgets(line, LINE_MAX_LENGTH, fs_pFileForReading);

        //! Convert string to int, get hour.
        sScriptData.minute = atoi(line);

        //! Read line from the file.
        fgets(line, LINE_MAX_LENGTH, fs_pFileForReading);

        //! Convert string to int, get hour.
        sScriptData.second = atoi(line);

        //! Read line from the file.
        fgets(line, LINE_MAX_LENGTH, fs_pFileForReading);

        //! Remove the new line at the end of the string.
        fs_removeNewLineChar(line, LINE_MAX_LENGTH);

        //! Copy the file name to the struct.
        strncpy(sScriptData.name, line ,SCRIPT_NAME_MAX_LENGTH);

        //! Decrease the unreaded count.
        fs_unreadedScriptsCount--;
    }

    //! Return the script data.
    return sScriptData;
}

/**
 * @brief Close the stream to the file.
 */
void Reader_CloseStream(void)
{
    if (fs_pFileForReading == NULL)
    {
        LOG_WRITE(eLogLevel_Warning, "%s",
                  "Trying to close the file stream with null stream pointer");
    }
    else
    {
        //! Close the file stream.
        fclose(fs_pFileForReading);
    }

}
