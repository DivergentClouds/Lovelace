#ifndef CPU_H
#define CPU_H

#include "../motherboard/motherboard.h"

typedef struct registers_s {
	uint8_t r[4];
	uint8_t acc;
	uint16_t pc;
	uint8_t sp;
	uint8_t flags; // bitwise
} registers_t;

typedef struct {
	uint8_t reset;
	uint8_t interrupt;
	uint8_t rw;
	uint16_t address; // bitwise
	uint8_t data; // bitwise
} cpu_pins_t;

extern registers_t registers;
extern cpu_pins_t cpu_pins;

// states

extern uint8_t instruction;
extern uint8_t stage;
extern uint8_t hold[2]; // for load and store
extern uint8_t interrupting; // should an interrupt happen
extern uint8_t mid_interrupt; // for checking if an interrupt is in progress

// misc functions

void do_cpu_cycle();

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

void do_store_ind(uint8_t data);
void do_store_ind_zp(uint8_t data);
void do_load_ind(uint8_t *data);
void do_load_ind_zp(uint8_t *data);


void do_push(uint8_t data);
void do_pop(uint8_t *data);

void do_bra(uint8_t mask);
void do_bran(uint8_t mask);
void do_compare_lit(uint8_t data);

void do_reset();
void do_interrupt();

// opcodes

#define NOOP 0x00

#define STORE_R0 0x09
#define STORE_R1 0x0a
#define STORE_R2 0x0b
#define STORE_R3 0x0c
#define STORE_ACC 0x0d
#define STORE_LIT 0x0e
#define STORE_ZP_R0 0x0f
#define STORE_ZP_R1 0x10
#define STORE_ZP_R2 0x11
#define STORE_ZP_R3 0x12
#define STORE_ZP_ACC 0x13
#define STORE_ZP_LIT 0x14
#define STORE_IND_R0 0x15
#define STORE_IND_R1 0x16
#define STORE_IND_R2 0x17
#define STORE_IND_R3 0x18
#define STORE_IND_ACC 0x19
#define STORE_IND_ZP_R0 0x1a
#define STORE_IND_ZP_R1 0x1b
#define STORE_IND_ZP_R2 0x1c
#define STORE_IND_ZP_R3 0x1d
#define STORE_IND_ZP_ACC 0x1e
#define LOAD_R0 0x1f
#define LOAD_R1 0x20
#define LOAD_R2 0x21
#define LOAD_R3 0x22
#define LOAD_ACC 0x23
#define LOAD_ZP_R0 0x24
#define LOAD_ZP_R1 0x25
#define LOAD_ZP_R2 0x26
#define LOAD_ZP_R3 0x27
#define LOAD_ZP_ACC 0x28
#define LOAD_LIT_R0 0x29
#define LOAD_LIT_R1 0x2a
#define LOAD_LIT_R2 0x2b
#define LOAD_LIT_R3 0x2c
#define LOAD_LIT_ACC 0x2d
#define LOAD_IND_R0 0x2e
#define LOAD_IND_R1 0x2f
#define LOAD_IND_R2 0x30
#define LOAD_IND_R3 0x31
#define LOAD_IND_ACC 0x32
#define LOAD_IND_ZP_R0 0x33
#define LOAD_IND_ZP_R1 0x34
#define LOAD_IND_ZP_R2 0x35
#define LOAD_IND_ZP_R3 0x36
#define LOAD_IND_ZP_ACC 0x37
#define TRANS_R0_R1 0x38
#define TRANS_R0_R2 0x39
#define TRANS_R0_R3 0x3a
#define TRANS_R0_ACC 0x3b
#define TRANS_R1_R0 0x3c
#define TRANS_R1_R2 0x3d
#define TRANS_R1_R3 0x3e
#define TRANS_R1_ACC 0x3f
#define TRANS_R2_R0 0x40
#define TRANS_R2_R1 0x41
#define TRANS_R2_R3 0x42
#define TRANS_R2_ACC 0x43
#define TRANS_R3_R0 0x44
#define TRANS_R3_R1 0x45
#define TRANS_R3_R2 0x46
#define TRANS_R3_ACC 0x47
#define TRANS_ACC_R0 0x48
#define TRANS_ACC_R1 0x49
#define TRANS_ACC_R2 0x4a
#define TRANS_ACC_R3 0x4b
#define TRANS_SP_R0 0x4c
#define TRANS_SP_R1 0x4d
#define TRANS_SP_R2 0x4e
#define TRANS_SP_R3 0x4f
#define TRANS_SP_ACC 0x50
#define TRANS_FLAGS_R0 0x51
#define TRANS_FLAGS_R1 0x52
#define TRANS_FLAGS_R2 0x53
#define TRANS_FLAGS_R3 0x54
#define TRANS_FLAGS_ACC 0x55

