#ifndef SCRIPT_EXECUTIONER_H
#define SCRIPT_EXECUTIONER_H

#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "log_write.h"
#include "scripts_list_management.h"

void Execute_Script(const char *fp_pScriptName,
                    const int  fp_scriptIndex);

#endif // SCRIPT_EXECUTIONER_H
