#include "audio.h"
#include "../clock/clock.h"

// registers

void reset_registers() {
	for (int osc = 0; osc < 3; osc++) {
		for (int reg = 0; reg < 8; reg++) {
			oscillators[osc].registers[reg] = 0;
		}
	}
}

// pins

void reset_pins() {
	audio_pins.reset = 0;
	audio_pins.osc = 0;
	audio_pins.reg = 0;
	audio_pins.data = 0;
	audio_pins.rw = 0;
	audio_pins.out = 0;
}

// clock stuff

void do_audio_cycle() {
	if (audio_pins.rw) { // read
			audio_pins.data = oscillators[audio_pins.osc]
			.registers[audio_pins.reg];
	} else { // write
		oscillators[audio_pins.osc]
			.registers[audio_pins.reg] = audio_pins.data;
	}
}

// audio samples

float note_freq(uint8_t note, uint8_t bend) {
	if (note == 0) {
		return 0;
	} else {
		return 440 * powf(2, ((int8_t) note - 58 + bend / 256.0) / 12.0);
	}
}

float pulse_wave(float phase, uint8_t width) {
	return phase < width / 256.0 ? 1.0 : -1.0;
}

float saw_wave(float phase) {
	return phase * 2 - 1;
}

float triangle_wave(float phase) {
	return fmin(phase * 4 - 1, (1 - phase) * 4 - 1);
}

float noise_wave() {
	return rand() / (float) RAND_MAX * 2 - 1;
}

float render_oscillator(uint8_t n) {
	float freq;

	freq = note_freq(oscillators[n].oscillator.note,
		oscillators[n].oscillator.bend);

	phases[n] = fmod(phases[n] + freq / SAMPLE_RATE, 1);

	if (oscillators[n].oscillator.waveform == 0b00)
		return pulse_wave(fmod(phases[n] +
			oscillators[n].oscillator.phase / 256.0, 1),
			oscillators[n].oscillator.width)
			* smooth_volume[n];
	else if (oscillators[n].oscillator.waveform == 0b01)
		return saw_wave(fmod(phases[n] +
			oscillators[n].oscillator.phase / 256.0, 1))
			* smooth_volume[n];
	else if (oscillators[n].oscillator.waveform == 0b10)
		return triangle_wave(fmod(phases[n] +
			oscillators[n].oscillator.phase / 256.0, 1))
			* smooth_volume[n];
	else // 0b11
		return noise_wave()
		* smooth_volume[n];
}

void generate_sample() {
	for (int i = 0; i < 3; i++)
		smooth_volume[i] = (smooth_volume[i] * 19 +
				oscillators[i].oscillator.volume / 255.0) / 20;

	for (int i = 0; i < 3; i++)
		smooth_low[i] = (smooth_low[i] * 199 +
				oscillators[i].oscillator.low / 255.0) / 200;

	for (int i = 0; i < 3; i++)
		smooth_high[i] = (smooth_high[i] * 199 +
				oscillators[i].oscillator.high / 255.0) / 200;

	audio_pins.out = 0;
	audio_pins.out += highpass(highpass(lowpass(lowpass(render_oscillator(0),
		0, 0, butterworth_const_1),
		3, 0, butterworth_const_2),
		0, 0, butterworth_const_1),
		3, 0, butterworth_const_2);
	audio_pins.out += highpass(highpass(lowpass(lowpass(render_oscillator(1),
		1, 1, butterworth_const_1),
		4, 1, butterworth_const_2),
		1, 1, butterworth_const_1),
		4, 1, butterworth_const_2);
	audio_pins.out += highpass(highpass(lowpass(lowpass(render_oscillator(2),
		2, 2, butterworth_const_1),
		5, 2, butterworth_const_2),
		2, 2, butterworth_const_1),
		5, 2, butterworth_const_2);
}

float lowpass(float sample, uint8_t n, uint8_t osc, float butterworth_const) {
	float result;
	float cutoff;
	float c2;
	float a0;

	cutoff = smooth_low[osc];
	cutoff = (cutoff * cutoff) * (20000.0 / SAMPLE_RATE);
	cutoff = reciprocal_pi * atanf(cutoff * M_PI);
	butterworth_const *= cutoff;
	c2 = cutoff * cutoff;
	a0 = reciprocal_pi_squared + butterworth_const + c2;

	if (oscillators[osc].oscillator.low == 255) {
		result = sample;
	} else {
		result =
			(2 * c2 - 2 * reciprocal_pi_squared) / -a0 * lowpass_state[n].y1 +
			(reciprocal_pi_squared - butterworth_const + c2) / -a0 * lowpass_state[n].y2 +
			c2 / a0 * sample +
			c2 / a0 * 2 * lowpass_state[n].x1 +
			c2 / a0 * lowpass_state[n].x2;
	}

	lowpass_state[n].x2 = lowpass_state[n].x1;
	lowpass_state[n].x1 = sample;
	lowpass_state[n].y2 = lowpass_state[n].y1;
	lowpass_state[n].y1 = result;

	return result;
}

float highpass(float sample, uint8_t n, uint8_t osc, float butterworth_const) {
	float result;
	float cutoff;
	float c2;
	float a0;

	cutoff = smooth_high[osc];
	cutoff = (cutoff * cutoff) * (20000.0 / SAMPLE_RATE);
	cutoff = reciprocal_pi * atanf(cutoff * M_PI);
	butterworth_const *= cutoff;
	c2 = cutoff * cutoff;
	a0 = reciprocal_pi_squared + butterworth_const + c2;

	if (oscillators[osc].oscillator.high == 0) {
		result = sample;
	} else {
		result =
			(2 * c2 - 2 * reciprocal_pi_squared) / -a0 * highpass_state[n].y1 +
			(reciprocal_pi_squared - butterworth_const + c2) / -a0 * highpass_state[n].y2 +
			reciprocal_pi_squared / a0 * sample +
			reciprocal_pi_squared / a0 * -2 * highpass_state[n].x1 +
			reciprocal_pi_squared / a0 * highpass_state[n].x2;
	}

	highpass_state[n].x2 = highpass_state[n].x1;
	highpass_state[n].x1 = sample;
	highpass_state[n].y2 = highpass_state[n].y1;
	highpass_state[n].y1 = result;

	return result;
}
