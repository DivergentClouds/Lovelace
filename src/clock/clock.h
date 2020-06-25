#ifndef CLOCK_H
#define CLOCK_H

#include <inttypes.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string.h>

#define SAMPLE_RATE 50000
#define AUDIO_BUFFER_SIZE 4096
#define PC_START 0x200

uint8_t should_close = 0;
uint16_t clock_count = 0;

uint8_t clock_interrupted = 0;

void audio_callback(void *data, Uint8 *stream, int len);

#endif
