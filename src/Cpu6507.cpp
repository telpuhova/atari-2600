#include "Cpu6507.h"
#include <stdio.h>
#include <functional>
#include <iostream>
#include <assert.h>

Cpu6507::Cpu6507(Rom* rom) : Log(), rom(rom), IP(0) {
	_init_instr();
}

Cpu6507::~Cpu6507(){
	_deinit_instr();
}

void Cpu6507::_deinit_instr(){
	for(int i = 0; i < 256; i++){
		if (instructions[i] != NULL){
			delete instructions[i];
		}		
	}
}
							
void Cpu6507::do_one_instr(){
	assert(("ROM is NULL", rom != NULL));
    	
    uint8_t current_instr = rom->fetch(IP);
    IP++;

    if(instructions[current_instr] == NULL){
		log(0, "ERROR: Illegal instruction, opcode = 0x%x", current_instr);
		return;
    }

    for(int i = 0; i < instructions[current_instr]->data_length; i++){
        args[i] = rom->fetch(IP);
        IP++;
    }

    CALL_MEMBER_FN(*this, instructions[current_instr]->interpretator)();
}

void Cpu6507::_init_instr(){
	Cpu6507::Instruction *instr;
	for(int i = 0; i < 256; i++){
		instructions[i] = NULL;		
	}
	
	//Adding instructions
	instr = new Cpu6507::Instruction(0, 2, &Cpu6507::_TAY, NULL);
	instructions[0xA8] = instr;
	
	instr = new Cpu6507::Instruction(0, 2, &Cpu6507::_TAX, NULL);
	instructions[0xAA] = instr;
	
	instr = new Cpu6507::Instruction(0, 2, &Cpu6507::_TSX, NULL);
	instructions[0xBA] = instr;
	
	instr = new Cpu6507::Instruction(0, 2, &Cpu6507::_TYA, NULL);
	instructions[0x98] = instr;
	
	instr = new Cpu6507::Instruction(0, 2, &Cpu6507::_TXA, NULL);
	instructions[0x8A] = instr;
	
	instr = new Cpu6507::Instruction(0, 2, &Cpu6507::_TXS, NULL);
	instructions[0x9A] = instr;
	
	instr = new Cpu6507::Instruction(1, 2, &Cpu6507::_LDA_hnn, NULL);
	instructions[0xA9] = instr;
	
	instr = new Cpu6507::Instruction(1, 2, &Cpu6507::_LDX_hnn, NULL);
	instructions[0xA2] = instr;
	
	instr = new Cpu6507::Instruction(1, 2, &Cpu6507::_LDY_hnn, NULL);
	instructions[0xA0] = instr;
	
}

//Instructions interpretator functions 
void Cpu6507::_TAY(){
    Y = A;
	PSR.N = (Y >> 7) & 1;
	PSR.Z = !Y;
}

void Cpu6507::_TAX(){
    X = A;
	PSR.N = (X >> 7) & 1;
	PSR.Z = !X;
}

void Cpu6507::_TSX(){
    X = S;
	PSR.N = (X >> 7) & 1;
	PSR.Z = !X;
}

void Cpu6507::_TYA(){
    A = Y;
	PSR.N = (A >> 7) & 1;
	PSR.Z = !A;
}

void Cpu6507::_TXA(){
    A = X;
	PSR.N = (A >> 7) & 1;
	PSR.Z = !A;
}

void Cpu6507::_TXS(){
    S = X;
}

void Cpu6507::_LDA_hnn(){
    A = args[0];
	PSR.N = (A >> 7) & 1;
	PSR.Z = !A;
}

void Cpu6507::_LDX_hnn(){
    X = args[0];
	PSR.N = (X >> 7) & 1;
	PSR.Z = !X;
}

void Cpu6507::_LDY_hnn(){
    Y = args[0];
	PSR.N = (Y >> 7) & 1;
	PSR.Z = !Y;
}
