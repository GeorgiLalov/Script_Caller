#ifndef SCRIPTS_LIST_MANAGEMENT_H
#define SCRIPTS_LIST_MANAGEMENT_H

#include "stdio.h"

#include "log_write.h"
#include "scripts_file_reader.h"

void          ScriptsList_Init(void);
void          ScriptsList_Destroy(void);
void          ScriptsList_GetCount(void);
tsScriptData* ScriptsList_GetByIndex(int fp_scriptIndex);

#endif // SCRIPTS_LIST_MANAGEMENT_H
