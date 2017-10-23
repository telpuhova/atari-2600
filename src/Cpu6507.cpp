#include "Cpu6507.h"
#include <stdio.h>
#include <functional>
#include <iostream>

Cpu6507::Cpu6507(const char* device_name, MemoryController* memory_controller) : Log(device_name), memory_controller(memory_controller), IP(0) {
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
	log(MAX_LOG_LEVEL, "do_one_instr");
	assert(("memory_controller is NULL", memory_controller != NULL));
    	
    uint8_t current_instr = memory_controller->read_byte(IP);
    IP++;
	log(MAX_LOG_LEVEL, "Got 0x%x", current_instr);

    if(instructions[current_instr] == NULL){
		log_wo_check("ERROR: Illegal instruction, opcode = 0x%x", current_instr);
		return;
    }
	
	log(MAX_LOG_LEVEL, "Retrieving args");
    for(int i = 0; i < instructions[current_instr]->data_length; i++){
        args[i] = memory_controller->read_byte(IP);
        IP++;
		log(MAX_LOG_LEVEL, "Got 0x%x", args[i]);
    }

	if(get_log_level() == MAX_LOG_LEVEL){
		if(instructions[current_instr]->disasm != NULL){
			CALL_MEMBER_FN(*this, instructions[current_instr]->disasm)();
		}else{
			log_wo_check("disasm lacks for this instruction, opcode is 0x%x", current_instr);
		}
	}
	
	log(MAX_LOG_LEVEL, "Calling interpretator");
    CALL_MEMBER_FN(*this, instructions[current_instr]->interpretator)();
}

void Cpu6507::_init_instr(){
	Cpu6507::Instruction *instr;
	for(int i = 0; i < 256; i++){
		instructions[i] = NULL;		
	}
	
	//Adding instructions
	instr = new Cpu6507::Instruction(0, 2, &Cpu6507::_TAY, NULL); //creating a new object of Instruction 
	instructions[0xA8] = instr; //putting this item to the main instructions array at offset = opcode
	
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
	
	instr = new Cpu6507::Instruction(0, 3, &Cpu6507::_LDA_nn, NULL);	
	instructions[0xA5] = instr;
	
	instr = new Cpu6507::Instruction(0, 4, &Cpu6507::_LDA_nn_X, NULL);
	instructions[0xB5] = instr;
	
	instr = new Cpu6507::Instruction(0, 4, &Cpu6507::_LDA_nnnn, NULL);
	instructions[0xAD] = instr;
	
	instr = new Cpu6507::Instruction(0, 3, &Cpu6507::_STA_nn, NULL);
	instructions[0x85] = instr;
	
	instr = new Cpu6507::Instruction(0, 4, &Cpu6507::_STA_nn_X, NULL);
	instructions[0x95] = instr;
	
}

//Instructions interpretator functions 
void Cpu6507::_TAY(){
    Y = A;
	PSR.N = (Y >> 7) & 1;
	PSR.Z = !Y;
}

void Cpu6507::_d_TAY(){
	log_wo_check("A8        nz----  2   TAY         MOV Y,A             ;Y=A, arg - N/A");
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

void Cpu6507::_LDA_nn(){
	A = memory_controller->read_byte(args[0]);
	PSR.N = (A >> 7) & 1;
	PSR.Z = !A;
}

void Cpu6507::_d_LDA_nn(){
	log_wo_check("A5 nn     nz----  3   LDA nn      MOV A,[nn]          ;A=[nn], arg - 0x%x", args[0]);
}

void Cpu6507::_LDA_nn_X(){
	A = memory_controller->read_byte((args[0] + X) % 0x100);
	PSR.N = (A >> 7) & 1;
	PSR.Z = !A;
}

void Cpu6507::_d_LDA_nn_X(){
	log_wo_check("B5 nn     nz----  4   LDA nn,X    MOV A,[nn+X]        ;A=[nn+X], arg - 0x%x, X = 0x%x", args[0], X);
}

void Cpu6507::_LDA_nnnn(){
	A = memory_controller->read_byte((args[1] << 8) | args[0]);//TODO check if BE/LE used  
	PSR.N = (A >> 7) & 1;
	PSR.Z = !A;
}

void Cpu6507::_d_LDA_nnnn(){
	log_wo_check("AD nn nn  nz----  4   LDA nnnn    MOV A,[nnnn]        ;A=[nnnn], args - 0x%x", (args[1] << 8) | args[0]);
}

void Cpu6507::_STA_nn(){
	memory_controller->write_byte(args[0], A);
}

void Cpu6507::_STA_nn_X(){
	memory_controller->write_byte((args[0] + X) % 0x100, A);
}
