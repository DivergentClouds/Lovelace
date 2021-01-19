#include "cpu.h"

// definitions
uint8_t interrupting = 0;

uint8_t instruction;
uint8_t stage;
uint8_t hold[2];

registers_t registers;
cpu_pins_t cpu_pins;

void do_cpu_cycle() {

	if (stage == 0) {
		// printf("PC: 0x%x\n", registers.pc);
		// printf("instruction: %x, reset: %d, interrupt: %d, mask flag: %d\n", instruction, cpu_pins.reset, cpu_pins.interrupt, (registers.flags & 0b00100000));
		// if (registers.sp > 0) {
		// 	printf("PC: 0x%x, instruction: 0x%x\n", registers.pc, instruction);
		// }
		if (cpu_pins.reset) {
			do_reset();
			cpu_pins.reset = 0;
		} else if (cpu_pins.interrupt && !(registers.flags & 0b00100000)) {
			cpu_pins.interrupt = 0;
			interrupting = 1;
			// printf("keyboard_interrupted = %d\n", keyboard_interrupted);
		} else {
			instruction = cpu_pins.data;
		}
	}

    // printf("instruction: %d, interrupting: %d, stage: %d\n", instruction, interrupting, stage);

	if (interrupting) {
		do_interrupt();
	} else {
		// printf("instruction: %x\n", instruction);
		// printf("program counter: %x\n", registers.pc);
		// if (stage == 0)
			// printf("instruction: 0x%x, program counter: 0x%x\n", instruction, registers.pc);
		switch (instruction) {
		case NOOP:
			registers.pc++;
			break;
		case STORE_IND_R0:
			do_store_ind(registers.r[0]);
			break;
		case STORE_IND_R1:
			do_store_ind(registers.r[1]);
			break;
		case STORE_IND_R2:
			do_store_ind(registers.r[2]);
			break;
		case STORE_IND_R3:
			do_store_ind(registers.r[3]);
			break;
		case STORE_IND_ACC:
			do_store_ind(registers.acc);
			break;
		case STORE_IND_ZP_R0:
			do_store_ind_zp(registers.r[0]);
			break;
		case STORE_IND_ZP_R1:
			do_store_ind_zp(registers.r[1]);
			break;
		case STORE_IND_ZP_R2:
			do_store_ind_zp(registers.r[2]);
			break;
		case STORE_IND_ZP_R3:
			do_store_ind_zp(registers.r[3]);
			break;
		case STORE_IND_ZP_ACC:
			do_store_ind_zp(registers.acc);
			break;
		case STORE_LIT:
			switch (stage) {
				case 0:
					cpu_pins.rw = 1;
					cpu_pins.address = registers.pc + 1;
					stage++;
					break;
				case 1:
					hold[0] = cpu_pins.data; // literal
					cpu_pins.rw = 1;
					cpu_pins.address = registers.pc + 2;
					stage++;
					break;
				case 2:
					hold[1] = cpu_pins.data; // top of address
					cpu_pins.rw = 1;
					cpu_pins.address = registers.pc + 3;
					stage++;
					break;
				case 3:
					cpu_pins.address = (hold[1] << 8) | cpu_pins.data;
					cpu_pins.data = hold[0];
					cpu_pins.rw = 0;
					stage++;
					break;
				case 4:
					registers.pc += 4;
					stage = 0;
					break;
			}
			break;
		case STORE_ZP_LIT:
			switch (stage) {
				case 0:
					cpu_pins.rw = 1;
					cpu_pins.address = registers.pc + 1;
					stage++;
					break;
				case 1:
					hold[0] = cpu_pins.data; // literal
					cpu_pins.rw = 1;
					cpu_pins.address = registers.pc + 2;
					stage++;
					break;
				case 2:
					cpu_pins.address = cpu_pins.data;
					cpu_pins.data = hold[0];
					cpu_pins.rw = 0;
					stage++;
					break;
				case 3:
					registers.pc += 3;
					stage = 0;
					break;
			}
			break;
		case STORE_R0:
			do_store(registers.r[0]);
			break;
		case STORE_R1:
			do_store(registers.r[1]);
			break;
		case STORE_R2:
			do_store(registers.r[2]);
			break;
		case STORE_R3:
			do_store(registers.r[3]);
			break;
		case STORE_ACC:
			do_store(registers.acc);
			break;
		case STORE_ZP_R0:
			do_store_zp(registers.r[0]);
			break;
		case STORE_ZP_R1:
			do_store_zp(registers.r[1]);
			break;
		case STORE_ZP_R2:
			do_store_zp(registers.r[2]);
			break;
		case STORE_ZP_R3:
			do_store_zp(registers.r[3]);
			break;
		case STORE_ZP_ACC:
			do_store_zp(registers.acc);
			break;
		case LOAD_IND_R0:
			do_load_ind(&registers.r[0]);
			break;
		case LOAD_IND_R1:
			do_load_ind(&registers.r[1]);
			break;
		case LOAD_IND_R2:
			do_load_ind(&registers.r[2]);
			break;
		case LOAD_IND_R3:
			do_load_ind(&registers.r[3]);
			break;
		case LOAD_IND_ACC:
			do_load_ind(&registers.acc);
			break;
		case LOAD_IND_ZP_R0:
			do_load_ind_zp(&registers.r[0]);
			break;
		case LOAD_IND_ZP_R1:
			do_load_ind_zp(&registers.r[1]);
			break;
		case LOAD_IND_ZP_R2:
			do_load_ind_zp(&registers.r[2]);
			break;
		case LOAD_IND_ZP_R3:
			do_load_ind_zp(&registers.r[3]);
			break;
		case LOAD_IND_ZP_ACC:
			do_load_ind_zp(&registers.acc);
			break;
		case LOAD_R0:
			do_load(&registers.r[0]);
			break;
		case LOAD_R1:
			do_load(&registers.r[1]);
			break;
		case LOAD_R2:
			do_load(&registers.r[2]);
			break;
		case LOAD_R3:
			do_load(&registers.r[3]);
			break;
		case LOAD_ACC:
			do_load(&registers.acc);
			break;
		case LOAD_ZP_R0:
			do_load_zp(&registers.r[0]);
			break;
		case LOAD_ZP_R1:
			do_load_zp(&registers.r[1]);
			break;
		case LOAD_ZP_R2:
			do_load_zp(&registers.r[2]);
			break;
		case LOAD_ZP_R3:
			do_load_zp(&registers.r[3]);
			break;
		case LOAD_ZP_ACC:
			do_load_zp(&registers.acc);
			break;
		case LOAD_LIT_R0:
			do_load_lit(&registers.r[0]);
			break;
		case LOAD_LIT_R1:
			do_load_lit(&registers.r[1]);
			break;
		case LOAD_LIT_R2:
			do_load_lit(&registers.r[2]);
			break;
		case LOAD_LIT_R3:
			do_load_lit(&registers.r[3]);
			break;
		case LOAD_LIT_ACC:
			do_load_lit(&registers.acc);
			break;
		case TRANS_R0_R1:
			registers.r[1] = registers.r[0];
			registers.pc++;
			break;
		case TRANS_R0_R2:
			registers.r[2] = registers.r[0];
			registers.pc++;
			break;
		case TRANS_R0_R3:
			registers.r[3] = registers.r[0];
			registers.pc++;
			break;
		case TRANS_R0_ACC:
			registers.acc = registers.r[0];
			registers.pc++;
			break;
		case TRANS_R1_R0:
			registers.r[0] = registers.r[1];
			registers.pc++;
			break;
		case TRANS_R1_R2:
			registers.r[2] = registers.r[1];
			registers.pc++;
			break;
		case TRANS_R1_R3:
			registers.r[3] = registers.r[1];
			registers.pc++;
			break;
		case TRANS_R1_ACC:
			registers.acc = registers.r[1];
			registers.pc++;
			break;
		case TRANS_R2_R0:
			registers.r[0] = registers.r[2];
			registers.pc++;
			break;
		case TRANS_R2_R1:
			registers.r[1] = registers.r[2];
			registers.pc++;
			break;
		case TRANS_R2_R3:
			registers.r[3] = registers.r[2];
			registers.pc++;
			break;
		case TRANS_R2_ACC:
			registers.acc = registers.r[2];
			registers.pc++;
			break;
		case TRANS_R3_R0:
			registers.r[0] = registers.r[3];
			registers.pc++;
			break;
		case TRANS_R3_R1:
			registers.r[1] = registers.r[3];
			registers.pc++;
			break;
		case TRANS_R3_R2:
			registers.r[2] = registers.r[3];
			registers.pc++;
			break;
		case TRANS_R3_ACC:
			registers.acc = registers.r[3];
			registers.pc++;
			break;
		case TRANS_ACC_R0:
			registers.acc = registers.r[0];
			registers.pc++;
			break;
		case TRANS_ACC_R1:
			registers.acc = registers.r[1];
			registers.pc++;
			break;
		case TRANS_ACC_R2:
			registers.acc = registers.r[2];
			registers.pc++;
			break;
		case TRANS_ACC_R3:
			registers.acc = registers.r[3];
			registers.pc++;
			break;
		case TRANS_SP_R0:
			registers.r[0] = registers.sp;
			registers.pc++;
			break;
		case TRANS_SP_R1:
			registers.r[1] = registers.sp;
			registers.pc++;
			break;
		case TRANS_SP_R2:
			registers.r[2] = registers.sp;
			registers.pc++;
			break;
		case TRANS_SP_R3:
			registers.r[3] = registers.sp;
			registers.pc++;
			break;
		case TRANS_SP_ACC:
			registers.acc = registers.sp;
			registers.pc++;
			break;
		case TRANS_FLAGS_R0:
			registers.r[0] = registers.flags;
			registers.pc++;
			break;
		case TRANS_FLAGS_R1:
			registers.r[1] = registers.flags;
			registers.pc++;
			break;
		case TRANS_FLAGS_R2:
			registers.r[2] = registers.flags;
			registers.pc++;
			break;
		case TRANS_FLAGS_R3:
			registers.r[3] = registers.flags;
			registers.pc++;
			break;
		case TRANS_FLAGS_ACC:
			registers.acc = registers.flags;
			registers.pc++;
			break;
		case ADD_LIT:
			switch (stage) {
				case 0:
					cpu_pins.rw = 1;
					cpu_pins.address = registers.pc + 1;
					stage++;
					break;
				case 1:
					do_add(cpu_pins.data);
					stage = 0;
					registers.pc += 2;
					break;
			}
			break;
		case ADDC_LIT:
			switch (stage) {
				case 0:
					cpu_pins.rw = 1;
					cpu_pins.address = registers.pc + 1;
					stage++;
					break;
				case 1:
					do_addc(cpu_pins.data);
					stage = 0;
					registers.pc += 2;
					break;
			}
			break;
		case ADD_R0:
			do_add(registers.r[0]);
			registers.pc++;
			break;
		case ADD_R1:
			do_add(registers.r[1]);
			registers.pc++;
			break;
		case ADD_R2:
			do_add(registers.r[2]);
			registers.pc++;
			break;
		case ADD_R3:
			do_add(registers.r[3]);
			registers.pc++;
			break;
		case ADD_ACC:
			do_add(registers.acc);
			registers.pc++;
			break;
		case ADDC_R0:
			do_addc(registers.r[0]);
			registers.pc++;
			break;
		case ADDC_R1:
			do_addc(registers.r[1]);
			registers.pc++;
			break;
		case ADDC_R2:
			do_addc(registers.r[2]);
			registers.pc++;
			break;
		case ADDC_R3:
			do_addc(registers.r[3]);
			registers.pc++;
			break;
		case ADDC_ACC:
			do_addc(registers.acc);
			registers.pc++;
			break;
		case SUB_LIT:
			switch (stage) {
				case 0:
					cpu_pins.rw = 1;
					cpu_pins.address = registers.pc + 1;
					stage++;
					break;
				case 1:
					do_sub(cpu_pins.data);
					stage = 0;
					registers.pc += 2;
					break;
			}
			break;
		case SUBC_LIT:
			switch (stage) {
				case 0:
					cpu_pins.rw = 1;
					cpu_pins.address = registers.pc + 1;
					stage++;
					break;
				case 1:
					do_subc(cpu_pins.data);
					stage = 0;
					registers.pc += 2;
					break;
			}
			break;
		case SUB_R0:
			do_sub(registers.r[0]);
			registers.pc++;
			break;
		case SUB_R1:
			do_sub(registers.r[1]);
			registers.pc++;
			break;
		case SUB_R2:
			do_sub(registers.r[2]);
			registers.pc++;
			break;
		case SUB_R3:
			do_sub(registers.r[3]);
			registers.pc++;
			break;
		case SUBC_R0:
			do_subc(registers.r[0]);
			registers.pc++;
			break;
		case SUBC_R1:
			do_subc(registers.r[1]);
			registers.pc++;
			break;
		case SUBC_R2:
			do_subc(registers.r[2]);
			registers.pc++;
			break;
		case SUBC_R3:
			do_subc(registers.r[3]);
			registers.pc++;
			break;
		case SHR_LIT:
			switch (stage) {
				case 0:
					cpu_pins.rw = 1;
					cpu_pins.address = registers.pc + 1;
					stage++;
					break;
				case 1:
					registers.acc >>= cpu_pins.data;
					set_zero_and_sign();
					stage = 0;
					registers.pc += 2;
					break;
			}
			break;
		case SHR_R0:
			registers.acc >>= registers.r[0];
			set_zero_and_sign();
			registers.pc++;
			break;
		case SHR_R1:
			registers.acc >>= registers.r[1];
			set_zero_and_sign();
			registers.pc++;
			break;
		case SHR_R2:
			registers.acc >>= registers.r[2];
			set_zero_and_sign();
			registers.pc++;
			break;
		case SHR_R3:
			registers.acc >>= registers.r[3];
			set_zero_and_sign();
			registers.pc++;
			break;
		case SHR_ACC:
			registers.acc >>= registers.acc;
			set_zero_and_sign();
			registers.pc++;
			break;
		case SHL_LIT:
			switch (stage) {
				case 0:
					cpu_pins.rw = 1;
					cpu_pins.address = registers.pc + 1;
					stage++;
					break;
				case 1:
					registers.acc <<= cpu_pins.data;
					set_zero_and_sign();
					stage = 0;
					registers.pc += 2;
					break;
			}
			break;
		case SHL_R0:
			registers.acc <<= registers.r[0];
			set_zero_and_sign();
			registers.pc++;
			break;
		case SHL_R1:
			registers.acc <<= registers.r[1];
			set_zero_and_sign();
			registers.pc++;
			break;
		case SHL_R2:
			registers.acc <<= registers.r[2];
			set_zero_and_sign();
			registers.pc++;
			break;
		case SHL_R3:
			registers.acc <<= registers.r[3];
			set_zero_and_sign();
			registers.pc++;
			break;
		case SHL_ACC:
			registers.acc <<= registers.acc;
			set_zero_and_sign();
			registers.pc++;
			break;
		case AND_R0:
			registers.acc &= registers.r[0];
			set_zero_and_sign();
			registers.pc++;
			break;
		case AND_R1:
			registers.acc &= registers.r[1];
			set_zero_and_sign();
			registers.pc++;
			break;
		case AND_R2:
			registers.acc &= registers.r[2];
			set_zero_and_sign();
			registers.pc++;
			break;
		case AND_R3:
			registers.acc &= registers.r[3];
			set_zero_and_sign();
			registers.pc++;
			break;
		case AND_LIT:
			switch (stage) {
				case 0:
					cpu_pins.rw = 1;
					cpu_pins.address = registers.pc + 1;
					stage++;
					break;
				case 1:
					registers.acc &= cpu_pins.data;
					set_zero_and_sign();
					stage = 0;
					registers.pc += 2;
					break;
			}
			break;
		case OR_R0:
			registers.acc |= registers.r[0];
			set_zero_and_sign();
			registers.pc++;
			break;
		case OR_R1:
			registers.acc |= registers.r[1];
			set_zero_and_sign();
			registers.pc++;
			break;
		case OR_R2:
			registers.acc |= registers.r[2];
			set_zero_and_sign();
			registers.pc++;
			break;
		case OR_R3:
			registers.acc |= registers.r[3];
			set_zero_and_sign();
			registers.pc++;
			break;
		case OR_LIT:
			switch (stage) {
				case 0:
					cpu_pins.rw = 1;
					cpu_pins.address = registers.pc + 1;
					stage++;
					break;
				case 1:
					registers.acc |= cpu_pins.data;
					set_zero_and_sign();
					stage = 0;
					registers.pc += 2;
					break;
			}
			break;
		case XOR_R0:
			registers.acc ^= registers.r[0];
			set_zero_and_sign();
			registers.pc++;
			break;
		case XOR_R1:
			registers.acc ^= registers.r[1];
			set_zero_and_sign();
			registers.pc++;
			break;
		case XOR_R2:
			registers.acc ^= registers.r[2];
			set_zero_and_sign();
			registers.pc++;
			break;
		case XOR_R3:
			registers.acc ^= registers.r[3];
			set_zero_and_sign();
			registers.pc++;
			break;
		case XOR_LIT:
			switch (stage) {
				case 0:
					cpu_pins.rw = 1;
					cpu_pins.address = registers.pc + 1;
					stage++;
					break;
				case 1:
					registers.acc ^= cpu_pins.data;
					set_zero_and_sign();
					stage = 0;
					registers.pc += 2;
					break;
			}
			break;
		case NOT_0:
			registers.acc = ~registers.acc;
			set_zero_and_sign();
			registers.pc++;
			break;
		case INC_R0:
			do_inc(0);
			registers.pc++;
			break;
		case INC_R1:
			do_inc(1);
			registers.pc++;
			break;
		case INC_R2:
			do_inc(2);
			registers.pc++;
			break;
		case INC_R3:
			do_inc(3);
			registers.pc++;
			break;
		case INC_ACC:
			do_add(1);
			registers.pc++;
			break;
		case DEC_R0:
			do_dec(0);
			registers.pc++;
			break;
		case DEC_R1:
			do_dec(1);
			registers.pc++;
			break;
		case DEC_R2:
			do_dec(2);
			registers.pc++;
			break;
		case DEC_R3:
			do_dec(3);
			registers.pc++;
			 // // printf("R3 = 0x%x\n", registers.r[3]);
			break;
		case DEC_ACC:
			do_sub(1);
			registers.pc++;
			break;
		case JSR_0:
			switch (stage) {
				case 0:
					cpu_pins.rw = 0;
					cpu_pins.data = (registers.pc + 3) >> 8;
					registers.sp++;
					cpu_pins.address = 0x100 | registers.sp;
					stage++;
					break;
				case 1:
					cpu_pins.rw = 0;
					cpu_pins.data = registers.pc + 3;
					registers.sp++;
					cpu_pins.address = 0x100 | registers.sp;
					stage++;
					break;
				case 2:
					cpu_pins.rw = 1;
					cpu_pins.address = registers.pc + 1;
					stage++;
					break;
				case 3:
					cpu_pins.rw = 1;
					cpu_pins.address = registers.pc + 2;
					registers.pc = ((uint16_t) cpu_pins.data) << 8;
					stage++;
					break;
				case 4:
					registers.pc |= cpu_pins.data;
					// // printf("JSR PC = 0x%x\n", registers.pc);
					stage = 0;
					break;
			}
			break;
		case JSRI_0:
			switch (stage) {
				case 0:
					cpu_pins.rw = 0;
					cpu_pins.data = (registers.pc + 3) >> 8;
					registers.sp++;
					cpu_pins.address = 0x100 | registers.sp;
					stage++;
					break;
				case 1:
					cpu_pins.rw = 0;
					cpu_pins.data = registers.pc + 3;
					registers.sp++;
					cpu_pins.address = 0x100 | registers.sp;
					stage++;
					break;
				case 2:
					cpu_pins.rw = 1;
					cpu_pins.address = registers.pc + 1;
					stage++;
					break;
				case 3:
					hold[0] = cpu_pins.data;
					cpu_pins.rw = 1;
					cpu_pins.address++;
					stage++;
					break;
				case 4:
					cpu_pins.rw = 1;
					cpu_pins.address = ((uint16_t) hold[0] << 8) | cpu_pins.data;
					stage++;
					break;
				case 5:
					cpu_pins.rw = 1;
					cpu_pins.address++;
					registers.pc = ((uint16_t) cpu_pins.data) << 8;
					stage++;
					break;
				case 6:
					registers.pc |= cpu_pins.data;
					// // printf("JSR PC = 0x%x\n", registers.pc);
					stage = 0;
					break;
			}
			break;
		case RET_0:
			switch (stage) {
				case 0:
					cpu_pins.rw = 1;
					cpu_pins.address = 0x100 | registers.sp;
					registers.sp--;
					stage++;
					break;
				case 1:
					cpu_pins.rw = 1;
					registers.pc = cpu_pins.data;
					// // printf("RET PC MSB = 0x%x\n\n", registers.pc);
					cpu_pins.address = 0x100 | registers.sp;
					registers.sp--;
					stage++;
					break;
				case 2:
					registers.pc |= ((uint16_t) cpu_pins.data) << 8;
					stage = 0;
					// printf("RET PC = 0x%x\n\n", registers.pc);
					break;
			}
			break;
		case RETI_0:
			switch (stage) {
				case 0:
					// printf("instruction: 0x%x, program counter: 0x%x\n", instruction, registers.pc);
					cpu_pins.rw = 1;
					cpu_pins.address = 0x100 | registers.sp;
					// printf("sp = 0x%x", registers.sp);
					registers.sp--;
					stage++;
					break;
				case 1:
					cpu_pins.rw = 1;
					registers.pc = cpu_pins.data;
					cpu_pins.address = 0x100 | registers.sp;
					registers.sp--;
					stage++;
					break;
				case 2:
					cpu_pins.rw = 1;
					registers.pc |= ((uint16_t) cpu_pins.data) << 8;
					cpu_pins.address = 0x100 | registers.sp;
					registers.sp--;
					stage++;
					break;
				case 3:
					// printf("instruction: 0x%x, program counter: 0x%x, sp: %d\n", instruction, registers.pc, registers.sp);
					registers.flags = cpu_pins.data;
					stage = 0;
					break; // interrupts push an already incremented address
			}
			break;
		case PUSH_R0:
			do_push(registers.r[0]);
			break;
		case PUSH_R1:
			do_push(registers.r[1]);
			break;
		case PUSH_R2:
			do_push(registers.r[2]);
			break;
		case PUSH_R3:
			do_push(registers.r[3]);
			break;
		case PUSH_ACC:
			do_push(registers.acc);
			break;
		case PUSH_LIT:
			switch (stage) {
				case 0:
					cpu_pins.rw = 1;
					cpu_pins.address = registers.pc + 1;
					stage++;
					break;
				case 1:
					cpu_pins.rw = 0;
					registers.sp++;
					cpu_pins.address = 0x100 | registers.sp;
					stage++;
					break;
				case 2:
					// Time for writing to stack
					registers.pc += 2;
					// // printf("PUSH STACK = 0x%x\n", global_memory[0x100 | registers.sp]);
					stage = 0;
					break;
			}
			break;
		case POP_R0:
			do_pop(&registers.r[0]);
			break;
		case POP_R1:
			do_pop(&registers.r[1]);
			break;
		case POP_R2:
			do_pop(&registers.r[2]);
			break;
		case POP_R3:
			do_pop(&registers.r[3]);
			break;
		case POP_ACC:
			do_pop(&registers.acc);
			break;
		case DROP_0:
			registers.sp--;
			registers.pc++;
			break;
		case CMP_R0_R1:
			do_compare(registers.r[0], registers.r[1]);
			registers.pc++;
			break;
		case CMP_R0_R2:
			do_compare(registers.r[0], registers.r[2]);
			registers.pc++;
			break;
		case CMP_R0_R3:
			do_compare(registers.r[0], registers.r[3]);
			registers.pc++;
			break;
		case CMP_R0_ACC:
			do_compare(registers.r[0], registers.acc);
			registers.pc++;
			break;
		case CMP_R1_R0:
			do_compare(registers.r[1], registers.r[0]);
			registers.pc++;
			break;
		case CMP_R1_R2:
			do_compare(registers.r[1], registers.r[2]);
			registers.pc++;
			break;
		case CMP_R1_R3:
			do_compare(registers.r[1], registers.r[3]);
			registers.pc++;
			break;
		case CMP_R1_ACC:
			do_compare(registers.r[1], registers.acc);
			registers.pc++;
			break;
		case CMP_R2_R0:
			do_compare(registers.r[2], registers.r[0]);
			registers.pc++;
			break;
		case CMP_R2_R1:
			do_compare(registers.r[2], registers.r[1]);
			registers.pc++;
			break;
		case CMP_R2_R3:
			do_compare(registers.r[2], registers.r[3]);
			registers.pc++;
			break;
		case CMP_R2_ACC:
			do_compare(registers.r[2], registers.acc);
			registers.pc++;
			break;
		case CMP_R3_R0:
			do_compare(registers.r[3], registers.r[0]);
			registers.pc++;
			break;
		case CMP_R3_R1:
			do_compare(registers.r[3], registers.r[1]);
			registers.pc++;
			break;
		case CMP_R3_R2:
			do_compare(registers.r[3], registers.r[2]);
			registers.pc++;
			break;
		case CMP_R3_ACC:
			do_compare(registers.r[3], registers.acc);
			registers.pc++;
			break;
		case CMP_ACC_R0:
			do_compare(registers.acc, registers.r[0]);
			registers.pc++;
			break;
		case CMP_ACC_R1:
			do_compare(registers.acc, registers.r[1]);
			registers.pc++;
			break;
		case CMP_ACC_R2:
			do_compare(registers.acc, registers.r[2]);
			registers.pc++;
			break;
		case CMP_ACC_R3:
			do_compare(registers.acc, registers.r[3]);
			registers.pc++;
			break;
		case CMP_R0_LIT:
			do_compare_lit(registers.r[0]);
			break;
		case CMP_R1_LIT:
			do_compare_lit(registers.r[1]);
			break;
		case CMP_R2_LIT:
			do_compare_lit(registers.r[2]);
			break;
		case CMP_R3_LIT:
			do_compare_lit(registers.r[3]);
			break;
		case CMP_ACC_LIT:
			do_compare_lit(registers.acc);
			break;
		case BRA_S:
			do_bra(0b10000000);
			break;
		case BRA_C:
			do_bra(0b01000000);
			break;
		case BRA_I:
			do_bra(0b00100000);
			break;
		case BRA_O:
			do_bra(0b00010000);
			break;
		case BRA_G:
			do_bra(0b00000010);
			break;
		case BRA_Z:
			do_bra(0b00000001);
			break;
		case BRAN_S:
			do_bran(0b10000000);
			break;
		case BRAN_C:
			do_bran(0b01000000);
			break;
		case BRAN_I:
			do_bran(0b00100000);
			break;
		case BRAN_O:
			do_bran(0b00010000);
			break;
		case BRAN_G:
			do_bran(0b00000010);
			break;
		case BRAN_Z:
			// printf("R0: 0x%x\n", registers.r[0]);
			do_bran(0b00000001);
			break;
		case JMP_0:
			switch (stage) {
				case 0:
					cpu_pins.rw = 1;
					cpu_pins.address = registers.pc + 1;
					stage++;
					break;
				case 1:
					cpu_pins.address = registers.pc + 2;
					registers.pc = ((uint16_t) cpu_pins.data) << 8;
					cpu_pins.rw = 1;
					stage++;
					break;
				case 2:
					registers.pc |= cpu_pins.data;
					stage = 0;
					// printf("0x%x\n",registers.pc);
					break;
			}
			break;
		case SET_S:
			registers.flags |= 0b10000000;
			registers.pc++;
			break;
		case SET_C:
			registers.flags |= 0b01000001;
			registers.pc++;
			break;
		case SET_I:
			registers.flags |= 0b00100000;
			registers.pc++;
			break;
		case SET_O:
			registers.flags |= 0b00010000;
			registers.pc++;
			break;
		case SET_G:
			registers.flags |= 0b00000010;
			registers.pc++;
			break;
		case SET_Z:
			registers.flags |= 0b00000001;
			registers.pc++;
			break;
		case CLEAR_S:
			registers.flags &= 0b01111111;
			registers.pc++;
			break;
		case CLEAR_C:
			registers.pc++;
			registers.flags &= 0b10111111;
			break;
		case CLEAR_I:
			registers.flags &= 0b11011111;
			registers.pc++;
			break;
		case CLEAR_O:
			registers.flags &= 0b11101111;
			registers.pc++;
			break;
		case CLEAR_G:
			registers.flags &= 0b11111101;
			registers.pc++;
			break;
		case CLEAR_Z:
			registers.flags &= 0b11111110;
			registers.pc++;
			break;
		default: // switch to fault
			if (should_close == 0) {
				printf("\n");
				printf("instruction = 0x%x\n", instruction);
				printf("address = 0x%x\n", cpu_pins.address);
				printf("data = 0x%x\n", cpu_pins.data);
				printf("\nregisters:\n");
				printf("acc = 0x%x\n", registers.acc);
				printf("r0 = 0x%x\n", registers.r[0]);
				printf("r1 = 0x%x\n", registers.r[1]);
				printf("r2 = 0x%x\n", registers.r[2]);
				printf("r3 = 0x%x\n", registers.r[3]);
				printf("flags = 0x%x\n", registers.flags);
				printf("stack pointer = 0x%x\n", registers.sp);
				printf("program counter = 0x%x\n", registers.pc);
				printf("\nstack:\n");
				while (registers.sp--) {
					printf("%d: 0x%x\n", registers.sp, global_memory[0x100 | registers.sp]);
				}
				printf("\n");
			}
			should_close = 1;
			stage = 1;
			break;
		}
	}

	if (stage == 0) {
		cpu_pins.rw = 1;
		cpu_pins.address = registers.pc;

		// // printf("\nPC = 0x%x\n", registers.pc);
		// // printf("OP = 0x%x\n", instruction);
		// // printf("R0 = 0x%x\n", registers.r[0]);
		// // printf("R1 = 0x%x\n", registers.r[1]);
	}
}

