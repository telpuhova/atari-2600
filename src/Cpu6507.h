#include "common.h"
#include "rom.h"

class Cpu6507;

typedef void (Cpu6507::*Cpu6507Fn)();
#define CALL_MEMBER_FN(object, ptr_to_member) ((object).*(ptr_to_member))


class Cpu6507: private Log {
    struct Instruction {
        uint8_t data_length;
        //void (*interpretator)(void);
        //void (*disasm)();
        Cpu6507Fn interpretator;
        Cpu6507Fn disasm;
		Instruction(uint8_t data_length, Cpu6507Fn interpretator, Cpu6507Fn disasm): data_length(data_length), interpretator(interpretator), disasm() { }
    };

    public:
        Cpu6507(Rom* rom);
		~Cpu6507();
        void do_one_instr();
    private:
        uint16_t ip;
        uint8_t args[2];
        Rom* rom;
        Instruction *instructions[256];

		void _init_instr();
		void _deinit_instr();
        void _int_A0(void);
        void _int_A1(void);
};
