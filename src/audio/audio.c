#include "audio.h"

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

void audio_callback(void *data, Uint8 *stream, int len) {
	float *fstream;

	fstream = (float *) stream;
	for (int i = 0; i < AUDIO_BUFFER_SIZE; i++) {
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
	want.samples = AUDIO_BUFFER_SIZE;
	want.callback = audio_callback;
	dev = SDL_OpenAudioDevice(NULL, 0, &want, &have,
		SDL_AUDIO_ALLOW_FORMAT_CHANGE);

	return dev;
}

const uint8_t scale[7] = {0, 2, 4, 5, 7, 9, 11};

int main(int argc, char const **argv) {
	SDL_AudioDeviceID dev;

	reset_registers();
	reset_pins();
	srand(0x7EA75);

	// play audio

	if (SDL_Init(SDL_INIT_AUDIO) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}

	dev = initialise_audio();

	SDL_PauseAudioDevice(dev, 0);

	// generate audio

	// for (int i = 0; i < 1; i++) {
	// 	oscillators[i].oscillator.volume = 100;
	// 	oscillators[i].oscillator.width = 128;
	// 	oscillators[i].oscillator.waveform = 0b10;
	// 	oscillators[i].oscillator.note = 30;
	// 	oscillators[i].oscillator.low = 254;
	// }

	oscillators[0].oscillator.waveform = 0b00;
	oscillators[0].oscillator.volume = 25;
	oscillators[0].oscillator.high = 0;
	oscillators[0].oscillator.low = 90;
	oscillators[0].oscillator.width = 128;

	oscillators[1].oscillator.waveform = 0b00;
	oscillators[1].oscillator.volume = 25;
	oscillators[1].oscillator.high = 0;
	oscillators[1].oscillator.low = 128;
	oscillators[1].oscillator.width = 128;

	oscillators[1].oscillator.note = 38;
	SDL_Delay(250);
	oscillators[1].oscillator.note = 0;
	SDL_Delay(50);

	oscillators[1].oscillator.note = 45;
	SDL_Delay(250);
	oscillators[1].oscillator.note = 0;
	SDL_Delay(50);
	oscillators[1].oscillator.note = 47;
	SDL_Delay(250);
	oscillators[1].oscillator.note = 0;
	SDL_Delay(50);
	oscillators[1].oscillator.note = 48;
	SDL_Delay(250);
	oscillators[1].oscillator.note = 0;
	SDL_Delay(50);
	oscillators[1].oscillator.note = 45;
	SDL_Delay(250);
	oscillators[1].oscillator.note = 0;
	SDL_Delay(50);

	oscillators[1].oscillator.note = 47;
	SDL_Delay(250);
	oscillators[1].oscillator.note = 0;
	SDL_Delay(50);
	oscillators[1].oscillator.note = 48;
	SDL_Delay(250);
	oscillators[1].oscillator.note = 0;
	SDL_Delay(50);
	oscillators[1].oscillator.note = 50;
	SDL_Delay(250);
	oscillators[1].oscillator.note = 0;
	SDL_Delay(50);
	oscillators[1].oscillator.note = 47;
	SDL_Delay(250);
	oscillators[1].oscillator.note = 0;
	SDL_Delay(50);

	oscillators[1].oscillator.note = 48;
	SDL_Delay(500);
	oscillators[1].oscillator.note = 0;
	SDL_Delay(100);
	oscillators[1].oscillator.note = 52;
	SDL_Delay(500);
	oscillators[1].oscillator.note = 0;
	SDL_Delay(100);

	oscillators[1].oscillator.note = 50;
	SDL_Delay(250);
	oscillators[1].oscillator.note = 0;
	SDL_Delay(50);
	oscillators[1].oscillator.note = 48;
	SDL_Delay(250);
	oscillators[1].oscillator.note = 0;
	SDL_Delay(50);
	oscillators[1].oscillator.note = 47;
	SDL_Delay(250);
	oscillators[1].oscillator.note = 0;
	SDL_Delay(50);
	oscillators[1].oscillator.note = 50;
	SDL_Delay(250);
	oscillators[1].oscillator.note = 0;
	SDL_Delay(50);


	oscillators[1].oscillator.note = 48;
	SDL_Delay(250);
	oscillators[1].oscillator.note = 0;
	SDL_Delay(50);
	oscillators[1].oscillator.note = 47;
	SDL_Delay(250);
	oscillators[1].oscillator.note = 0;
	SDL_Delay(50);
	oscillators[1].oscillator.note = 45;
	SDL_Delay(250);
	oscillators[1].oscillator.note = 0;
	SDL_Delay(50);
	oscillators[1].oscillator.note = 48;
	SDL_Delay(250);
	oscillators[1].oscillator.note = 0;
	SDL_Delay(50);

	oscillators[1].oscillator.note = 47;
	SDL_Delay(500);
	oscillators[1].oscillator.note = 0;
	SDL_Delay(100);
	oscillators[1].oscillator.note = 44;
	SDL_Delay(500);
	oscillators[1].oscillator.note = 0;
	SDL_Delay(100);
	// cleanup

	SDL_CloseAudioDevice(dev);

	SDL_Quit();

	return 0;
}