void do_compare(uint8_t a, uint8_t b) {
	if (a == b) {
		registers.flags |= 0b00000001;
	} else {
		registers.flags &= 0b11111110;
	}

	if (a > b) {
		registers.flags |= 0b00000010;
	} else {
		registers.flags &= 0b11111101;
	}
}

void set_zero_and_sign() {
	if (registers.acc == 0) {
		registers.flags |= 0b00000001;
	} else {
		registers.flags &= 0b11111110;
	}

	if (registers.acc & 0b10000000) {
		registers.flags |= 0b10000000;
	} else {
		registers.flags &= 0b01111111;
	}
}

void set_zero_and_sign_value(uint8_t value) {
	if (value == 0) {
		registers.flags |= 0b00000001;
	} else {
		registers.flags &= 0b11111110;
	}

	if (value & 0b10000000) {
		registers.flags |= 0b10000000;
	} else {
		registers.flags &= 0b01111111;
	}
}

void do_inc(uint8_t reg) {
	uint8_t old = registers.r[reg];

	registers.r[reg]++;

	if (registers.r[reg] < old) {
		registers.flags |= 0b01000000;
	} else {
		registers.flags &= 0b10111111;
	}

	if (((int8_t)registers.r[reg]) < ((int8_t)old)) {
		registers.flags |= 0b00010000;
	} else {
		registers.flags &= 0b11101111;
	}

	set_zero_and_sign_value(registers.r[reg]);
}

