#include <iostream>
#include <stdio.h>
#include "Cpu6507.h"
#include "MemoryController.h"
#include "rom.h"

int main(){
    std::cout<<"start"<<std::endl;

    MemoryController memory_controller("MemoryController");
    Cpu6507 cpu("Cpu6507", &memory_controller);
	Rom rom("ROM");
	
	cpu.set_log_level(MAX_LOG_LEVEL);
	memory_controller.set_log_level(MAX_LOG_LEVEL);
	rom.set_log_level(MAX_LOG_LEVEL);
	
	memory_controller.map(0, 256, 0, &rom);
	
    cpu.do_one_instr();
    cpu.do_one_instr();
}
