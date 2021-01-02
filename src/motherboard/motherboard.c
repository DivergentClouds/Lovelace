#include "motherboard.h"

// definitions

uint8_t should_close = 0;
uint16_t clock_count = 0;

uint8_t clock_interrupted = 0;

SDL_mutex *fcMutex;
int fcMutexStatus;

void audio_callback(void *data, Uint8 *stream, int len) {
	float *fstream;
	fstream = (float *) stream;
	for (int i = 0; i < CYCLES_PER_CALLBACK; i++) {
		clock_count++;
		if (clock_count >= 40000) {
			fcMutexStatus = SDL_TryLockMutex(fcMutex);
			if (fcMutexStatus == 0) {
				clock_interrupted = 1;
				cpu_pins.interrupt = 1;
				clock_count = 0;
				SDL_UnlockMutex(fcMutex);
			} else if (fcMutexStatus == SDL_MUTEX_TIMEDOUT) {

			} else {
				printf("Failed to lock fcMutex in cpu.c: %s\n", SDL_GetError());
				should_close = 1;
			}
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

int main(int argc, char **argv) {
	SDL_AudioDeviceID dev;
	SDL_Event event;

	fcMutex = SDL_CreateMutex();
	if (!fcMutex) {
		fprintf(stderr, "Couldn't create mutex: %s\n", SDL_GetError());
		should_close = 1;
	}


	reset_registers();
	reset_pins();
	srand(time(NULL));

	cpu_pins.reset = 1;
	do_cpu_cycle();
	cpu_pins.reset = 0;

	memcpy(global_memory + PC_START, preload_program, INT_OFFSET - PC_START - 1);
	memcpy(global_memory + INT_OFFSET, preload_ihandler, 0xFE);

	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}

	dev = initialise_audio();

	SDL_PauseAudioDevice(dev, 0);

	SDL_Window *screen = SDL_CreateWindow("Lovelace",
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
					printf("Quitting Properly\n"); // debug
					should_close = 1;
					break;
				case SDL_KEYDOWN:
				case SDL_KEYUP:
					handle_keyboard_event(event);
					break;
			}
		}
		SDL_Delay(10);
	}

	SDL_UnlockMutex(fcMutex);
	SDL_DestroyMutex(fcMutex);
	SDL_CloseAudioDevice(dev);
	SDL_DestroyWindow(screen);
	SDL_Quit();

	printf("1 if closed successfully: %d \n", should_close); // debug

	return 0;
}
