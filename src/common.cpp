#include <typeinfo>
#include "common.h"
#include "stdio.h"

void Log::log(int level, const char* format, ...){
    if(this->log_level >= level){
        va_list arg;
		va_start(arg, format);
		_log(format, arg);
		va_end(arg);
    }
}

void Log::log_wo_check(const char* format, ...){
	va_list arg;
	va_start(arg, format);
	_log(format, arg);
	va_end(arg);
}

void Log::_log(const char * format, va_list arg){
	printf("[%s] ", device_name);
	vprintf(format, arg);
	printf("\n");
}

void Log::set_log_level(uint8_t log_level){
	if(MAX_LOG_LEVEL < log_level){
		log(0, "ERROR: Attempt to set bigger log-level than it's allowed to, max log-level is %d", MAX_LOG_LEVEL);
	}
	this->log_level = log_level;
}

uint8_t Log::get_log_level(){
	return log_level;
}
