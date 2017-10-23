#include "MemoryController.h"

MemoryController::~MemoryController(){
	MapChainItem *curr = head;
	MapChainItem *next;
	while(curr != NULL){
		next = curr->next;
		delete curr;
		curr = next;
	}
}

void MemoryController::map(uint16_t start_address, uint16_t length, uint16_t offset, Memory* memory){
	MapChainItem *prev;
	MapChainItem *new_item;
	
	if(head == NULL){ // if there is no mapping at all yet
		head = new MapChainItem(NULL, NULL, start_address, length, offset, memory);
	} else {
		prev = head;
		while(prev != NULL){
			if (prev->map_item.start_address >= start_address){
				break;
			}
			prev = prev->next;
		}
		if (prev == NULL){// if our map item is last
			new_item = new MapChainItem(NULL, prev, start_address, length, offset, memory);
			prev->next = new_item;
		}else{
			new_item = new MapChainItem(prev->next, prev, start_address, length, offset, memory);
			prev = prev->next->previous = new_item;
			prev->next = new_item;
			if(prev->next->map_item.start_address <= ( start_address + length - 1 )){
				log(0, "ERROR: Multiple mapping starting 0x%x", prev->next->map_item.start_address);
			}
		}
	}
}

MemoryController::MapItem* MemoryController::find_memory(uint16_t address){
	log(MAX_LOG_LEVEL, "find_memory, addr = 0x%x", address);
	MapChainItem *curr;
	curr = head;
	if(last != NULL){
		if(last->map_item.start_address < address){
			curr = last;
		}
	}
	
	while(curr != NULL){
		if(curr->map_item.start_address <= address){
			if(curr->map_item.end_address >= address){
				last = curr;
				return &(curr->map_item);
			}
		}else{
			return NULL;
		}
		curr = curr->next;
	}
	return NULL;
}

void MemoryController::write_byte(uint16_t address, uint8_t byte) {
	MapItem *map_item = find_memory(address);
	if(map_item == NULL){
		log_wo_check("ERROR: Unmapped write access, addr = 0x%x", address);
		return;
	}
	map_item->memory->write_byte(address - map_item->start_address + map_item->offset, byte);
}

uint8_t MemoryController::read_byte(uint16_t address) {
	log(MAX_LOG_LEVEL, "read_byte, addr = 0x%x", address);
	MapItem *map_item = find_memory(address);
	if(map_item == NULL){
		log_wo_check("ERROR: Unmapped read access, addr = 0x%x", address);
		return 0xFF;
	}
	map_item->memory->read_byte(address - map_item->start_address + map_item->offset);
}


