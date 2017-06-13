#ifndef LOG_WRITE_H
#define LOG_WRITE_H

#include <stdio.h>
#include <stdarg.h>

#include "time_manager.h"

void Log_Write(int fp_debug_lvl, char *fp_format, ...);

#endif // LOG_WRITE_H
