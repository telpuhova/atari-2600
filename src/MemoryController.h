#ifndef _MemoryController_
#define _MemoryController_
#include "common.h"

class MemoryController : public Log, public Memory {
	struct MapItem {
		uint16_t start_address;
		uint16_t end_address;
		uint16_t offset;
		Memory* memory;
		MapItem(uint16_t start_address, uint16_t length, uint16_t offset, Memory* memory): start_address(start_address), offset(offset), memory(memory) {
			end_address = start_address + length - 1;
		}
	};
	struct MapChainItem {
		MapChainItem* next;
		MapChainItem* previous;
		MapItem map_item;
		MapChainItem(MapChainItem* next, MapChainItem* previous, uint16_t start_address, uint16_t length, uint16_t offset, Memory* memory): next(next), previous(previous), map_item(start_address, length, offset, memory) { }
	};
    private:
        MapChainItem* head;
        MapChainItem* tail;
        MapChainItem* last;
		
		MapItem* find_memory(uint16_t address);
    public:
		MemoryController(const char* device_name): Log(device_name) {
			head = NULL;
			tail = NULL;
			last = NULL;
		}	
		~MemoryController();
		
		void map(uint16_t start_address, uint16_t length, uint16_t offset, Memory* memory);
		void write_byte(uint16_t address, uint8_t byte);
		uint8_t read_byte(uint16_t address);
        
};

#endif
