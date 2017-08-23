#include "rom.h"

Rom::Rom() {
    //TODO
    this->data[0] = 0xA0;
    this->data[1] = 0xA1;
    this->data[1] = 0xDE;
}

uint8_t Rom::fetch(uint16_t address){
    if(sizeof(data) > address){
        return this->data[address];
    }else{
        return 0xff;
    }
}
