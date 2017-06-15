/**
*    Managing the list with scripts.
*/

//! TODO: First allocate all space with malloc.

#include "scripts_list_management.h"

static tsScriptData *fs_scriptsHead = NULL;
static int          fs_scriptsCount = 0;

/**
 * @brief Read from file with scripts and init
 *       the list with scripts
 */
void ScriptsList_Init(void)
{
    int count = Reader_GetScriptsCount();
    int index = 0;
    tsScriptData scData;

    for (index = 0; index < count; index++)
    {
        scData =  Reader_GetNextScript();
    }
}

/**
 * @brief Free the memory allocated by the list.
 */
void ScriptsList_Destroy(void)
{

}

/**
 * @brief Return the count of scripts in the list.
 */
void ScriptsList_GetCount(void)
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
        LOG_WRITE(eLogLevel_Error, "fs_scriptsHead is NULL");
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
        retScript = fs_scriptsHead[fp_scriptIndex];
    }

    return retScript;
}
