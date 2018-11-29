#include "input.h"
#include <vector>

volatile unsigned int *buttons_mem = (volatile unsigned int *)0x04000130;

int pressed_state[N_BUTTON];
uint64_t key_update[N_BUTTON];
uint64_t update_counter;

void check_buttons_states() {
    update_counter++;

	for(int i = 0; i < N_BUTTON; i++) {
        int pressed = !((*buttons_mem) & (1 << i));

        if (pressed == pressed_state[i]) continue;

        pressed_state[i] = pressed;
        key_update[i] = update_counter;
	}
}

bool pressed(int button) {
	return pressed_state[32 - __builtin_clz(button) - 1] && key_update[32 - __builtin_clz(button) - 1] == update_counter;
}

bool pressing(int button) {
	return pressed_state[32 - __builtin_clz(button) - 1];
}
