#ifndef MEMORY_H
#define MEMORY_H

#include <inttypes.h>
#include <string.h>

uint8_t bank;

uint8_t rom[0xF00] = {

};

uint8_t global_memory[0x3FFF];

void do_controller_cycle();

#endif
