#include <typeinfo>
#include "common.h"
#include "stdio.h"
#include "stdarg.h"

void Log::log(int level, const char* format, ...){
    if(this->log_level >= level){
        va_list arg;
        va_start(arg, format);
        vprintf(format, arg);
        va_end(arg);
        printf("\n");
    }
}
