#include "video.h"
#include "menu_bg.h"
#include "metr.h"

#include <string.h>

int main(){
	reset_dispcnt();
	set_video_mode(0);
    enable_background(2);

	set_background(menu_bgPal, menu_bgPalLen, menu_bgTiles, menu_bgTilesLen, menu_bgMap, menu_bgMapLen);

    memset(sprite_pal, 0, 512);
    set_sprite_pal(metrPal, metrPalLen);
    int sprite_used;

	REG_DISPCNT |= DCNT_OBJ | DCNT_OBJ_1D;

    set_sprite(metrTiles, metrTilesLen, &sprite_used);
    set_sprite_attr(sprite_used);

    set_sprite(metrTiles, metrTilesLen, &sprite_used);
    set_sprite_attr(sprite_used);

    char aux[512];
    sprintf(aux, "%d\n", sprite_used);
    vbaprint(aux);


	return 0;
}
