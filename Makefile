<<<<<<< HEAD
TARGET_EXEC := lovelace

CC = gcc

CFLAGS = -Wall

LDFLAGS = -lm -lSDL2 -O3
LDFLAGS_WIN = -lm `sdl2-config --cflags --libs` -O3

SRC_DIR = ./src
BUILD_DIR = ./build

SRCS = $(shell find ${SRC_DIR} -name *.c)

SRCS_ = $(shell find ${SRC_DIR} -name *.c -printf "%f ")
OBJS = $(SRCS_:%.c=$(BUILD_DIR)/%.o)

linux: ${OBJS}
	$(CC) $(OBJS) -o $(BUILD_DIR)/${TARGET_EXEC} $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/*/%.c 
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY = clean windows
clean:
	-@rm -r ${BUILD_DIR}

windows: ${OBJS}
	$(CC) $(OBJS) -o $(BUILD_DIR)/$(TARGET_EXEC).exe $(LDFLAGS_WIN)
=======
linux:
	mkdir -p build
	gcc -Wall -c ./src/motherboard/motherboard.c -o ./build/motherboard.o
	gcc -Wall -c ./src/cpu/cpu.c -o ./build/cpu.o
	gcc -Wall -c ./src/memory/memory.c -o ./build/memory.o
	gcc -Wall -c ./src/audio/audio.c -o ./build/audio.o
	gcc -Wall -c ./src/keyboard/keyboard.c -o ./build/keyboard.o
	gcc ./build/motherboard.o ./build/cpu.o ./build/memory.o ./build/audio.o ./build/keyboard.o -lm -lSDL2 -O3 -o ./build/lovelace

windows:
	mkdir -p build
	gcc -Wall -c ./src/motherboard/motherboard.c -o ./build/motherboard.o
	gcc -Wall -c ./src/cpu/cpu.c -o ./build/cpu.o
	gcc -Wall -c ./src/memory/memory.c -o ./build/memory.o
	gcc -Wall -c ./src/audio/audio.c -o ./build/audio.o
	gcc -Wall -c ./src/keyboard/keyboard.c -o ./build/keyboard.o
	gcc ./build/motherboard.o ./build/cpu.o ./build/memory.o ./build/audio.o ./build/keyboard.o -lm `sdl2-config --cflags --libs` -O3 -o ./build/lovelace.exe
>>>>>>> upstream/master
