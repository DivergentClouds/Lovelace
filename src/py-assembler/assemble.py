import argparse
import ast
from functools import partial

mnemonics = {
	"NOP": {
		"": 0x00
	},
	"STR": {
		"R0 ADR": 0x09,
		"R1 ADR": 0x0a,
		"R2 ADR": 0x0b,
		"R3 ADR": 0x0c,
		"ACC ADR": 0x0d,
		"LIT ADR": 0x0e,
		"R0 ZP": 0x0f,
		"R1 ZP": 0x10,
		"R2 ZP": 0x11,
		"R3 ZP": 0x12,
		"ACC ZP": 0x13,
		"LIT ZP": 0x14,
	},
	"STRI": {
		"R0 ADR": 0x15,
		"R1 ADR": 0x16,
		"R2 ADR": 0x17,
		"R3 ADR": 0x18,
		"ACC ADR": 0x19,
		"R0 ZP": 0x1a,
		"R1 ZP": 0x1b,
		"R2 ZP": 0x1c,
		"R3 ZP": 0x1d,
		"ACC ZP": 0x1e,
	},
	"LOD": {
		"ADR R0": 0x1f,
		"ADR R1": 0x20,
		"ADR R2": 0x21,
		"ADR R3": 0x22,
		"ADR ACC": 0x23,
		"ZP R0": 0x24,
		"ZP R1": 0x25,
		"ZP R2": 0x26,
		"ZP R3": 0x27,
		"ZP ACC": 0x28,
		"LIT R0": 0x29,
		"LIT R1": 0x2a,
		"LIT R2": 0x2b,
		"LIT R3": 0x2c,
		"LIT ACC": 0x2d,
	},
	"LODI": {
		"ADR R0": 0x2e,
		"ADR R1": 0x2f,
		"ADR R2": 0x30,
		"ADR R3": 0x31,
		"ADR ACC": 0x32,
		"ZP R0": 0x33,
		"ZP R1": 0x34,
		"ZP R2": 0x35,
		"ZP R3": 0x36,
		"ZP ACC": 0x37,
	},
	"TRN": {
		"R0 R1": 0x38,
		"R0 R2": 0x39,
		"R0 R3": 0x3a,
		"R0 ACC": 0x3b,
		"R1 R0": 0x3c,
		"R1 R2": 0x3d,
		"R1 R3": 0x3e,
		"R1 ACC": 0x3f,
		"R2 R0": 0x40,
		"R2 R1": 0x41,
		"R2 R3": 0x42,
		"R2 ACC": 0x43,
		"R3 R0": 0x44,
		"R3 R1": 0x45,
		"R3 R2": 0x46,
		"R3 ACC": 0x47,
		"ACC R0": 0x48,
		"ACC R1": 0x49,
		"ACC R2": 0x4a,
		"ACC R3": 0x4b,
		"SP R0": 0x4c,
		"SP R1": 0x4d,
		"SP R2": 0x4e,
		"SP R3": 0x4f,
		"SP ACC": 0x50,
		"FLG R0": 0x51,
		"FLG R1": 0x52,
		"FLG R2": 0x53,
		"FLG R3": 0x54,
		"FLG ACC": 0x55,
	},
	"ADD": {
		"R0": 0x5e,
		"R1": 0x5f,
		"R2": 0x60,
		"R3": 0x61,
		"ACC": 0x62,
		"LIT": 0x63,
	},
	"ADDC": {
		"R0": 0x64,
		"R1": 0x65,
		"R2": 0x66,
		"R3": 0x67,
		"ACC": 0x68,
		"LIT": 0x69,
	},
	"SUB": {
		"R0": 0x6a,
		"R1": 0x6b,
		"R2": 0x6c,
		"R3": 0x6d,
		"LIT": 0x6e,
	},
	"SUBC": {
		"R0": 0x6f,
		"R1": 0x70,
		"R2": 0x71,
		"R3": 0x72,
		"LIT": 0x73,
	},
	"SHR": {
		"R0": 0x74,
		"R1": 0x75,
		"R2": 0x76,
		"R3": 0x77,
		"ACC": 0x78,
		"LIT": 0x79,
	},
	"SHL": {
		"R0": 0x7a,
		"R1": 0x7b,
		"R2": 0x7c,
		"R3": 0x7d,
		"ACC": 0x7e,
		"LIT": 0x7f,
	},
	"AND": {
		"R0": 0x80,
		"R1": 0x81,
		"R2": 0x82,
		"R3": 0x83,
		"LIT": 0x84,
	},
	"OR": {
		"R0": 0x85,
		"R1": 0x86,
		"R2": 0x87,
		"R3": 0x88,
		"LIT": 0x89,
	},
	"XOR": {
		"R0": 0x8a,
		"R1": 0x8b,
		"R2": 0x8c,
		"R3": 0x8d,
		"LIT": 0x8e,
	},
	"NOT": {
		"": 0x8f,
	},
	"INC": {
		"R0": 0x90,
		"R1": 0x91,
		"R2": 0x92,
		"R3": 0x93,
		"LIT": 0x94,
	},
	"DEC": {
		"R0": 0x95,
		"R1": 0x96,
		"R2": 0x97,
		"R3": 0x98,
		"LIT": 0x99,
	},
	"JSR": {
		"ADR": 0xa2,
	},
	"RET": {
		"": 0xa3,
	},
	"RETI": {
		"": 0xa4,
	},
	"PSH": {
		"R0": 0xad,
		"R1": 0xae,
		"R2": 0xaf,
		"R3": 0xb0,
		"ACC": 0xb1,
		"LIT": 0xb2,
	},
	"POP": {
		"R0": 0xb3,
		"R1": 0xb4,
		"R2": 0xb5,
		"R3": 0xb6,
		"ACC": 0xb7,
	},
	"DRP": {
		"": 0xb8,
	},
	"CMP": {
		"R0 R1": 0xc1,
		"R0 R2": 0xc2,
		"R0 R3": 0xc3,
		"R0 ACC": 0xc4,
		"R1 R0": 0xc5,
		"R1 R2": 0xc6,
		"R1 R3": 0xc7,
		"R1 ACC": 0xc8,
		"R2 R0": 0xc9,
		"R2 R1": 0xca,
		"R2 R3": 0xcb,
		"R2 ACC": 0xcc,
		"R3 R0": 0xcd,
		"R3 R1": 0xce,
		"R3 R2": 0xcf,
		"R3 ACC": 0xd0,
		"ACC R0": 0xd1,
		"ACC R1": 0xd2,
		"ACC R2": 0xd3,
		"ACC R3": 0xd4,
		"R0 LIT": 0xd5,
		"R1 LIT": 0xd6,
		"R2 LIT": 0xd7,
		"R3 LIT": 0xd8,
		"ACC LIT": 0xd9,
	},
	"BRA": {
		"S ADR": 0xda,
		"C ADR": 0xdb,
		"I ADR": 0xdc,
		"O ADR": 0xdd,
		"G ADR": 0xde,
		"Z ADR": 0xdf,
	},
	"BRAN": {
		"S ADR": 0xe0,
		"C ADR": 0xe1,
		"I ADR": 0xe2,
		"O ADR": 0xe3,
		"G ADR": 0xe4,
		"Z ADR": 0xe5,
	},
	"JMP": {
		"ADR": 0xe6,
	},
	"SET": {
		"S": 0xef,
		"C": 0xf0,
		"I": 0xf1,
		"O": 0xf2,
		"G": 0xf3,
		"Z": 0xf4,
	},
	"CLR": {
		"S": 0xf5,
		"C": 0xf6,
		"I": 0xf7,
		"O": 0xf8,
		"G": 0xf9,
		"Z": 0xfa,
	},

	# temporary
	"QUIT": {
		"": 0xff,
	}
}

