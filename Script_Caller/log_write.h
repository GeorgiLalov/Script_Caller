#ifndef LOG_WRITE_H
#define LOG_WRITE_H

#include <stdio.h>
#include <stdarg.h>

#include "time_manager.h"

//! Define log levels
typedef enum
{
    eLogLevel_Info       = 0,
    eLogLevel_Error      = 1,
    eLogLevel_Issue      = 2,
    eLogLevel_Fatal      = 3,

    eLogLevel_UpperBound = 4
} teLogLevel;

void Log_Write(teLogLevel fp_log_level, char *fp_format, ...);

#endif // LOG_WRITE_H
