#include "video.h"
#include "menu_bg.h"

int main(){
	reset_dispcnt();
	set_video_mode(0);
	set_background_number(2);

	set_background(menu_bgPal, menu_bgPalLen, menu_bgTiles, menu_bgTilesLen, menu_bgMap, menu_bgMapLen);

	return 0;
}
