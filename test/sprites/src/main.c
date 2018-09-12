#include "input.h"
#include "video.h"
#include "sprite.h"
#include "utils.h"

#include "menu_bg.h"
#include "will_idle.h"
#include "metr.h"

#include <unistd.h>
#include <string.h>
#include <time.h>

#define OFFSET_DOUBLED_8BPP 2

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
    set_sprite_pal(will_idlePal, will_idlePalLen);

	REG_DISPCNT |= DCNT_OBJ | DCNT_OBJ_1D;

    init_sprite_attr_mem();

    uint32_t sprite_num = 8;
    struct attr will_attr[8];

    for (int i = 0; i < sprite_num; i++) {
        int tile_used;
        set_sprite(will_idleTiles, will_idleTilesLen, &tile_used);
        print("tile_used", tile_used);

        will_attr[i].cm = 1;
        will_attr[i].om = 0;
        will_attr[i].sh = 0; // square
        will_attr[i].sz = 1;
        will_attr[i].tid = (tile_used + 12) * OFFSET_DOUBLED_8BPP;
        will_attr[i].pb = 0;
        will_attr[i].x = i * 30;
        will_attr[i].y = 144;
    }

    uint16_t *data = (uint16_t *)(0x04000000+0x0100);
    struct reg_tmxcnt *cnt = (void *)(0x04000000+0x0102);

    *data = 0;

    cnt->fr = 1;
    cnt->enable = 1;

    uint16_t last = *data;
    uint64_t dt = 0;

    while(1) {
        uint16_t cur = *data;

        dt = cur - last;
        dt /= 1000;

        for (int i = 0; i < sprite_num; i++) {
            will_attr[i].tid = (will_attr[i].tid + 4 * dt) % 24;
            set_sprite_attrs(i, &will_attr[i]);
        }

        last = cur;
    }


	return 0;
}
