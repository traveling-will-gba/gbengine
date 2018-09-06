#include "video.h"
#include "sprite.h"
#include "menu_bg.h"
#include "metr.h"
#include "vbaprint.h"

#include <unistd.h>
#include <string.h>

#define OFFSET_DOUBLED_8BPP 2

void print(char *label, uint64_t n) {
    char buffer[500];
    sprintf(buffer, "%s: %llu\n", label, n);
    vbaprint(buffer);
}

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

    while(1) {
        set_sprite_attrs(tile_used / 64, &metr);
        set_sprite_attrs(tile_used2 / 64, &metr2);
    }


	return 0;
}
