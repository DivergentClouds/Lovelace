#ifndef AUDIO_H
#define AUDIO_H

#include <inttypes.h>
#include <math.h>
#include <stdlib.h>

// registers

typedef struct {
	uint8_t high;
	uint8_t low;
	uint8_t waveform;
	uint8_t width;
	uint8_t note;
	uint8_t bend;
	uint8_t phase;
	uint8_t volume;
} oscillator_t;

typedef union {
	oscillator_t oscillator;
	uint8_t registers[8];
} oscillator_u;

oscillator_u oscillators[3];

void reset_registers();

// pins

typedef struct {
	uint8_t reset;
	uint8_t osc; // bitwise
	uint8_t reg; // bitwise
	uint8_t data; // bitwise
	uint8_t rw;
	float out;
} audio_pins_t;

audio_pins_t audio_pins;

void reset_pins();

// clock stuff

void do_audio_cycle();

// audio samples

float phases[3];

void generate_sample();

float note_freq(uint8_t note, uint8_t bend);

float pulse_wave(float phase, uint8_t width);
float saw_wave(float phase);
float triangle_wave(float phase);
float noise_wave();

float render_oscillator(uint8_t n);

// -2 * cos(7 / 8 * pi) / pi
const float butterworth_const_1 = 0.5881599776824028f;
// -2 * cos(5 / 8 * pi) / pi
const float butterworth_const_2 = 0.24362383960110814f;

// 1 / pi / pi
const float reciprocal_pi_squared = 0.10132118364233778f;

// 1 / pi
const float reciprocal_pi = 0.3183098861837907f;

typedef struct biquad_s {
	float x1;
	float x2;
	float y1;
	float y2;
} biquad_t;

biquad_t lowpass_state[6];
biquad_t highpass_state[6];

float lowpass(float sample, uint8_t n, uint8_t osc, float butterworth_const);
float highpass(float sample, uint8_t n, uint8_t osc, float butterworth_const);

float smooth_volume[3];
float smooth_low[3];
float smooth_high[3];

#endif
