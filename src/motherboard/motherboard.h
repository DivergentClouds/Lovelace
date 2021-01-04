#ifndef MOTHERBOARD_H
#define MOTHERBOARD_H


#include <stdio.h>
#include <inttypes.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "../audio/audio.h"
#include "../memory/memory.h"
#include "../cpu/cpu.h"
#include "../keyboard/keyboard.h"

#define SAMPLE_RATE 50000
#define AUDIO_BUFFER_SIZE 1000

#define CPU_SIM_FREQ 2000000.0
#define CPU_UPDATE_FREQ (SAMPLE_RATE / AUDIO_BUFFER_SIZE)
#define CYCLES_PER_CALLBACK (CPU_SIM_FREQ / CPU_UPDATE_FREQ)

extern uint8_t should_close;
extern uint16_t clock_count;

extern uint8_t clock_interrupted;

void audio_callback(void *data, Uint8 *stream, int len);

#endif
