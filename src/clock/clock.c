#include "clock.h"
#include "../audio/audio.h"
#include "../memory/memory.h"
#include "../cpu/cpu.h"

uint8_t should_close;

void audio_callback(void *data, Uint8 *stream, int len) {
	float *fstream;

	fstream = (float *) stream;
	for (int i = 0; i < AUDIO_BUFFER_SIZE; i++) {
		for (int j = 0; j < 40; j++) {
			do_cpu_cycle();
			do_controller_cycle();
		}
		do_audio_cycle();
		generate_sample();
		fstream[i] = audio_pins.out;
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

	should_close = 0;

	while (!should_close) {
		SDL_Delay(1);
	}

	// cleanup

	SDL_CloseAudioDevice(dev);

	SDL_Quit();

	return 0;
}