void do_dec(uint8_t reg) {
	uint8_t old = registers.r[reg];

	registers.r[reg]--;

	if (registers.r[reg] > old) {
		registers.flags |= 0b01000000;
	} else {
		registers.flags &= 0b10111111;
	}

	if (((int8_t)registers.r[reg]) > ((int8_t)old)) {
		registers.flags |= 0b00010000;
	} else {
		registers.flags &= 0b11101111;
	}

	set_zero_and_sign_value(registers.r[reg]);
}

void do_add(uint8_t value) {
	uint8_t old = registers.acc;

	registers.acc += value;

	if (registers.acc < old) {
		registers.flags |= 0b01000000;
	} else {
		registers.flags &= 0b10111111;
	}

	if (((int8_t)registers.acc) < ((int8_t)old)) {
		registers.flags |= 0b00010000;
	} else {
		registers.flags &= 0b11101111;
	}

	set_zero_and_sign();
}

void do_addc(uint8_t value) {
	uint8_t old = registers.acc;

	registers.acc += value;

	if (registers.flags & 0b01000000) {
		registers.acc++;
	}

	if (registers.acc < old) {
		registers.flags |= 0b01000000;
	} else {
		registers.flags &= 0b10111111;
	}

	if (((int8_t)registers.acc) < ((int8_t)old)) {
		registers.flags |= 0b00010000;
	} else {
		registers.flags &= 0b11101111;
	}

	set_zero_and_sign();
}

