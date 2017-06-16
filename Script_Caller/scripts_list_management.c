/**
*    Managing the list with scripts.
*/

#include "scripts_list_management.h"

static tsScriptData *fs_scriptsHead = NULL;
static int          fs_scriptsCount = 0;

/**
 * @brief Read from file with scripts and init
 *        the list with scripts
 */
void ScriptsList_Init(void)
{
    int scriptIndex = 0;
    
    //! Read the scripts count from the file with scripts.
    fs_scriptsCount = Reader_GetScriptsCount();
    
    //! If scripts count is not a valid count number.
    if (fs_scriptsCount <= 0)
    {
        LOG_WRITE(eLogLevel_Error, 
                  "Invalid scripts count readed, fs_scriptsCount %d", 
                  fs_scriptsCount);
    }
    else
    {
        //! If there are more scripts in file that is allowed to.
        if (fs_scriptsCount > MAX_COUNT_OF_SCRIPTS)
        {
             LOG_WRITE(eLogLevel_Info, 
                       "Total count of scripts in file is %d, allowed count of scripts is %d,"
                       " only the allowed will be added to the list",
                       fs_scriptsCount, MAX_COUNT_OF_SCRIPTS);
                       
            //! The count is set to max.
            fs_scriptsCount = MAX_COUNT_OF_SCRIPTS;
        }
        
        //! Allocate space for all scripts data.
        fs_scriptsHead = (tsScriptData *) malloc(fs_scriptsCount * sizeof(tsScriptData));
        
        //! On memory error.
        if (fs_scriptsHead == NULL)
        {
            LOG_WRITE(eLogLevel_Error, "%s", "Error allocating memory for all scripts");
        }
        else
        {
            //! For each script.
            for (scriptIndex = 0; scriptIndex < fs_scriptsCount; scriptIndex++)
            {
                //! Copy the script data from file to the allocated space.
                fs_scriptsHead[scriptIndex] =  Reader_GetNextScript();

                 LOG_WRITE(eLogLevel_Info,
                 "Read and stored script with data: hour %d min %d sec %d name %s",
                 fs_scriptsHead[scriptIndex].hour, fs_scriptsHead[scriptIndex].minute,
                 fs_scriptsHead[scriptIndex].second, fs_scriptsHead[scriptIndex].script_name);
            }  
        }
    }
}

/**
 * @brief Free the memory allocated by the list.
 */
 //! TODO: Maybe use getCount and GetNext?
void ScriptsList_Destroy(void)
{
    int scriptIndex = 0;
    
    //! If scripts head is NULL.
    if (fs_scriptsHead == NULL)
    {
        //! TODO: Warning here, not error maybe.
        LOG_WRITE(eLogLevel_Error, "%s", "Trying to destroy list with null head");
    }
    else
    {
        //! For each script in the list.
        for (scriptIndex = 0; scriptIndex < fs_scriptsCount; scriptIndex++)
        {
            //! Deallocate the memory for the script.
            free(&(fs_scriptsHead[scriptIndex]));
        }
    }
}

/**
 * @brief Return the count of scripts in the list.
 */
int ScriptsList_GetCount(void)
{
    return fs_scriptsCount;
}

/**
 * @brief Return the script accessed by index.
 * @param fp_scriptIndex    The index.
 * @return  On success - valid pointer to script.
 *          On error   - NULL pointer.
 */
tsScriptData* ScriptsList_GetByIndex(int fp_scriptIndex)
{
    tsScriptData* retScript = NULL;

    //! If scripts head is not set.
    if (fs_scriptsHead == NULL)
    {
        LOG_WRITE(eLogLevel_Error, "%s", "fs_scriptsHead is NULL");
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
        retScript = &(fs_scriptsHead[fp_scriptIndex]);
    }

    return retScript;
}
