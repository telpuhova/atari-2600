#include <iostream>
#include <stdio.h>
#include "Cpu6507.h"
#include "rom.h"

int main(){
    std::cout<<"start"<<std::endl;

    Rom rom;
    Cpu6507 cpu(&rom);
    cpu.do_one_instr();
    cpu.do_one_instr();
}