void do_sub(uint8_t value) {
	uint8_t old = registers.acc;

	registers.acc -= value;

	if (registers.acc > old) {
		registers.flags |= 0b01000000;
	} else {
		registers.flags &= 0b10111111;
	}

	if (((int8_t)registers.acc) > ((int8_t)old)) {
		registers.flags |= 0b00010000;
	} else {
		registers.flags &= 0b11101111;
	}

	set_zero_and_sign();
}

void do_subc(uint8_t value) {
	uint8_t old = registers.acc;

	registers.acc -= value;

	if (registers.flags & 0b01000000) {
		registers.acc--;
	}

	if (registers.acc > old) {
		registers.flags |= 0b01000000;
	} else {
		registers.flags &= 0b10111111;
	}

	if (((int8_t)registers.acc) > ((int8_t)old)) {
		registers.flags |= 0b00010000;
	} else {
		registers.flags &= 0b11101111;
	}

	set_zero_and_sign();
}

void do_load(uint8_t *data) {
	switch (stage) {
		case 0:
			cpu_pins.rw = 1;
			cpu_pins.address = registers.pc + 1;
			stage++;
			break;
		case 1:
			hold[0] = cpu_pins.data;
			cpu_pins.rw = 1;
			cpu_pins.address = registers.pc + 2;
			stage++;
			break;
		case 2:
			cpu_pins.rw = 1;
			cpu_pins.address = ((uint16_t) hold[0] << 8) | cpu_pins.data;
			stage++;
			break;
		case 3:
			*data = cpu_pins.data;
			stage = 0;
			registers.pc += 3;
			break;
	}
}

