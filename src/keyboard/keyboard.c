#include "keyboard.h"
#include "../cpu/cpu.h"

void handle_keyboard_event() {
	const uint8_t *state = SDL_GetKeyboardState(NULL);

	key_states[0] = state[SDL_SCANCODE_LCTRL | SDL_SCANCODE_RCTRL];
	key_states[1] = state[SDL_SCANCODE_LALT | SDL_SCANCODE_RALT];
	key_states[2] = state[SDL_SCANCODE_LSHIFT | SDL_SCANCODE_RSHIFT];
	key_states[3] = state[SDL_SCANCODE_BACKSPACE];
	key_states[4] = state[SDL_SCANCODE_RETURN];
	key_states[5] = state[SDL_SCANCODE_ESCAPE];

	key_states[6] = state[SDL_SCANCODE_LEFT];
	key_states[7] = state[SDL_SCANCODE_RIGHT];
	key_states[8] = state[SDL_SCANCODE_UP];
	key_states[9] = state[SDL_SCANCODE_DOWN];

	key_states[10] = state[SDL_SCANCODE_SPACE];

	key_states[11] = state[SDL_SCANCODE_A];
	key_states[12] = state[SDL_SCANCODE_B];
	key_states[13] = state[SDL_SCANCODE_C];
	key_states[14] = state[SDL_SCANCODE_D];
	key_states[15] = state[SDL_SCANCODE_E];
	key_states[16] = state[SDL_SCANCODE_F];
	key_states[17] = state[SDL_SCANCODE_G];
	key_states[18] = state[SDL_SCANCODE_H];
	key_states[19] = state[SDL_SCANCODE_I];
	key_states[20] = state[SDL_SCANCODE_J];
	key_states[21] = state[SDL_SCANCODE_K];
	key_states[22] = state[SDL_SCANCODE_L];
	key_states[23] = state[SDL_SCANCODE_M];
	key_states[24] = state[SDL_SCANCODE_N];
	key_states[25] = state[SDL_SCANCODE_O];
	key_states[26] = state[SDL_SCANCODE_P];
	key_states[27] = state[SDL_SCANCODE_Q];
	key_states[28] = state[SDL_SCANCODE_R];
	key_states[29] = state[SDL_SCANCODE_S];
	key_states[30] = state[SDL_SCANCODE_T];
	key_states[31] = state[SDL_SCANCODE_U];
	key_states[32] = state[SDL_SCANCODE_V];
	key_states[33] = state[SDL_SCANCODE_W];
	key_states[34] = state[SDL_SCANCODE_X];
	key_states[35] = state[SDL_SCANCODE_Y];
	key_states[36] = state[SDL_SCANCODE_Z];

	key_states[37] = state[SDL_SCANCODE_0];
	key_states[38] = state[SDL_SCANCODE_1];
	key_states[39] = state[SDL_SCANCODE_2];
	key_states[40] = state[SDL_SCANCODE_3];
	key_states[41] = state[SDL_SCANCODE_4];
	key_states[42] = state[SDL_SCANCODE_5];
	key_states[43] = state[SDL_SCANCODE_6];
	key_states[44] = state[SDL_SCANCODE_7];
	key_states[45] = state[SDL_SCANCODE_8];
	key_states[46] = state[SDL_SCANCODE_9];

	key_states[47] = state[SDL_SCANCODE_MINUS];
	key_states[48] = state[SDL_SCANCODE_EQUALS];

	key_states[49] = state[SDL_SCANCODE_COMMA];
	key_states[50] = state[SDL_SCANCODE_PERIOD];
	key_states[51] = state[SDL_SCANCODE_SLASH];

	key_states[52] = state[SDL_SCANCODE_SEMICOLON];
	key_states[53] = state[SDL_SCANCODE_APOSTROPHE];
	key_states[54] = state[SDL_SCANCODE_BACKSLASH];

	key_states[55] = state[SDL_SCANCODE_LEFTBRACKET];
	key_states[56] = state[SDL_SCANCODE_RIGHTBRACKET];

	keyboard_interrupted = 1;
	cpu_pins.interrupt = 1;
}
