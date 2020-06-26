#include "clock.h"
#include "../audio/audio.h"
#include "../memory/memory.h"
#include "../cpu/cpu.h"
#include "../keyboard/keyboard.h"

void audio_callback(void *data, Uint8 *stream, int len) {
	float *fstream;
	fstream = (float *) stream;
	for (int i = 0; i < CYCLES_PER_CALLBACK; i++) {
		clock_count++;
		if (clock_count == 40000) {
			// cpu_pins.interrupt = 1;
			clock_count = 0;
			// clock_interrupted = 1;
		}
		do_cpu_cycle();
		do_controller_cycle(); // memory controller
		do_audio_cycle();
		cpu_pins.interrupt = 0;
	}
	for (int i = 0; i < AUDIO_BUFFER_SIZE; i++) {
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

int main(int argc, char const **argv) {
	SDL_AudioDeviceID dev;
	SDL_Event event;

	reset_registers();
	reset_pins();
	srand(0xBEADED);

	cpu_pins.reset = 1;
	do_cpu_cycle();
	cpu_pins.reset = 0;

	memcpy(global_memory + PC_START, preload_program, 0x7DFF);
	memcpy(global_memory + INT_OFFSET, preload_ihandler, 0xFE);

	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}

	dev = initialise_audio();

	SDL_PauseAudioDevice(dev, 0);

	SDL_Window *screen = SDL_CreateWindow("Harriet",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		800, 450,
		SDL_WINDOW_RESIZABLE
		| SDL_WINDOW_INPUT_FOCUS);

	SDL_Surface* screenSurface = SDL_GetWindowSurface(screen);

	while (!should_close) {
		// to prevent cpu eating (not working very well)
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0x00, 0x00, 0x00));
		SDL_UpdateWindowSurface(screen);
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					printf("quitting\n"); // debug
					should_close = 1;
					break;
				case SDL_KEYDOWN:
				case SDL_KEYUP:
					handle_keyboard_event(event);
					break;
			}
			// handle keyboard and window events
		}
		SDL_Delay(10);
	}

	SDL_CloseAudioDevice(dev);
	SDL_DestroyWindow(screen);
	SDL_Quit();
	printf("%d \n", should_close); // debug

	return 0;
}