void do_load_zp(uint8_t *data) {
	switch (stage) {
		case 0:
			cpu_pins.rw = 1;
			cpu_pins.address = registers.pc + 1;
			stage++;
			break;
		case 1:
			cpu_pins.rw = 1;
			cpu_pins.address = cpu_pins.data;
			stage++;
			break;
		case 2:
			*data = cpu_pins.data;
			stage = 0;
			registers.pc += 2;
			break;
	}
}

void do_load_lit(uint8_t *data) {
	switch (stage) {
		case 0:
			cpu_pins.rw = 1;
			cpu_pins.address = registers.pc + 1;
			stage++;
			break;
		case 1:
			*data = cpu_pins.data;
			stage = 0;
			registers.pc += 2;
			break;
	}
}

void do_load_ind(uint8_t *data) {
	switch (stage) {
		case 0:
			cpu_pins.rw = 1;
			cpu_pins.address = registers.pc + 1;
			stage++;
			break;
		case 1:
			hold[0] = cpu_pins.data;
			cpu_pins.rw = 1;
			cpu_pins.address = registers.pc + 2;
			stage++;
			break;
		case 2:
			cpu_pins.rw = 1;
			cpu_pins.address = ((uint16_t) hold[0] << 8) | cpu_pins.data;
			stage++;
			break;
		case 3:
			hold[0] = cpu_pins.data;
			cpu_pins.rw = 1;
			cpu_pins.address++;
			stage++;
			break;
		case 4:
			cpu_pins.rw = 1;
			cpu_pins.address = ((uint16_t) hold[0] << 8) | cpu_pins.data;
			stage++;
			break;
		case 5:
			stage = 0;
			*data = cpu_pins.data;
			registers.pc += 2;
			break;
	}
}