def parse_number(arg):
	if arg[0] in "0123456789":
		return int(arg)
	if arg.startswith("!"):
		return int(arg[1:])
	if arg.startswith("$"):
		return int(arg[1:], 16)
	if arg.startswith("%"):
		return int(arg[1:], 2)

def interpret_argument(arg, instruction):
	if arg.startswith(":"):
		return "ADR"
	elif arg.startswith("R"):
		return arg
	elif arg in "SCIOGZ":
		return arg
	elif arg.startswith("#"):
		return "LIT"
	elif arg[0] in "0123456789$%!":
		if parse_number(arg) < 256 and instruction in ["STR", "STRI", "LOD", "LODI"]:
			return "ZP"
		else:
			return "ADR"
	elif arg in ["ACC", "SP", "FLG"]:
		return arg
	else:
		raise Exception("Invalid argument")

def argument_size(arg):
	if arg == "ADR":
		return 2
	if arg == "ZP":
		return 1
	if arg == "LIT":
		return 1
	return 0

# Possibly make addresses controlled by floppy controller
def compile(source, location=0x0200):
	labels = {}
	instructions = []
	length = 0

	for line in source.split("\n"):
		parts = line.strip().upper().split(";")[0].split()

		if not parts:
			continue

		if parts[0].startswith(":"):
			assert len(parts) == 1, "Whitespace isn't allowed in label names"
			labels[parts[0][1:]] = length + location
		else:
			assert parts[0] in mnemonics, "Unrecognized mnemonic"
			instructions.append(parts)

			length += 1 + sum(map(argument_size,
				map(partial(interpret_argument, instruction=parts[0]), parts[1:])))

	for instruction in instructions:
		print(instruction)

		yield mnemonics[instruction[0]][
			" ".join(map(partial(interpret_argument, instruction=instruction[0]), instruction[1:]))]

		for arg in instruction[1:]:
			type = interpret_argument(arg, instruction[0])
			if type == "ADR":
				if arg[0] == ":":
					address = labels[arg[1:]]
				else:
					address = parse_number(arg)
				yield address >> 8
				yield address & 0xff
			elif type == "ZP":
				yield parse_number(arg)
			elif type == "LIT":
				yield parse_number(arg[1:])


if __name__ == "__main__":
	p = argparse.ArgumentParser(description="Assemble Harriet assembly language.")
	p.add_argument("file", help="an input assembly file")
	p.add_argument("-o", "--output", default="harriet.o",
		help="the output filename")
	p.add_argument("-f", "--offset", default="0x0200", type=ast.literal_eval,
		help="the address offset to use for labels")

	args = p.parse_args()
	with open(args.file) as f:
		source = f.read()

	code = bytes(compile(source, args.offset))

	with open(args.output, "wb") as f:
		f.write(code)
