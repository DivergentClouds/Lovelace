#ifndef AUDIO_H
#define AUDIO_H

#include <inttypes.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdlib.h>

#define SAMPLE_RATE 44100

// registers

typedef struct {
	uint8_t high;
	uint8_t low;
	// uint8_t attack;
	// uint8_t decay;
	// uint8_t sustain;
	// uint8_t release;
	uint8_t waveform;
	uint8_t width;
	uint8_t note;
	uint8_t bend;
	uint8_t phase;
	uint8_t volume;
} oscillator_t;

typedef union {
	oscillator_t oscillator;
	uint8_t registers[12];
} oscillator_u;

oscillator_u oscillators[3];

void reset_registers();

// pins

typedef struct {
	uint8_t clock;
	uint8_t reset;
	uint8_t osc; // bitwise
	uint8_t reg; // bitwise
	uint8_t data; // bitwise
	uint8_t rw;
	float out;
} pins_t;

typedef union {
	pins_t pins;
	uint8_t bytes[10];
} pins_u;

pins_u pins;

void reset_pins();

// clock stuff

void clock_actions();

// audio samples

float phases[3];

void generate_sample();

float note_freq(uint8_t note, uint8_t bend);

float pulse_wave(float phase, uint8_t width);
float saw_wave(float phase);
float triangle_wave(float phase);
float noise_wave();

float render_oscillator(uint8_t n);

// -2 * cos(0.75 * pi) / pi
const float butterworth_const = 0.45015815807855303f;

// 1 / pi / pi
const float reciprocal_pi_squared = 0.10132118364233778f;

typedef struct biquad_s {
	float x1;
	float x2;
	float y1;
	float y2;
} biquad_t;

biquad_t lowpass_state[6];
float lowpass(float sample, uint8_t n, uint8_t osc);

void audio_callback(void *data, Uint8 *stream, int len);

#endif
