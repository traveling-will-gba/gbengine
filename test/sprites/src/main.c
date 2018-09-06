#include "video.h"
#include "menu_bg.h"
#include "metr.h"

#include <string.h>

void print(char *label, int n) {
    char buffer[500];
    sprintf(buffer, "%s: %d\n", label, n);
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

    print("sp1:", tile_used);
 //   set_sprite_attr(tile_used);
    
    struct attr metr;
    metr.om = 0;
	metr.sh = 0; // square
	metr.sz = 3; // 11 -> size 64x64	
	metr.tid = tile_used;
	metr.pb = 0;
	metr.x = 10;
	metr.y = 40;
    metr.cm = 1;

    int tile_used2;
    set_sprite(metrTiles, metrTilesLen, &tile_used2);

    print("sp2:", tile_used2);
 //   set_sprite_attr(tile_used);
    
    struct attr metr2;
    metr2.om = 0;
	metr2.sh = 0; // square
	metr2.sz = 3; // 11 -> size 64x64	
	metr2.tid = tile_used2;
	metr2.pb = 0;
	metr2.x = 60;
	metr2.y = 40;
    metr2.cm = 1;

    while(1) {
        set_sprite_attrs(tile_used / 64, &metr);
        set_sprite_attrs(tile_used2 / 64, &metr2);
    }
/*
    vbaprint("oam:\n");
    for (int i = 0; i < 8; i++){
        char abcd2[500];
        sprintf(abcd2, "%d\n", *(((char *)0x07000000) + i));
        vbaprint(abcd2);
    }
*/
	return 0;
}
