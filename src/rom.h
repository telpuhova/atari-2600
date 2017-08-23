#ifndef _ROM_
#define _ROM_
#include "common.h"

class Rom : private Log {
    private:
        //TODO data length
        uint8_t data[3];
    public:
        Rom();
        uint8_t fetch(uint16_t address);
};

#endif
