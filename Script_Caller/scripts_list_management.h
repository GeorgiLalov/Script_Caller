#ifndef SCRIPTS_LIST_MANAGEMENT_H
#define SCRIPTS_LIST_MANAGEMENT_H

#include "stdio.h"

#include "log_write.h"
#include "scripts_file_reader.h"

//! Define the maximum number of scripts.
#define MAX_COUNT_OF_SCRIPTS    20

int           ScriptsList_Init(void);
void          ScriptsList_Destroy(void);
int           ScriptsList_GetCount(void);
tsScriptData* ScriptsList_GetByIndex(int fp_scriptIndex);

#endif // SCRIPTS_LIST_MANAGEMENT_H
