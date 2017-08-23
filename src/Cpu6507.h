#include "common.h"
#include "rom.h"

class Cpu6507: private Log {
    struct Instruction {
        uint8_t opcode;
        uint8_t length_with_data;
        void (Cpu6507::*interpretator)(void);
        void (*disasm)(uint8_t* data);
    };

    public:
        Cpu6507(Rom* rom);
        void do_one_instr();
    private:
        uint16_t ip;
        uint8_t args[2];
        Rom* rom;
        static const Instruction instructions[];


        void _int_A0(void);
        void _int_A1(void);
};
