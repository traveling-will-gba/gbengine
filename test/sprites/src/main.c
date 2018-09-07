#include "video.h"
#include "input.h"
#include "sprite.h"
#include "menu_bg.h"
#include "metr.h"
#include "vbaprint.h"

#include <unistd.h>
#include <string.h>
#include <time.h>

#define OFFSET_DOUBLED_8BPP 2

void print(char *label, uint64_t n) {
    char buffer[500];
    sprintf(buffer, "%s: %llu\n", label, n);
    vbaprint(buffer);
}

struct reg_tmxcnt {
    uint8_t fr : 2;
    uint8_t cm : 1;
    uint8_t filler : 3;
    uint8_t i : 1;
    uint8_t enable : 1;
    uint8_t filler2;
};

int main(){
	reset_dispcnt();
	set_video_mode(0);
    enable_background(2);

	set_background(menu_bgPal, menu_bgPalLen, menu_bgTiles, menu_bgTilesLen, menu_bgMap, menu_bgMapLen);

    memset(sprite_pal, 0, 512);
    set_sprite_pal(metrPal, metrPalLen);
    int tile_used;

	REG_DISPCNT |= DCNT_OBJ | DCNT_OBJ_1D;

    set_sprite(metrTiles, metrTilesLen, &tile_used);

    struct attr metr;
    metr.cm = 1;
    metr.om = 0;
	metr.sh = 0; // square
	metr.sz = 3; // 11 -> size 64x64	
	metr.tid = tile_used * OFFSET_DOUBLED_8BPP;
	metr.pb = 0;
	metr.x = 10;
	metr.y = 40;

    int tile_used2;
    set_sprite(metrTiles, metrTilesLen, &tile_used2);

    struct attr metr2;
    metr2.cm = 1;
    metr2.om = 0;
	metr2.sh = 0; // square
	metr2.sz = 3; // 11 -> size 64x64	
	metr2.tid = tile_used2 * OFFSET_DOUBLED_8BPP;
	metr2.pb = 0;
	metr2.x = 100;
	metr2.y = 40;

    uint16_t *data = (uint16_t *)(0x04000000+0x0100);
    struct reg_tmxcnt *cnt = (void *)(0x04000000+0x0102);

    *data = 0;

    cnt->fr = 1;
    cnt->enable = 1;

    uint16_t last = *data;

    uint64_t dt = 0;

    int i=0;
    while(1) {
        uint16_t cur = *data;

        dt = cur - last;
        dt /= 1000;

        check_buttons_states();

        set_sprite_attrs(tile_used / 64, &metr);
        set_sprite_attrs(tile_used2 / 64, &metr2);

        if (pressed(BUTTON_LEFT)){
            metr.x = (metr.x - 1 * dt + 240) % 240;
        }else if (pressed(BUTTON_RIGHT)) {
            metr.x = (metr.x + 1 * dt) % 240;
        }

        last = cur;
    }

	return 0;
}
