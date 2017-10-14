#ifndef _ROM_
#define _ROM_
#include "common.h"

class Rom : public Log, public Memory {
    private:
        //TODO data length
        uint8_t data[256];
    public:
        Rom(const char* device_name);
		void write_byte(uint16_t address, uint8_t byte);
		uint8_t read_byte(uint16_t address);
};

#endif
