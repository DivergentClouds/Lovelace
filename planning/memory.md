# Memory

# Lovelace

The general memory layout is as such;

- `0x0000` - `0x3FFE` Global memory
- `0x3FFF` Bank number
- `0x4000` - `0xFFFF` Bank memory

The bank memory for bank 0 is just mapped to the ROM.
The CPU program counter starts at `0x4000`. The ROM will contain a bootloader that jumps to `0x0200` when it's done.
