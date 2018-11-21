#include "video.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

volatile uint32_t *reg_dispcnt = (volatile uint32_t *)REG_BASE+0x0000;

void vsync() {
    while(REG_VCOUNT >= 160);
    while(REG_VCOUNT < 160);
}

void reset_dispcnt() {
	*reg_dispcnt = 0;
}

void set_video_mode(int video_mode) {
	*reg_dispcnt |= video_mode;
}

void enable_background(int background) {
	switch (background) {
		case 0:
			*reg_dispcnt |= 0x0100;
		case 1:
			*reg_dispcnt |= 0x0200;
		case 2:
			*reg_dispcnt |= 0x0400;
		case 3:
			*reg_dispcnt |= 0x0800;
	}
}
