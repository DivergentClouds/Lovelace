#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SDL2/SDL.h>

uint8_t key_states[57];
uint8_t keyboard_interrupted = 0;

void handle_keyboard_event();


#endif
