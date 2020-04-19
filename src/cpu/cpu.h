#ifndef CPU_H
#define CPU_H

#include <inttypes.h>
#include <stdio.h>

typedef struct registers_s {
	uint8_t r[4];
	uint8_t acc;
	uint16_t pc;
	uint8_t sp;
	uint8_t flags; // bitwise
} registers_t;

typedef struct pins_s {
	uint8_t reset;
	uint8_t interrupt;
	uint8_t rw;
	uint16_t address; // bitwise
	uint8_t data; // bitwise
} pins_t;

registers_t registers;
pins_t pins;

// states

uint8_t instruction;
uint8_t stage;
uint8_t temp[2]; // for load and store
uint8_t interrupting;

// misc functions

void do_compare(uint8_t a, uint8_t b);
void do_add(uint8_t value);
void do_addc(uint8_t value);
void do_sub(uint8_t value);
void do_subc(uint8_t value);

void set_zero_and_sign();
void set_zero_and_sign_value(uint8_t value);
void do_inc(uint8_t reg);
void do_dec(uint8_t reg);

void do_store(uint8_t data);
void do_store_zp(uint8_t data);

void do_load(uint8_t *data);
void do_load_zp(uint8_t *data);
void do_load_lit(uint8_t *data);

void do_push(uint8_t data);
void do_pop(uint8_t *data);

void do_bra(uint8_t mask);
void do_bran(uint8_t mask);
void do_compare_lit(uint8_t data);

// opcodes

#define NOOP 0x00

#define STORE_LIT 0x01
#define STORE_ZP_LIT 0x02
#define STORE_R0 0x03
#define STORE_R1 0x04
#define STORE_R2 0x05
#define STORE_R3 0x06
#define STORE_ACC 0x07
#define STORE_ZP_R0 0x08
#define STORE_ZP_R1 0x09
#define STORE_ZP_R2 0x0A
#define STORE_ZP_R3 0x0B
#define STORE_ZP_ACC 0x0C
#define LOAD_R0 0x0D
#define LOAD_R1 0x0E
#define LOAD_R2 0x0F
#define LOAD_R3 0x10
#define LOAD_ACC 0x11
#define LOAD_ZP_R0 0x12
#define LOAD_ZP_R1 0x13
#define LOAD_ZP_R2 0x14
#define LOAD_ZP_R3 0x15
#define LOAD_ZP_ACC 0x16
#define LOAD_LIT_R0 0x17
#define LOAD_LIT_R1 0x18
#define LOAD_LIT_R2 0x19
#define LOAD_LIT_R3 0x1A
#define LOAD_LIT_ACC 0x1B
#define TRANS_R0_R1 0x1C
#define TRANS_R0_R2 0x1D
#define TRANS_R0_R3 0x1E
#define TRANS_R0_ACC 0x1F
#define TRANS_R1_R0 0x20
#define TRANS_R1_R2 0x21
#define TRANS_R1_R3 0x22
#define TRANS_R1_ACC 0x23
#define TRANS_R2_R0 0x24
#define TRANS_R2_R1 0x25
#define TRANS_R2_R3 0x26
#define TRANS_R2_ACC 0x27
#define TRANS_R3_R0 0x28
#define TRANS_R3_R1 0x29
#define TRANS_R3_R2 0x2A
#define TRANS_R3_ACC 0x2B
#define TRANS_ACC_R0 0x2C
#define TRANS_ACC_R1 0x2D
#define TRANS_ACC_R2 0x2E
#define TRANS_ACC_R3 0x2F
#define TRANS_SP_R0 0x30
#define TRANS_SP_R1 0x31
#define TRANS_SP_R2 0x32
#define TRANS_SP_R3 0x33
#define TRANS_SP_ACC 0x34
#define TRANS_FLAGS_R0 0x35
#define TRANS_FLAGS_R1 0x36
#define TRANS_FLAGS_R2 0x37
#define TRANS_FLAGS_R3 0x38
#define TRANS_FLAGS_ACC 0x39

