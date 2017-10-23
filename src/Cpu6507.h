#include "common.h"
#include "MemoryController.h"
#include <assert.h>

class Cpu6507;

typedef void (Cpu6507::*Cpu6507Fn)();
#define CALL_MEMBER_FN(object, ptr_to_member) ((object).*(ptr_to_member))


class Cpu6507: public Log {
    struct Instruction {
        uint8_t data_length;
        uint8_t cycle_count;
        Cpu6507Fn interpretator;
        Cpu6507Fn disasm;
		Instruction(uint8_t data_length, uint8_t cycle_count, Cpu6507Fn interpretator, Cpu6507Fn disasm): data_length(data_length), cycle_count(cycle_count), disasm(disasm) { 
			assert(interpretator != NULL);
			this->interpretator = interpretator;
		}
    };
	
	struct PSR_t {
		uint8_t C : 1; //Carry         (0=No Carry, 1=Carry)
		uint8_t Z : 1; //Zero          (0=Nonzero, 1=Zero)
		uint8_t I : 1; //IRQ Disable   (0=IRQ Enable, 1=IRQ Disable)
		uint8_t D : 1; //Decimal Mode  (0=Normal, 1=BCD Mode for ADC/SBC opcodes)
		uint8_t B : 1; //Break Flag    (0=IRQ/NMI, 1=RESET or BRK/PHP opcode)
		uint8_t :1;    //Not used      (Always 1)
		uint8_t V : 1; //Overflow      (0=No Overflow, 1=Overflow)
		uint8_t N : 1; //Negative/Sign (0=Positive, 1=Negative)
	};

    public:
        Cpu6507(const char* device_name, MemoryController* memory_controller);
		~Cpu6507();
        void do_one_instr();
    private:
		//Registers
        uint16_t IP; 	//Program Counter
		uint8_t A; 		//Accumulator
		uint8_t X; 		//Index Register X
		uint8_t Y; 		//Index Register Y
		uint8_t S; 		//Stack Pointer
		uint8_t P; 		//Processor Status Register
		PSR_t PSR; 		//Processor Status Register (Flags)
		
		
        uint8_t args[2];
        MemoryController* memory_controller;
        Instruction *instructions[256];

		void _init_instr();
		void _deinit_instr();
		
		//Instructions interpretator functions 
		//Register/Immeditate to Register Transfer
		void _TAY();
		void _d_TAY();
		void _TAX();
		void _TSX();
		void _TYA();
		void _TXA();
		void _TXS();
		void _LDA_hnn();
		void _LDX_hnn();
		void _LDY_hnn();
		//Load Register from Memory
		void _LDA_nn();
		void _d_LDA_nn();
		void _LDA_nn_X();
		void _d_LDA_nn_X();
		void _LDA_nnnn();
		void _d_LDA_nnnn();
		//TODO
		//Store Register in Memory
		void _STA_nn();
		void _STA_nn_X();
		//TODO
};
