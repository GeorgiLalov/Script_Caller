/**
*    Managing the list with scripts.
*/

#include "scripts_list_management.h"

static tsScriptData *fs_pScriptsHead = NULL;
static int          fs_scriptsCount  = 0;

/**
 * @brief Read from file with scripts and init
 *        the list with scripts.
 *
 * @retval 0  - If init was successful.
 *         -1 - On error.
 */
int ScriptsList_Init(void)
{
    int returnValue = 0;
    int scriptIndex = 0;
    
    //! Read the scripts count from the file with scripts.
    fs_scriptsCount = Reader_GetScriptsCount();
    
    //! If scripts count is not a valid count number.
    if (fs_scriptsCount <= 0)
    {
        LOG_WRITE(eLogLevel_Error, 
                  "Invalid scripts count readed, fs_scriptsCount %d", 
                  fs_scriptsCount);

        //! Return error.
        returnValue = -1;
    }
    else
    {
        //! If there are more scripts in file that is allowed to.
        if (fs_scriptsCount > MAX_COUNT_OF_SCRIPTS)
        {
             LOG_WRITE(eLogLevel_Warning,
                       "Total count of scripts in file is %d, allowed count of scripts is %d,"
                       " only the allowed will be added to the list",
                       fs_scriptsCount, MAX_COUNT_OF_SCRIPTS);
                       
            //! The count is set to max.
            fs_scriptsCount = MAX_COUNT_OF_SCRIPTS;
        }
        
        //! Allocate space for all scripts data.
        fs_pScriptsHead = (tsScriptData *) malloc(fs_scriptsCount * sizeof(tsScriptData));
        
        //! On memory error.
        if (fs_pScriptsHead == NULL)
        {
            LOG_WRITE(eLogLevel_Error, "%s", "Error allocating memory for all scripts");

            //! Return error.
            returnValue = -1;
        }
        else
        {
            //! For each script.
            for (scriptIndex = 0; scriptIndex < fs_scriptsCount; scriptIndex++)
            {
                //! Copy the script data from file to the allocated space.
                fs_pScriptsHead[scriptIndex] = Reader_GetNextScript();

                 LOG_WRITE(eLogLevel_Info,
                 "Read and stored script with data: hour %d min %d sec %d name %s",
                 fs_pScriptsHead[scriptIndex].hour, fs_pScriptsHead[scriptIndex].minute,
                 fs_pScriptsHead[scriptIndex].second, fs_pScriptsHead[scriptIndex].name);
            }  
        }
    }

    //! Close the file stream.
    Reader_CloseStream();

    return returnValue;
}

/**
 * @brief Free the memory allocated by the list.
 */
void ScriptsList_Destroy(void)
{
    //! If scripts head is NULL.
    if (fs_pScriptsHead == NULL)
    {
        LOG_WRITE(eLogLevel_Warning, "%s",
                  "Trying to destroy list with null head");
    }
    else
    {
        //! Free the memory.
        free(fs_pScriptsHead);

        //! Reset the static variables.
        fs_pScriptsHead  = NULL;
        fs_scriptsCount = 0;
    }
}

/**
 * @brief Get the count of scripts in the list.
 */
int ScriptsList_GetCount(void)
{
    return fs_scriptsCount;
}

/**
 * @brief Get script accessed by index.
 * @param fp_scriptIndex    The index.
 * @return  On success - valid pointer to script.
 *          On error   - NULL pointer.
 */
tsScriptData* ScriptsList_GetByIndex(const int fp_scriptIndex)
{
    tsScriptData *pRetScript = NULL;

    //! If scripts head is not set.
    if (fs_pScriptsHead == NULL)
    {
        LOG_WRITE(eLogLevel_Error, "%s", "fs_pScriptsHead is NULL");
    }
    //! If index is not in the bounds.
    else if (fp_scriptIndex >= fs_scriptsCount ||
             fp_scriptIndex < 0)
    {
        LOG_WRITE(eLogLevel_Error,
                  "Trying to access script with invalid index, fp_scriptIndex %d",
                  fp_scriptIndex);
    }
    else
    {
        //! Access the script by index.
        pRetScript = (fs_pScriptsHead + fp_scriptIndex);
    }

    return pRetScript;
}
