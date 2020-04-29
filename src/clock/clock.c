#include "clock.h"
#include "../audio/audio.h"
#include "../memory/memory.h"
#include "../cpu/cpu.h"

void audio_callback(void *data, Uint8 *stream, int len) {
	float *fstream;

	fstream = (float *) stream;
	for (int i = 0; i < AUDIO_BUFFER_SIZE; i++) {
		for (int j = 0; j < 40; j++) {
			clock_count++;
			if (clock_count == 40000) {
				cpu_pins.interrupt = 1;
				clock_count = 0;
				clock_interrupted = 1;
			}
			do_cpu_cycle();
			do_controller_cycle();
			do_audio_cycle();
			cpu_pins.interrupt = 0;
		}
		generate_sample();
		fstream[i] = audio_pins.out * 0.75;
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

	cpu_pins.reset = 1;
	do_cpu_cycle();
	cpu_pins.reset = 0;

	memcpy(global_memory + 0x0200, preload_program, 0x7DFF);
	memcpy(global_memory + 0x7F00, preload_ihandler, 0xFF);

	// play audio

	if (SDL_Init(SDL_INIT_AUDIO) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}

	dev = initialise_audio();

	SDL_PauseAudioDevice(dev, 0);

	// generate audio

	while (!should_close)
		SDL_Delay(1);

	// cleanup

	SDL_CloseAudioDevice(dev);

	SDL_Quit();

	return 0;
}