void do_load_ind_zp(uint8_t *data) {
	switch (stage) {
		case 0:
			cpu_pins.rw = 1;
			cpu_pins.address = registers.pc + 1;
			stage++;
			break;
		case 1:
			cpu_pins.rw = 1;
			cpu_pins.address = cpu_pins.data;
			stage++;
			break;
		case 2:
			cpu_pins.rw = 1;
			hold[0] = cpu_pins.data;
			// printf("hold[0] = 0x%x\n", hold[0]);
			cpu_pins.address++;
			stage++;
			break;
		case 3:
			cpu_pins.rw = 1;
			cpu_pins.address = ((uint16_t) hold[0] << 8) | cpu_pins.data;
			stage++;
			break;
		case 4:
			stage = 0;
			*data = cpu_pins.data;
			registers.pc += 2;
			break;
	}
}

void do_store(uint8_t data) {
	switch (stage) {
		case 0:
			cpu_pins.rw = 1;
			cpu_pins.address = registers.pc + 1;
			stage++;
			break;
		case 1:
			hold[0] = cpu_pins.data;
			cpu_pins.rw = 1;
			cpu_pins.address = registers.pc + 2;
			stage++;
			break;
		case 2:
			cpu_pins.rw = 0;
			cpu_pins.address = ((uint16_t) hold[0] << 8) | cpu_pins.data;
			cpu_pins.data = data;
			stage++;
			break;
		case 3:
			stage = 0;
			registers.pc += 3;
			break;
	}
}

