#include "memory.h"
#include "../cpu/cpu.h"
#include "../audio/audio.h"

void do_controller_cycle() {
	if (cpu_pins.address < 0x3FFF) {
		if (cpu_pins.rw) // read
			cpu_pins.data = global_memory[cpu_pins.address];
		else
			global_memory[cpu_pins.address] = cpu_pins.data;
	} else if (cpu_pins.address > 0x3FFF) {
		if (bank == 0) {
			// assume read and correct address
			cpu_pins.data = rom[cpu_pins.address - 0x4000];
		} else if (bank == 1) {
			// keyboard
		} else if (bank == 2) {
			// video card
		} else if (bank == 3) {
			switch (cpu_pins.address - 0x4000) {
				case 0:
					if (cpu_pins.rw) // read
						cpu_pins.data = audio_pins.reset;
					else
						audio_pins.reset = cpu_pins.data & 1;
					break;
				case 1:
					if (cpu_pins.rw) // read
						cpu_pins.data = audio_pins.osc;
					else
						audio_pins.osc = cpu_pins.data;
					break;
				case 2:
					if (cpu_pins.rw) // read
						cpu_pins.data = audio_pins.reg;
					else
						audio_pins.reg = cpu_pins.data;
					break;
				case 3:
					if (cpu_pins.rw) // read
						cpu_pins.data = audio_pins.data;
					else
						audio_pins.data = cpu_pins.data;
					break;
				case 4:
					if (cpu_pins.rw) // read
						cpu_pins.data = audio_pins.rw;
					else
						audio_pins.rw = cpu_pins.data;
					break;
			}
		} // todo: other banks
	} else {
		if (cpu_pins.rw) // read
			cpu_pins.data = bank;
		else
			bank = cpu_pins.data;
	}
}
