#include "keyboard.h"
#include "../cpu/cpu.h"

void handle_keyboard_event(SDL_Event event) {
	// const uint8_t *state = SDL_GetKeyboardState(NULL);
	key_states[0] = (event.key.keysym.sym == SDLK_LCTRL && event.key.state == SDL_PRESSED)
			|| (event.key.keysym.sym == SDLK_RCTRL && event.key.state == SDL_PRESSED);
	key_states[1] = (event.key.keysym.sym == SDLK_LALT && event.key.state == SDL_PRESSED)
			|| (event.key.keysym.sym == SDLK_RALT && event.key.state == SDL_PRESSED);
	key_states[2] = (event.key.keysym.sym == SDLK_LSHIFT && event.key.state == SDL_PRESSED)
			|| (event.key.keysym.sym == SDLK_RSHIFT && event.key.state == SDL_PRESSED);
	key_states[3] = event.key.keysym.sym == SDLK_BACKSPACE && event.key.state == SDL_PRESSED;
	key_states[4] = event.key.keysym.sym == SDLK_RETURN && event.key.state == SDL_PRESSED;
	key_states[5] = event.key.keysym.sym == SDLK_ESCAPE && event.key.state == SDL_PRESSED;

	key_states[6] = event.key.keysym.sym == SDLK_LEFT && event.key.state == SDL_PRESSED;
	key_states[7] = event.key.keysym.sym == SDLK_RIGHT && event.key.state == SDL_PRESSED;
	key_states[8] = event.key.keysym.sym == SDLK_UP && event.key.state == SDL_PRESSED;
	key_states[9] = event.key.keysym.sym == SDLK_DOWN && event.key.state == SDL_PRESSED;

	key_states[10] = event.key.keysym.sym == SDLK_SPACE && event.key.state == SDL_PRESSED;

	key_states[11] = event.key.keysym.sym == SDLK_a && event.key.state == SDL_PRESSED;
	key_states[12] = event.key.keysym.sym == SDLK_b && event.key.state == SDL_PRESSED;
	key_states[13] = event.key.keysym.sym == SDLK_c && event.key.state == SDL_PRESSED;
	key_states[14] = event.key.keysym.sym == SDLK_d && event.key.state == SDL_PRESSED;
	key_states[15] = event.key.keysym.sym == SDLK_e && event.key.state == SDL_PRESSED;
	key_states[16] = event.key.keysym.sym == SDLK_f && event.key.state == SDL_PRESSED;
	key_states[17] = event.key.keysym.sym == SDLK_g && event.key.state == SDL_PRESSED;
	key_states[18] = event.key.keysym.sym == SDLK_h && event.key.state == SDL_PRESSED;
	key_states[19] = event.key.keysym.sym == SDLK_i && event.key.state == SDL_PRESSED;
	key_states[20] = event.key.keysym.sym == SDLK_j && event.key.state == SDL_PRESSED;
	key_states[21] = event.key.keysym.sym == SDLK_k && event.key.state == SDL_PRESSED;
	key_states[22] = event.key.keysym.sym == SDLK_l && event.key.state == SDL_PRESSED;
	key_states[23] = event.key.keysym.sym == SDLK_m && event.key.state == SDL_PRESSED;
	key_states[24] = event.key.keysym.sym == SDLK_n && event.key.state == SDL_PRESSED;
	key_states[25] = event.key.keysym.sym == SDLK_o && event.key.state == SDL_PRESSED;
	key_states[26] = event.key.keysym.sym == SDLK_p && event.key.state == SDL_PRESSED;
	key_states[27] = event.key.keysym.sym == SDLK_q && event.key.state == SDL_PRESSED;
	key_states[28] = event.key.keysym.sym == SDLK_r && event.key.state == SDL_PRESSED;
	key_states[29] = event.key.keysym.sym == SDLK_s && event.key.state == SDL_PRESSED;
	key_states[30] = event.key.keysym.sym == SDLK_t && event.key.state == SDL_PRESSED;
	key_states[31] = event.key.keysym.sym == SDLK_u && event.key.state == SDL_PRESSED;
	key_states[32] = event.key.keysym.sym == SDLK_v && event.key.state == SDL_PRESSED;
	key_states[33] = event.key.keysym.sym == SDLK_w && event.key.state == SDL_PRESSED;
	key_states[34] = event.key.keysym.sym == SDLK_x && event.key.state == SDL_PRESSED;
	key_states[35] = event.key.keysym.sym == SDLK_y && event.key.state == SDL_PRESSED;
	key_states[36] = event.key.keysym.sym == SDLK_z && event.key.state == SDL_PRESSED;

	key_states[37] = event.key.keysym.sym == SDLK_0 && event.key.state == SDL_PRESSED;
	key_states[38] = event.key.keysym.sym == SDLK_1 && event.key.state == SDL_PRESSED;
	key_states[39] = event.key.keysym.sym == SDLK_2 && event.key.state == SDL_PRESSED;
	key_states[40] = event.key.keysym.sym == SDLK_3 && event.key.state == SDL_PRESSED;
	key_states[41] = event.key.keysym.sym == SDLK_4 && event.key.state == SDL_PRESSED;
	key_states[42] = event.key.keysym.sym == SDLK_5 && event.key.state == SDL_PRESSED;
	key_states[43] = event.key.keysym.sym == SDLK_6 && event.key.state == SDL_PRESSED;
	key_states[44] = event.key.keysym.sym == SDLK_7 && event.key.state == SDL_PRESSED;
	key_states[45] = event.key.keysym.sym == SDLK_8 && event.key.state == SDL_PRESSED;
	key_states[46] = event.key.keysym.sym == SDLK_9 && event.key.state == SDL_PRESSED;

	key_states[47] = event.key.keysym.sym == SDLK_MINUS && event.key.state == SDL_PRESSED;
	key_states[48] = event.key.keysym.sym == SDLK_EQUALS && event.key.state == SDL_PRESSED;

	key_states[49] = event.key.keysym.sym == SDLK_COMMA && event.key.state == SDL_PRESSED;
	key_states[50] = event.key.keysym.sym == SDLK_PERIOD && event.key.state == SDL_PRESSED;
	key_states[51] = event.key.keysym.sym == SDLK_SLASH && event.key.state == SDL_PRESSED;

	key_states[52] = event.key.keysym.sym == SDLK_SEMICOLON && event.key.state == SDL_PRESSED;
	key_states[53] = event.key.keysym.sym == SDLK_QUOTE && event.key.state == SDL_PRESSED;
	key_states[54] = event.key.keysym.sym == SDLK_BACKSLASH && event.key.state == SDL_PRESSED;

	key_states[55] = event.key.keysym.sym == SDLK_LEFTBRACKET && event.key.state == SDL_PRESSED;
	key_states[56] = event.key.keysym.sym == SDLK_RIGHTBRACKET && event.key.state == SDL_PRESSED;

	keyboard_interrupted = 1;
	cpu_pins.interrupt = 1;
}
