#include "rom.h"

Rom::Rom(const char* device_name): Log(device_name) {
    //TODO
    this->data[0] = 0xA0;
    this->data[1] = 0xA1;
    this->data[2] = 0xDE;
}

void Rom::write_byte(uint16_t address, uint8_t byte){
	log(0, "ERROR: Rom write access, addr = 0x%x, value = 0x%x", address, byte);
}

uint8_t Rom::read_byte(uint16_t address){
	 if(sizeof(data) > address){
        return this->data[address];
    }else{
        return 0xff;
    }
}
