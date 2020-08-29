linux:
	mkdir -p build
	gcc -Wall -c ./src/motherboard/motherboard.c -o ./build/motherboard.o
	gcc -Wall -c ./src/cpu/cpu.c -o ./build/cpu.o
	gcc -Wall -c ./src/memory/memory.c -o ./build/memory.o
	gcc -Wall -c ./src/audio/audio.c -o ./build/audio.o
	gcc -Wall -c ./src/keyboard/keyboard.c -o ./build/keyboard.o
	gcc ./build/motherboard.o ./build/cpu.o ./build/memory.o ./build/audio.o ./build/keyboard.o -lm -lSDL2 -O2 -o ./build/lovelace

windows:
	mkdir -p build
	gcc -Wall -c ./src/motherboard/motherboard.c -o ./build/motherboard.o
	gcc -Wall -c ./src/cpu/cpu.c -o ./build/cpu.o
	gcc -Wall -c ./src/memory/memory.c -o ./build/memory.o
	gcc -Wall -c ./src/audio/audio.c -o ./build/audio.o
	gcc -Wall -c ./src/keyboard/keyboard.c -o ./build/keyboard.o
	gcc ./build/motherboard.o ./build/cpu.o ./build/memory.o ./build/audio.o ./build/keyboard.o -lm `sdl2-config --cflags --libs` -O2 -o ./build/lovelace.exe
