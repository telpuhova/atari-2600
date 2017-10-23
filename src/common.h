#ifndef _COMMON_
#define _COMMON_
#include "stdint.h"
#include "stddef.h"
#include "stdarg.h"

#ifndef MAX_LOG_LEVEL 
#define MAX_LOG_LEVEL 2
#endif

class Log {
	public:
		void set_log_level(uint8_t log_level);
		uint8_t get_log_level();
    protected:
        Log(const char* device_name) : log_level(0), device_name(device_name) {};
        void log(int level, const char* format, ...);
		void log_wo_check(const char* format, ...);
	private:
		const char* device_name;
		uint8_t log_level;
		void _log(const char * format, va_list arg);
};

class Memory { //Interface Memory
	public:
		virtual void write_byte(uint16_t address, uint8_t byte) = 0;
		virtual uint8_t read_byte(uint16_t address) = 0;
};


#endif
