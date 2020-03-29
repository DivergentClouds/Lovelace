# Harriet Fantasy Computer

## Basics

A text-based fantasy computer providing:

- Virtual graphics, input, audio, memory, storage, and CPU hardware
 - Storage is virtual floppy disks
- A file system
- An assembly language for that CPU
- A programming language for that hardware and assembly language
 - Embedded assembly
 - Curses-like graphics library
- A bootstrap compiler for that language, written in Python
- A basic disk operating system
- Implementations of these tools
- Various software running within the computer
 - Text editor
 - A compiler for the programming language, written in itself

## Design ideals

Each element of the design of the computer can be used separately, and should be well documented enough that other people can make their own implementations.

The design should be plausible for real implementation.

## Community project ideas

- A pixel art editor and programming library to use it in games
- A tracker

## Hardware

### Graphics

EGA, perhaps reference DOSBox for implementation.
Modes are switchable.

The CPU renders into a memory framebuffer which moves over a cable to a screen.

### Input

Just a keyboard. Insert and replace modes should both be present.

### Audio

Somewhere between NES sound and C64 sound

### Memory

16-bit addressing and memory mapped I/O.

### Storage

Floppy disks.

2 disk drives.

### CPU, assembly

Load/store architecture (have a look @ SPARC, 6502)

## Software

### OS

A single-process disk operating system that provides a shell to launch programs.
