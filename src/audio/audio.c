#include "audio.h"

// registers

void reset_registers() {
	for (int osc = 0; osc < 3; osc++) {
		for (int reg = 0; reg < 12; reg++) {
			oscillators[osc].registers[reg] = 0;
		}
	}
}

// pins

void reset_pins() {
	for (int pin = 0; pin < 10; pin++) {
		pins.bytes[pin] = 0;
	}
}

// clock stuff

void clock_actions() {
	if (pins.pins.clock) {
		if (pins.pins.rw) { // read
			pins.pins.data = oscillators[pins.pins.osc]
				.registers[pins.pins.reg];
		} else { // write
			oscillators[pins.pins.osc]
				.registers[pins.pins.reg] = pins.pins.data;
		}
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
			* (oscillators[n].oscillator.volume / 255.0);
	else if (oscillators[n].oscillator.waveform == 0b01)
		return saw_wave(fmod(phases[n] +
			oscillators[n].oscillator.phase / 256.0, 1))
			* (oscillators[n].oscillator.volume / 255.0);
	else if (oscillators[n].oscillator.waveform == 0b10)
		return triangle_wave(fmod(phases[n] +
			oscillators[n].oscillator.phase / 256.0, 1))
			* (oscillators[n].oscillator.volume / 255.0);
	else // 0b11
		return noise_wave()
		* (oscillators[n].oscillator.volume / 255.0);
}

void generate_sample() {
	pins.pins.out = 0;
	pins.pins.out += highpass(highpass(lowpass(lowpass(render_oscillator(0),
		0, 0, butterworth_const_1),
		3, 0, butterworth_const_2),
		0, 0, butterworth_const_1),
		3, 0, butterworth_const_2);
	pins.pins.out += highpass(highpass(lowpass(lowpass(render_oscillator(1),
		1, 1, butterworth_const_1),
		4, 1, butterworth_const_2),
		1, 1, butterworth_const_1),
		4, 1, butterworth_const_2);
	pins.pins.out += highpass(highpass(lowpass(lowpass(render_oscillator(2),
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

	cutoff = oscillators[osc].oscillator.low / 128.0 * (20000.0 / SAMPLE_RATE);
	cutoff = (cutoff * cutoff) / 2;
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

	cutoff = oscillators[osc].oscillator.high / 128.0 * (20000.0 / SAMPLE_RATE);
	cutoff = (cutoff * cutoff) / 2;
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

void audio_callback(void *data, Uint8 *stream, int len) {
	float *fstream;

	fstream = (float *) stream;
	for (int i = 0; i < 256; i++) {
		generate_sample();
		fstream[i] = pins.pins.out;
	}
}

SDL_AudioDeviceID initialise_audio() {
	SDL_AudioSpec want, have;
	SDL_AudioDeviceID dev;

	SDL_memset(&want, 0, sizeof(want));
	want.freq = SAMPLE_RATE;
	want.format = AUDIO_F32;
	want.channels = 1;
	want.samples = 256;
	want.callback = audio_callback;
	dev = SDL_OpenAudioDevice(NULL, 0, &want, &have,
		SDL_AUDIO_ALLOW_FORMAT_CHANGE);

	return dev;
}

int main(int argc, char const **argv) {
	SDL_AudioDeviceID dev;

	reset_registers();
	srand(0x7EA75);

	// play audio

	if (SDL_Init(SDL_INIT_AUDIO) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}

	dev = initialise_audio();

	SDL_PauseAudioDevice(dev, 0);

	// generate audio

	oscillators[0].oscillator.volume = 60;
	oscillators[0].oscillator.width = 128;
	oscillators[0].oscillator.waveform = 0b00;
	oscillators[0].oscillator.note = 37;

	for (uint8_t i = 1; i < 127; i++) {
		oscillators[0].oscillator.low = 180 - i;
		oscillators[0].oscillator.high = i;
		SDL_Delay(8);
	}

	for (uint8_t i = 127; i > 1; i--) {
		oscillators[0].oscillator.low = 180 - i;
		oscillators[0].oscillator.high = i;
		SDL_Delay(8);
	}

	// cleanup

	SDL_CloseAudioDevice(dev);

	SDL_Quit();

	return 0;
}
