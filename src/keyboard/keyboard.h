#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../motherboard/motherboard.h"

extern uint8_t key_states[57];
extern uint8_t keyboard_interrupted;

void handle_keyboard_event(SDL_Event event);


#endif