void do_store_zp(uint8_t data) {
	switch (stage) {
		case 0:
			cpu_pins.rw = 1;
			cpu_pins.address = registers.pc + 1;
			stage++;
			break;
		case 1:
			cpu_pins.rw = 0;
			cpu_pins.address = cpu_pins.data;
			cpu_pins.data = data;
			stage++;
			break;
		case 2:
			stage = 0;
			registers.pc += 2;
			break;
	}
}

void do_store_ind(uint8_t data) {
	switch (stage) {
		case 0:
			cpu_pins.rw = 1;
			cpu_pins.address = registers.pc + 1;
			stage++;
			break;
		case 1:
			hold[0] = cpu_pins.data;
			cpu_pins.rw = 1;
			cpu_pins.address = registers.pc + 2;
			stage++;
			break;
		case 2:
			cpu_pins.rw = 1;
			cpu_pins.address = ((uint16_t) hold[0] << 8) | cpu_pins.data;
			stage++;
			break;
		case 3:
			hold[0] = cpu_pins.data;
			cpu_pins.rw = 1;
			cpu_pins.address++;
			stage++;
			break;
		case 4:
			cpu_pins.rw = 0;
			cpu_pins.address = ((uint16_t) hold[0] << 8) | cpu_pins.data;
			cpu_pins.data = data;
			stage++;
			break;
		case 5:
			stage = 0;
			registers.pc += 2;
			break;
	}
}

