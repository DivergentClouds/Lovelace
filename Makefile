linux:
	mkdir -p build
	gcc -c ./src/motherboard/motherboard.c -o ./build/motherboard.o
	gcc -c ./src/cpu/cpu.c -o ./build/cpu.o
	gcc -c ./src/memory/memory.c -o ./build/memory.o
	gcc -c ./src/audio/audio.c -o ./build/audio.o
	gcc -c ./src/keyboard/keyboard.c -o ./build/keyboard.o
	gcc ./build/motherboard.o ./build/cpu.o ./build/memory.o ./build/audio.o ./build/keyboard.o -lm -lSDL2 -O2 -o ./build/harriet
windows:
	mkdir -p build
	gcc -c ./src/motherboard/motherboard.c -o ./build/motherboard.o
	gcc -c ./src/cpu/cpu.c -o ./build/cpu.o
	gcc -c ./src/memory/memory.c -o ./build/memory.o
	gcc -c ./src/audio/audio.c -o ./build/audio.o
	gcc -c ./src/keyboard/keyboard.c -o ./build/keyboard.o
	gcc ./build/motherboard.o ./build/cpu.o ./build/memory.o ./build/audio.o ./build/keyboard.o -lm `sdl2-config --cflags --libs` -O2 -o ./build/harriet.exe
