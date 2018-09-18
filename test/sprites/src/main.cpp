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

struct reg_tmxcnt {
    uint8_t fr : 2;
    uint8_t cm : 1;
    uint8_t filler : 3;
    uint8_t i : 1;
    uint8_t enable : 1;
    uint8_t filler2;
};

void vsync() {
    while(REG_VCOUNT >= 160);
    while(REG_VCOUNT < 160);
}

int main(){
    reset_dispcnt();
    set_video_mode(0);
    enable_background(2);

    set_background(menu_bgPal, menu_bgPalLen, menu_bgTiles, menu_bgTilesLen, menu_bgMap, menu_bgMapLen);

    REG_DISPCNT |= DCNT_OBJ | DCNT_OBJ_1D;

    memset(sprite_pal, 0, 512);
//    set_sprite_pal(will_idlePal, will_idlePalLen);

    init_sprite_attr_mem();

    Texture texture(6, will_idlePal, will_idlePalLen, will_idleTiles, will_idleTilesLen);

    texture.metadata.cm = 1;
    texture.metadata.om = 0;
    texture.metadata.sh = 0; // square
    texture.metadata.sz = 1;
    texture.metadata.pb = texture.pallete_id;
    texture.metadata.x = 30;
    texture.metadata.y = 144;

    uint32_t sprite_num = 8;
    struct attr will_attr[8];

    for (int i = 0; i < sprite_num; i++) {
        uint32_t tile_used;
        set_sprite(will_idleTiles, will_idleTilesLen, &tile_used);

        will_attr[i].cm = 1;
        will_attr[i].om = 0;
        will_attr[i].sh = 0; // square
        will_attr[i].sz = 1;
        will_attr[i].tid = (tile_used + 12) * OFFSET_DOUBLED_8BPP;
        will_attr[i].pb = 0;
        will_attr[i].x = i * 30;
        will_attr[i].y = 144;
    }

    while(1) {
        for (int i=0; i < 8;i++){
            vsync();
        }

        texture.update();
    }

    return 0;
}