void do_store_ind_zp(uint8_t data) {
	switch (stage) {
		case 0:
			cpu_pins.rw = 1;
			cpu_pins.address = registers.pc + 1;
			stage++;
			break;
		case 1:
			cpu_pins.rw = 1;
			cpu_pins.address = cpu_pins.data;
			stage++;
			break;
		case 2:
			hold[0] = cpu_pins.data;
			cpu_pins.rw = 1;
			cpu_pins.address++;
			stage++;
			break;
		case 3:
			cpu_pins.rw = 0;
			cpu_pins.address = ((uint16_t) hold[0] << 8) | cpu_pins.data;
			cpu_pins.data = data;
			stage++;
			break;
		case 4:
			stage = 0;
			registers.pc += 2;
			// // printf("R1 = 0x%x\n", registers.r[1]);
			break;
	}
}

void do_push(uint8_t data) {
	switch (stage) {
		case 0:
			cpu_pins.rw = 0;
			registers.sp++;
			cpu_pins.address = 0x100 | registers.sp;
			cpu_pins.data = data;
			stage++;
			break;
		case 1:
			// Time for writing to stack
			stage = 0;
			registers.pc++;
			break;
	}
}

void do_pop(uint8_t *data) {
	switch (stage) {
		case 0:
			cpu_pins.rw = 1;
			cpu_pins.address = 0x100 | registers.sp;
			registers.sp--;
			stage++;
			break;
		case 1:
			*data = cpu_pins.data;
			stage = 0;
			registers.pc++;
			break;
	}
}

void do_bra(uint8_t mask) {
	switch (stage) {
		case 0:
			if (registers.flags & mask) {
				cpu_pins.rw = 1;
				cpu_pins.address = registers.pc + 1;
				stage++;
			} else {
				registers.pc += 3;
			}
			break;
		case 1:
			cpu_pins.rw = 1;
			cpu_pins.address = registers.pc + 2;
			registers.pc = ((uint16_t) cpu_pins.data) << 8;
			stage++;
			break;
		case 2:
			registers.pc |= cpu_pins.data;
			stage = 0;
			break;
	}
}

void do_bran(uint8_t mask) {
	switch (stage) {
		case 0:
			if (!(registers.flags & mask)) {
				cpu_pins.rw = 1;
				cpu_pins.address = registers.pc + 1;
				stage++;
			} else {
				registers.pc += 3;
			}
			break;
		case 1:
			cpu_pins.rw = 1;
			cpu_pins.address = registers.pc + 2;
			registers.pc = ((uint16_t) cpu_pins.data) << 8;
			stage++;
			break;
		case 2:
			registers.pc |= cpu_pins.data;
			stage = 0;
			break;
	}
}

void do_compare_lit(uint8_t data) {
	switch (stage) {
		case 0:
			cpu_pins.rw = 1;
			cpu_pins.address = registers.pc + 1;
			stage++;
			break;
		case 1:
			do_compare(data, cpu_pins.data);
			stage = 0;
			registers.pc += 2;
			break;
	}
}

void do_reset() {
	printf("cpu reset\n");
	registers.r[0] = 0;
	registers.r[1] = 0;
	registers.r[2] = 0;
	registers.r[3] = 0;
	registers.acc = 0;
	registers.flags = 0;
	registers.sp = 0;
	registers.pc = BANK_OFFSET;

	cpu_pins.address = 0;
	cpu_pins.data = 0;
	cpu_pins.interrupt = 0;
	cpu_pins.rw = 1;
	cpu_pins.reset = 0;

	instruction = 0x01;
	stage = 0;
}

void do_interrupt() {
	switch (stage) {
		case 0:
			cpu_pins.rw = 0;
			registers.sp++;
			cpu_pins.address = 0x100 | registers.sp;
			cpu_pins.data = registers.flags;
			stage++;
			break;
		case 1:
			cpu_pins.rw = 0;
			registers.sp++;
			cpu_pins.address = 0x100 | registers.sp;
			cpu_pins.data = registers.pc >> 8;
			stage++;
			break;
		case 2:
			cpu_pins.rw = 0;
			registers.sp++;
			cpu_pins.address = 0x100 | registers.sp;
			cpu_pins.data = registers.pc;
			stage++;
			break;
		case 3:
			registers.pc = INT_OFFSET;
			interrupting = 0;
			stage = 0;
			break;
	}
}
