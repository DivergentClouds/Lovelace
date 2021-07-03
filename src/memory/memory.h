#ifndef MEMORY_H
#define MEMORY_H

#include "../motherboard/motherboard.h"

#define BANK_OFFSET 0xB000
#define INT_OFFSET (BANK_OFFSET - 0x100)
#define PC_START 0x200

extern uint8_t bank;

extern uint8_t rom[0xF00];

extern uint8_t global_memory[0xFFFF];

extern uint8_t preload_program[INT_OFFSET - PC_START - 1]; // temp

// 0xDFFE number of device banks + rom bank
// 0xDFFF current bank number

extern uint8_t preload_ihandler[0xFD];

extern uint8_t keyboard_handler[0x100];

extern uint8_t clock_handler[0x100];

extern uint8_t audio_handler[0x100];

extern uint8_t video_handler[0x100];

extern uint8_t floppy1_handler[0x100];

extern uint8_t floppy2_handler[0x100];

void do_controller_cycle();

#endif
