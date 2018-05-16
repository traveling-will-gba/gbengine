#include "video.h"

#include <string.h>

void reset_dispcnt() {
	REG_DISPCNT = 0;
}

void set_video_mode(int video_mode) {
	REG_DISPCNT |= video_mode;
}

void set_background_number(int background) {
	switch (background) {
		case 0:
			REG_DISPCNT |= 0x0100;
		case 1:
			REG_DISPCNT |= 0x0200;
		case 2:
			REG_DISPCNT |= 0x0400;
		case 3:
			REG_DISPCNT |= 0x0800;
	}
}

void set_background(const void *pal, int pal_len, const void *tiles, int tiles_len, const void *map, int map_len) {
	// Load palette
	memcpy(pal_bg_mem, pal, pal_len);
	// Load tiles into CBB 0
	memcpy(&tile_mem[0][0], tiles, tiles_len);
	// Load map into SBB 31
	memcpy(&se_mem[31][0], map, map_len);

	REG_BG2CNT = BG_CBB(0) | BG_SBB(31) | BG_8BPP | BG_REG_64x32;
}
