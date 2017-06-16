#ifndef SCRIPT_EXECUTIONER_H
#define SCRIPT_EXECUTIONER_H

#include <pthread.h>

#include "log_write.h"
#include "time_manager.h"
#include "scripts_file_reader.h"
#include "scripts_list_management.h"

void create_new_thread(const char *fp_script_name,
                       int        fp_script_index);

#endif // SCRIPT_EXECUTIONER_H
