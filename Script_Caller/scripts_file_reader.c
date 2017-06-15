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

static FILE *fs_pFileForReading = NULL;
static int  fs_scripts_count    = 0;
//! Used to determine where is the end of file.
static int  fs_internal_count   = 0;

int Reader_GetScriptsCount(void)
{
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
        fs_scripts_count = atoi(line);

        //! Copy to internal count.
        fs_internal_count = fs_scripts_count;
    }

    //! Return the scripts count.
    return fs_scripts_count;
}

tsScriptData Reader_GetNextScript(void)
{
    char         line[LINE_MAX_LENGTH] = { '\0' };
    tsScriptData sScriptData           = { 0, 0, 0, { '\0' } };

    //! If file is not opened for reading..
    if (fs_pFileForReading == NULL)
    {
        LOG_WRITE(eLogLevel_Error, "File %s is not opened for reading",
                  SCRIPTS_FILE_NAME);
    }
    //! If we should't read.
    else if (fs_internal_count <= 0)
    {
        LOG_WRITE(eLogLevel_Error, "Internal count is %d",
                  fs_internal_count);
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

        //! Get file name.
        strncpy(sScriptData.script_name, line ,SCRIPT_NAME_MAX_LENGTH);

        //! Decrease the internal count.
        fs_internal_count--;

        //! If there are no more readings expected.
        if (fs_internal_count == 0)
        {
            //! Close the file stream.
            fclose(fs_pFileForReading);
        }
    }

    //! Return the script data.
    return sScriptData;
}

