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
