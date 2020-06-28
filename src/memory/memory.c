#include "memory.h"

// definitions

uint8_t rom[0xF00] = {
	0xdb, 0x02, 0x00,
};

uint8_t preload_program[0x7DFF] = {
	0x0e, 0x03, 0x7f, 0xff, 0x0e, 0x00, 0x80, 0x02, 0x0e, 0x02, 0x80, 0x03, 0x0e, 0x00, 0x80, 0x04, 0x0e, 0x03, 0x80, 0x03, 0x0e, 0x80, 0x80, 0x04, 0x0e, 0x01, 0x80, 0x03, 0x0e, 0x64, 0x80, 0x04, 0x0e, 0x04, 0x80, 0x03, 0x0e, 0x31, 0x80, 0x04, 0x0e, 0x03, 0x7f, 0xff, 0x0e, 0x07, 0x80, 0x03, 0x0e, 0x01, 0x7f, 0xff, 0x1f, 0x80, 0x09, 0xca, 0x01, 0xd4, 0x02, 0x3f, 0xda, 0x02, 0x4a, 0x0e, 0x03, 0x7f, 0xff, 0x0e, 0x40, 0x80, 0x04, 0xdb, 0x02, 0x30, 0x0e, 0x03, 0x7f, 0xff, 0x0e, 0x00, 0x80, 0x04, 0xdb, 0x02, 0x30
};

uint8_t preload_ihandler[0xFE] = {
	0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0x1f, 0x1f, 0xfe, 0x09, 0x1f, 0xff, 0x20, 0x20, 0x00, 0xcb, 0x00, 0xd4, 0x02, 0x1a, 0xdd, 0xff, 0x00, 0x0e, 0x00, 0x20, 0x00, 0x95, 0xca, 0x01, 0xda, 0x02, 0x08, 0xac, 0xab, 0xaa, 0xa9, 0xa8
};

uint8_t keyboard_handler[0x100];
uint8_t clock_handler[0x100];
uint8_t audio_handler[0x100];
uint8_t video_handler[0x100];
uint8_t floppy1_handler[0x100];
uint8_t floppy2_handler[0x100];

uint8_t bank;
uint8_t global_memory[0xFFFF];


void do_controller_cycle() {
	if (cpu_pins.address < BANK_OFFSET - 1) {
		if (cpu_pins.rw) // read
			cpu_pins.data = global_memory[cpu_pins.address];
		else
			global_memory[cpu_pins.address] = cpu_pins.data;
	} else if (cpu_pins.address > BANK_OFFSET - 1) {
		if (cpu_pins.address >= 0xFF00) {
			if (bank == 1) {
				if (cpu_pins.rw) // read
					cpu_pins.data = keyboard_handler[cpu_pins.address - 0xFF00];
				else
					keyboard_handler[cpu_pins.address - 0xFF00] = cpu_pins.data;
			} else if (bank == 2) {
				if (cpu_pins.rw) // read
					cpu_pins.data = video_handler[cpu_pins.address - 0xFF00];
				else
					video_handler[cpu_pins.address - 0xFF00] = cpu_pins.data;
			} else if (bank == 3) {
				if (cpu_pins.rw) // read
					cpu_pins.data = audio_handler[cpu_pins.address - 0xFF00];
				else
					audio_handler[cpu_pins.address - 0xFF00] = cpu_pins.data;
			} else if (bank == 4) {
				if (cpu_pins.rw) // read
					cpu_pins.data = clock_handler[cpu_pins.address - 0xFF00];
				else
					clock_handler[cpu_pins.address - 0xFF00] = cpu_pins.data;
			} else if (bank == 5) {
				if (cpu_pins.rw) // read
					cpu_pins.data = floppy1_handler[cpu_pins.address - 0xFF00];
				else
					floppy1_handler[cpu_pins.address - 0xFF00] = cpu_pins.data;
			} else if (bank == 6) {
				if (cpu_pins.rw) // read
					cpu_pins.data = floppy2_handler[cpu_pins.address - 0xFF00];
				else
					floppy2_handler[cpu_pins.address - 0xFF00] = cpu_pins.data;
			}
		} else if (bank == 0) {
			// assume read
			if (cpu_pins.address - BANK_OFFSET < 0xF00)
				cpu_pins.data = rom[cpu_pins.address - BANK_OFFSET];
			else
				cpu_pins.data = 0;
		} else if (bank == 1) {
			// keyboard
			if (cpu_pins.address == BANK_OFFSET) {
				if (cpu_pins.rw) // read
					cpu_pins.data = keyboard_interrupted;
				else
					keyboard_interrupted = cpu_pins.data;
			} else if (cpu_pins.address - BANK_OFFSET - 1 < 57) {
				if (cpu_pins.rw) { // read
					cpu_pins.data = key_states[cpu_pins.address - BANK_OFFSET];
					// printf("R: %d\n", cpu_pins.data);
				} else {
					key_states[cpu_pins.address - BANK_OFFSET] = cpu_pins.data;
					// printf("W: %d\n", cpu_pins.data);
				}
			}
		} else if (bank == 2) {
			// video card
		} else if (bank == 3) {
			// audio
			switch (cpu_pins.address - BANK_OFFSET) {
				case 1:
					if (cpu_pins.rw) // read
						cpu_pins.data = audio_pins.reset;
					else
						audio_pins.reset = cpu_pins.data & 1;
					break;
				case 2:
					if (cpu_pins.rw) // read
						cpu_pins.data = audio_pins.osc;
					else
						audio_pins.osc = cpu_pins.data;
					break;
				case 3:
					if (cpu_pins.rw) // read
						cpu_pins.data = audio_pins.reg;
					else
						audio_pins.reg = cpu_pins.data;
					break;
				case 4:
					if (cpu_pins.rw) // read
						cpu_pins.data = audio_pins.data;
					else
						audio_pins.data = cpu_pins.data;
					break;
				case 5:
					if (cpu_pins.rw) // read
						cpu_pins.data = audio_pins.rw;
					else
						audio_pins.rw = cpu_pins.data;
					break;
			}
		} else if (bank == 4) {
			switch (cpu_pins.address - BANK_OFFSET) {
				case 0xFEFF:
					if (cpu_pins.rw) // read
						cpu_pins.data = clock_interrupted;
					else
						clock_interrupted = cpu_pins.data;
					break;
			}
		} else if (bank == 5) {
			// floppy controller 1
		} else if (bank == 6) {
			// floppy controller 2
		}
			// todo: possibly other device banks
	} else {
		if (cpu_pins.rw) // read
			cpu_pins.data = bank;
		else
			bank = cpu_pins.data;
	}
}
