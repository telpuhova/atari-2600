#ifndef _COMMON_
#define _COMMON_
#include "stdint.h"

class Log {
    public:
        uint8_t log_level;
    protected:
        Log() : log_level(1) {};
        void log(int level, const char* format, ...);
};

#endif
