#ifndef LOG_WRITE_H
#define LOG_WRITE_H

#include <stdio.h>
#include <stdarg.h>

#include "time_manager.h"

//! Macro function for calling log_write with parameters for file name, line number and
//! function name.
#define LOG_WRITE(log_level, format, ...) \
    Log_Write(__FILE__, __LINE__, __func__, log_level, format, __VA_ARGS__)

//! Define log levels
typedef enum
{
    eLogLevel_Info       = 0,
    eLogLevel_Error      = 1,
    eLogLevel_Issue      = 2,
    eLogLevel_Fatal      = 3,

    eLogLevel_UpperBound = 4
} teLogLevel;

void Log_Write(const char *fp_fileName,
               int        fp_lineNumber,
               const char *fp_functionName,
               teLogLevel fp_log_level,
               char       *fp_format,
               ...);

#endif // LOG_WRITE_H
