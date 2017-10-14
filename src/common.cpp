#include <typeinfo>
#include "common.h"
#include "stdio.h"
#include "stdarg.h"

void Log::log(int level, const char* format, ...){
    if(this->log_level >= level){
        va_list arg;
        va_start(arg, format);
		printf("[%s] ", device_name);
        vprintf(format, arg);
        va_end(arg);
        printf("\n");
    }
}

void Log::set_log_level(uint8_t log_level){
	if(MAX_LOG_LEVEL < log_level){
		log(0, "ERROR: Attempt to set bigger log-level than it's allowed to, max log-level is %d", MAX_LOG_LEVEL);
	}
	this->log_level = log_level;
}
