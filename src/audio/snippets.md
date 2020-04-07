## The Lick
```C
	oscillators[0].oscillator.volume = 10;
	oscillators[0].oscillator.width = 128;
	oscillators[0].oscillator.waveform = 0b00;
	oscillators[1].oscillator.volume = 10;
	oscillators[1].oscillator.waveform = 0b01;
	oscillators[2].oscillator.volume = 10;
	oscillators[2].oscillator.waveform = 0b10;

	oscillators[0].oscillator.low = 100;
	oscillators[1].oscillator.low = 100;
	oscillators[2].oscillator.low = 100;

	oscillators[0].oscillator.note = 38;
	oscillators[1].oscillator.note = 45;
	oscillators[2].oscillator.note = 50;
	SDL_Delay(200);

	oscillators[0].oscillator.note = 40;
	oscillators[1].oscillator.note = 47;
	oscillators[2].oscillator.note = 52;
	SDL_Delay(200);

	oscillators[0].oscillator.note = 41;
	oscillators[1].oscillator.note = 48;
	oscillators[2].oscillator.note = 53;
	SDL_Delay(200);

	oscillators[0].oscillator.note = 43;
	oscillators[1].oscillator.note = 50;
	oscillators[2].oscillator.note = 55;
	SDL_Delay(200);

	oscillators[0].oscillator.note = 40;
	oscillators[1].oscillator.note = 47;
	oscillators[2].oscillator.note = 52;
	SDL_Delay(400);

	oscillators[0].oscillator.note = 36;
	oscillators[1].oscillator.note = 43;
	oscillators[2].oscillator.note = 48;
	SDL_Delay(200);

	// oscillators[0].oscillator.low = 255;
	// oscillators[1].oscillator.low = 255;
	// oscillators[2].oscillator.low = 255;

	oscillators[0].oscillator.note = 38;
	oscillators[1].oscillator.note = 45;
	oscillators[2].oscillator.note = 50;
	SDL_Delay(600);
```
## Pulse Low-Pass Sweep
```C
	oscillators[0].oscillator.volume = 20;
	oscillators[0].oscillator.width = 128;
	oscillators[0].oscillator.waveform = 0b00;

	for (uint8_t i = 254; i > 0; i--) {
		oscillators[0].oscillator.low = i;
		oscillators[0].oscillator.note = 37;
		SDL_Delay(8);
	}
	for (uint8_t i = 0; i < 254; i++) {
		oscillators[0].oscillator.low = i;
		oscillators[0].oscillator.note = 37;
		SDL_Delay(8);
	}
```

## Pulse Width Sweep

```C
	oscillators[0].oscillator.volume = 20;
	oscillators[0].oscillator.width = 128;
	oscillators[0].oscillator.waveform = 0b00;
	oscillators[0].oscillator.low = 255;

	for (uint8_t i = 255; i > 4; i--) {
		oscillators[0].oscillator.width = i;
		oscillators[0].oscillator.note = 37;
		SDL_Delay(8);
	}
	for (uint8_t i = 4; i < 255; i++) {
		oscillators[0].oscillator.width = i;
		oscillators[0].oscillator.note = 37;
		SDL_Delay(8);
	}
```