#define ADD_R0 0x5e
#define ADD_R1 0x5f
#define ADD_R2 0x60
#define ADD_R3 0x61
#define ADD_ACC 0x62
#define ADD_LIT 0x63
#define ADDC_R0 0x64
#define ADDC_R1 0x65
#define ADDC_R2 0x66
#define ADDC_R3 0x67
#define ADDC_ACC 0x68
#define ADDC_LIT 0x69
#define SUB_R0 0x6a
#define SUB_R1 0x6b
#define SUB_R2 0x6c
#define SUB_R3 0x6d
#define SUB_LIT 0x6e
#define SUBC_R0 0x6f
#define SUBC_R1 0x70
#define SUBC_R2 0x71
#define SUBC_R3 0x72
#define SUBC_LIT 0x73
#define SHR_R0 0x74
#define SHR_R1 0x75
#define SHR_R2 0x76
#define SHR_R3 0x77
#define SHR_ACC 0x78
#define SHR_LIT 0x79
#define SHL_R0 0x7a
#define SHL_R1 0x7b
#define SHL_R2 0x7c
#define SHL_R3 0x7d
#define SHL_ACC 0x7e
#define SHL_LIT 0x7f
#define AND_R0 0x80
#define AND_R1 0x81
#define AND_R2 0x82
#define AND_R3 0x83
#define AND_LIT 0x84
#define OR_R0 0x85
#define OR_R1 0x86
#define OR_R2 0x87
#define OR_R3 0x88
#define OR_LIT 0x89
#define XOR_R0 0x8a
#define XOR_R1 0x8b
#define XOR_R2 0x8c
#define XOR_R3 0x8d
#define XOR_LIT 0x8e
#define NOT_0 0x8f
#define INC_R0 0x90
#define INC_R1 0x91
#define INC_R2 0x92
#define INC_R3 0x93
#define INC_ACC 0x94
#define DEC_R0 0x95
#define DEC_R1 0x96
#define DEC_R2 0x97
#define DEC_R3 0x98
#define DEC_ACC 0x99

#define PUSH_R0 0xa2
#define PUSH_R1 0xa3
#define PUSH_R2 0xa4
#define PUSH_R3 0xa5
#define PUSH_ACC 0xa6
#define PUSH_LIT 0xa7
#define POP_R0 0xa8
#define POP_R1 0xa9
#define POP_R2 0xaa
#define POP_R3 0xab
#define POP_ACC 0xac
#define DROP_0 0xad

#define CMP_R0_R1 0xb6
#define CMP_R0_R2 0xb7
#define CMP_R0_R3 0xb8
#define CMP_R0_ACC 0xb9
#define CMP_R1_R0 0xba
#define CMP_R1_R2 0xbb
#define CMP_R1_R3 0xbc
#define CMP_R1_ACC 0xbd
#define CMP_R2_R0 0xbe
#define CMP_R2_R1 0xbf
#define CMP_R2_R3 0xc0
#define CMP_R2_ACC 0xc1
#define CMP_R3_R0 0xc2
#define CMP_R3_R1 0xc3
#define CMP_R3_R2 0xc4
#define CMP_R3_ACC 0xc5
#define CMP_ACC_R0 0xc6
#define CMP_ACC_R1 0xc7
#define CMP_ACC_R2 0xc8
#define CMP_ACC_R3 0xc9
#define CMP_R0_LIT 0xca
#define CMP_R1_LIT 0xcb
#define CMP_R2_LIT 0xcc
#define CMP_R3_LIT 0xcd
#define CMP_ACC_LIT 0xce
#define BRA_S 0xcf
#define BRA_C 0xd0
#define BRA_I 0xd1
#define BRA_O 0xd2
#define BRA_G 0xd3
#define BRA_Z 0xd4
#define BRAN_S 0xd5
#define BRAN_C 0xd6
#define BRAN_I 0xd7
#define BRAN_O 0xd8
#define BRAN_G 0xd9
#define BRAN_Z 0xda
#define JMP_0 0xdb
#define JMPI_0 0xdc
#define JSR_0 0xdd
#define JSRI_0 0xde
#define RET_0 0xdf
#define RETI_0 0xe0

#define SET_S 0xe9
#define SET_C 0xea
#define SET_I 0xeb
#define SET_O 0xec
#define SET_G 0xed
#define SET_Z 0xee
#define CLEAR_S 0xef
#define CLEAR_C 0xf0
#define CLEAR_I 0xf1
#define CLEAR_O 0xf2
#define CLEAR_G 0xf3
#define CLEAR_Z 0xf4

#endif
