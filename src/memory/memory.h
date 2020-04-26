#ifndef MEMORY_H
#define MEMORY_H

#include <inttypes.h>
#include <string.h>

uint8_t bank;

uint8_t rom[0xF00] = {
	0xe6, 0x02, 0x00,
};

uint8_t global_memory[0x0200];

uint8_t our_data[0x3DFF] = {

};

void do_controller_cycle();

#endif
