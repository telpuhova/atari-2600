#include "Cpu6507.h"
#include <stdio.h>

Cpu6507::Cpu6507(Rom* rom) : Log(), rom(rom), ip(0) {
    printf("Here\n");
    log(1, "Log1 = 0x%x, log2 = %d\n", 0x15, 0x40);
}

const Cpu6507::Instruction Cpu6507::instructions[] = {
                            {0xA0, 1, &Cpu6507::_int_A0, NULL}, 
                            {0xA1, 2, &Cpu6507::_int_A1, NULL}};

void Cpu6507::do_one_instr(){
    if(rom == NULL){
        log(0, "ERROR: rom is null");
        return;
    }

    int i;
    uint8_t current_instr_idx;
    uint8_t current_instr = rom->fetch(ip);
    ip++;

    for(i = 0; i < sizeof(instructions); ++i){
        if(instructions[i].opcode == current_instr){
            current_instr_idx = i;
            break;
        }
    }
    if(i == sizeof(instructions)){
        log(0, "ERROR", "Illegal instruction");
    }

    for(i = 0; i < instructions[current_instr_idx].length_with_data; i++){
        args[i] = rom->fetch(ip);
        ip++;
    }

    instructions[current_instr_idx].*interpretator();
}

void Cpu6507::_int_A0(void){
    log(1,"A0");
}

void Cpu6507::_int_A1(void){
    log(1,"A1 - 0x%x", this->args[1]);
}
