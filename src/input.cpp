#include "input.h"
#include <vector>

volatile unsigned int *buttons_mem = (volatile unsigned int *)0x04000130;

int pressed_state[N_BUTTON];

void check_buttons_states() {
	for(int i = 0; i < N_BUTTON; i++) {
		pressed_state[i] = !((*buttons_mem) & (1 << i));
	}
}

bool pressed(int button) {
	return pressed_state[32 - __builtin_clz(button) - 1];
}