#define ADD_LIT 0x3D
#define ADDC_LIT 0x3E
#define SUB_LIT 0x3F
#define SUBC_LIT 0x40
#define ADD_R0 0x41
#define ADD_R1 0x42
#define ADD_R2 0x43
#define ADD_R3 0x44
#define ADDC_R0 0x45
#define ADDC_R1 0x46
#define ADDC_R2 0x47
#define ADDC_R3 0x48
#define SUB_R0 0x49
#define SUB_R1 0x4A
#define SUB_R2 0x4B
#define SUB_R3 0x4C
#define SUBC_R0 0x4D
#define SUBC_R1 0x4E
#define SUBC_R2 0x4F
#define SUBC_R3 0x51
#define SHR_LIT 0x52
#define SHR_R0 0x53
#define SHR_R1 0x54
#define SHR_R2 0x55
#define SHR_R3 0x56
#define SHR_ACC 0x57
#define SHL_LIT 0x58
#define SHL_R0 0x59
#define SHL_R1 0x5A
#define SHL_R2 0x5B
#define SHL_R3 0x5C
#define SHL_ACC 0x5D
#define AND_R0 0x5E
#define AND_R1 0x5F
#define AND_R2 0x60
#define AND_R3 0x61
#define AND_LIT 0x62
#define OR_R0 0x63
#define OR_R1 0x64
#define OR_R2 0x65
#define OR_R3 0x66
#define OR_LIT 0x67
#define XOR_R0 0x68
#define XOR_R1 0x69
#define XOR_R2 0x6A
#define XOR_R3 0x6B
#define XOR_LIT 0x6C
#define NOT_0 0x6D
#define INC_R0 0x6E
#define INC_R1 0x6F
#define INC_R2 0x70
#define INC_R3 0x71
#define INC_ACC 0x72
#define DEC_R0 0x73
#define DEC_R1 0x74
#define DEC_R2 0x75
#define DEC_R3 0x76
#define DEC_ACC 0x77

// zero page mode?
#define JSR_0 0x7F
#define RET_0 0x80
#define RETI_0 0x81

#define PUSH_R0 0x89
#define PUSH_R1 0x8A
#define PUSH_R2 0x8B
#define PUSH_R3 0x8C
#define PUSH_ACC 0x8D
#define PUSH_LIT 0x8E
#define POP_R0 0x8F
#define POP_R1 0x90
#define POP_R2 0x91
#define POP_R3 0x92
#define POP_ACC 0x93
#define DROP_0 0x94

#define CMP_R0_R1 0x9C
#define CMP_R0_R2 0x9D
#define CMP_R0_R3 0x9E
#define CMP_R0_ACC 0x9F
#define CMP_R1_R0 0xA0
#define CMP_R1_R2 0xA1
#define CMP_R1_R3 0xA2
#define CMP_R1_ACC 0xA3
#define CMP_R2_R0 0xA4
#define CMP_R2_R1 0xA5
#define CMP_R2_R3 0xA6
#define CMP_R2_ACC 0xA7
#define CMP_R3_R0 0xA8
#define CMP_R3_R1 0xA9
#define CMP_R3_R2 0xAA
#define CMP_R3_ACC 0xAB
#define CMP_ACC_R0 0xAC
#define CMP_ACC_R1 0xAD
#define CMP_ACC_R2 0xAE
#define CMP_ACC_R3 0xAF
#define CMP_R0_LIT 0xB0
#define CMP_R1_LIT 0xB1
#define CMP_R2_LIT 0xB2
#define CMP_R3_LIT 0xB3
#define CMP_ACC_LIT 0xB4
#define BRA_S 0xB5
#define BRA_C 0xB6
#define BRA_I 0xB7
#define BRA_O 0xB8
#define BRA_G 0xB9
#define BRA_Z 0xBA
#define BRAN_S 0xBB
#define BRAN_C 0xBC
#define BRAN_I 0xBD
#define BRAN_O 0xBE
#define BRAN_G 0xBF
#define BRAN_Z 0xC0
#define JMP_0 0xC1

#define SET_S 0xC9
#define SET_C 0xCA
#define SET_I 0xCB
#define SET_O 0xCC
#define SET_G 0xCD
#define SET_Z 0xCE
#define CLEAR_S 0xCF
#define CLEAR_C 0xD0
#define CLEAR_I 0xD1
#define CLEAR_O 0xD2
#define CLEAR_G 0xD3
#define CLEAR_Z 0xD4

#endif
