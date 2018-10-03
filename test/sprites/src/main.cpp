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

#include <vector>

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

    volatile uint32_t *reg_dispcnt = (volatile uint32_t *)REG_BASE+0x0000;

//    REG_DISPCNT |= DCNT_OBJ | DCNT_OBJ_1D;
    *reg_dispcnt |= DCNT_OBJ | DCNT_OBJ_1D;

    memset(sprite_pal, 0, 512);
//    set_sprite_pal(will_idlePal, will_idlePalLen);

    init_sprite_attr_mem();

    vector <Texture *> texture;

    for (int i = 0; i < 5; i++) {
        Texture *t = new Texture(6, will_idlePal, will_idlePalLen, will_idleTiles, will_idleTilesLen);

        t->metadata.cm = 1;
        t->metadata.om = 0;
        t->metadata.sh = 0; // square
        t->metadata.sz = 1;
        t->metadata.pb = t->pallete_id;
        t->metadata.x = 30 * i;
        t->metadata.y = 144;

        texture.push_back(t);
    }

    while(1) {
        for (int i=0; i < 8; i++){
            vsync();
        }

        for (size_t i = 0; i < texture.size(); i++) {
            texture[i]->update();
            print("%d %lu\n", i, texture[i]->metadata.tid);
        }
    }

    return 0;
}
