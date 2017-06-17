#ifndef SCRIPTS_FILE_READER_H
#define SCRIPTS_FILE_READER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log_write.h"

#define SCRIPT_NAME_MAX_LENGTH    100

//! Holding needed data about the script.
typedef struct
{
    int       hour;
    int       minute;
    int       second;
    char      name[SCRIPT_NAME_MAX_LENGTH];
} tsScriptData;

int          Reader_GetScriptsCount(void);
tsScriptData Reader_GetNextScript(void);
void         Reader_CloseStream(void);

#endif // SCRIPTS_FILE_READER_H
