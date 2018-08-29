#include "video.h"
#include "menu_bg.h"

int main(){
	reset_dispcnt();
	set_video_mode(0);
    enable_background(2);

	set_background(menu_bgPal, menu_bgPalLen, menu_bgTiles, menu_bgTilesLen, menu_bgMap, menu_bgMapLen);

	return 0;
}
