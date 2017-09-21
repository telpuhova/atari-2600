#include "Cpu6507.h"
#include <stdio.h>
#include <functional>
#include <iostream>

Cpu6507::Cpu6507(Rom* rom) : Log(), rom(rom), ip(0) {
	_init_instr();
}

Cpu6507::~Cpu6507(){
	_deinit_instr();
}

void Cpu6507::_init_instr(){
	Cpu6507::Instruction *instr;
	for(int i = 0; i < 256; i++){
		instructions[i] = NULL;		
	}
	
	//Adding instructions
	instr = new Cpu6507::Instruction(0, &Cpu6507::_int_A0, NULL);
	instructions[0xA0] = instr;
	
	instr = new Cpu6507::Instruction(1, &Cpu6507::_int_A1, NULL);
	instructions[0xA1] = instr;
	
}

void Cpu6507::_deinit_instr(){
	for(int i = 0; i < 256; i++){
		if (instructions[i] != NULL){
			delete instructions[i];
		}		
	}
}
							
void Cpu6507::do_one_instr(){
    if(rom == NULL){
		//TODO: change to assert
        log(0, "ERROR: rom is null");
        return;
    }
	
    uint8_t current_instr = rom->fetch(ip);
    ip++;

    if(instructions[current_instr] == NULL){
			log(0, "ERROR: Illegal instruction, opcode = 0x%x", current_instr);
			return;
    }

    for(int i = 0; i < instructions[current_instr]->data_length; i++){
        args[i] = rom->fetch(ip);
        ip++;
    }

    // Cpu6507Fn ptf = instructions[current_instr]->interpretator;
    // CALL_MEMBER_FN(*this, ptf)();
    CALL_MEMBER_FN(*this, instructions[current_instr]->interpretator)();
}

void Cpu6507::_int_A0(void){
    log(1,"A0");
}

void Cpu6507::_int_A1(void){
    log(1,"A1 - 0x%x", this->args[1]);
}

