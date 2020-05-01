#include "memory.h"
#include "../cpu/cpu.h"
#include "../audio/audio.h"
#include "../clock/clock.h"
#include "../keyboard/keyboard.h"

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
				if (cpu_pins.rw) // read
					cpu_pins.data = key_states[cpu_pins.address - BANK_OFFSET];
				else
					key_states[cpu_pins.address - BANK_OFFSET] = cpu_pins.data;
			}
		} else if (bank == 2) {
			// video card
		} else if (bank == 3) {
			// audio
			switch (cpu_pins.address - BANK_OFFSET) {
				case 0xFEFE:
					if (cpu_pins.rw) // read
						cpu_pins.data = audio_pins.reset;
					else
						audio_pins.reset = cpu_pins.data & 1;
					break;
				case 0xFEFD:
					if (cpu_pins.rw) // read
						cpu_pins.data = audio_pins.osc;
					else
						audio_pins.osc = cpu_pins.data;
					break;
				case 0xFEFC:
					if (cpu_pins.rw) // read
						cpu_pins.data = audio_pins.reg;
					else
						audio_pins.reg = cpu_pins.data;
					break;
				case 0xFEFB:
					if (cpu_pins.rw) // read
						cpu_pins.data = audio_pins.data;
					else
						audio_pins.data = cpu_pins.data;
					break;
				case 0xFEFA:
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
