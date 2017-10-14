#ifndef _COMMON_
#define _COMMON_
#include "stdint.h"
#include "stddef.h"

#ifndef MAX_LOG_LEVEL 
#define MAX_LOG_LEVEL 2
#endif

class Log {
	public:
		void set_log_level(uint8_t log_level);
    protected:
        Log(const char* device_name) : log_level(0), device_name(device_name) {};
        void log(int level, const char* format, ...);
	private:
		const char* device_name;
		uint8_t log_level;
};

class Memory {
	public:
		virtual void write_byte(uint16_t address, uint8_t byte) = 0;
		virtual uint8_t read_byte(uint16_t address) = 0;
};

#endif
