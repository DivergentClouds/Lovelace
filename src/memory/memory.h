#ifndef MEMORY_H
#define MEMORY_H

#include <inttypes.h>
#include <string.h>

uint8_t bank;

uint8_t rom[0xF00] = {
	0xa2, 0x40, 0x07, 0xa2, 0x40, 0x07, 0xff, 0xa3
};

uint8_t global_memory[0x3FFF];

void do_controller_cycle();

#endif
