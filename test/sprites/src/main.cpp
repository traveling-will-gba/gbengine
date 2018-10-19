#include "input.h"
#include "video.h"
#include "texture.h"
#include "utils.h"

#include "menu_bg.h"
#include "will_idle.h"
#include "collectable.h"
#include "metr.h"

#include <unistd.h>
#include <string.h>
#include <time.h>

#include <vector>

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

    *reg_dispcnt |= DCNT_OBJ | DCNT_OBJ_1D;

    memset(sprite_pal, 0, 512);

    init_sprite_attr_mem();

    vector <Texture *> texture;

    mem16cpy((uint8_t *)0x05000200, will_idlePal, 32);

    for (int i = 0; i < 1; i++) {
        Texture *t = new Texture(6, will_idlePal, will_idlePalLen, will_idleTiles, will_idleTilesLen, _4BPP);

        t->metadata.cm = 0;
        t->metadata.om = 0;
        t->metadata.sh = 0; // square
        t->metadata.sz = 1;
        t->metadata.pb = 0;
        t->metadata.x = 30 * i;
        t->metadata.y = 144;

        texture.push_back(t);
    }

    mem16cpy((uint8_t *)0x05000200 + 32, collectablePal, 32);

    Texture *col = new Texture(8, collectablePal, collectablePalLen, collectableTiles, collectableTilesLen, _4BPP);

    col->metadata.cm = 0;
    col->metadata.om = 0;
    col->metadata.sh = 0; // square
    col->metadata.sz = 2;
    col->metadata.pb = 1;
    col->metadata.x = 30 * 1;
    col->metadata.y = 60;

    while(1) {
        for (int i=0; i < 8; i++){
            vsync();
        }

        for (size_t i = 0; i < texture.size(); i++) {
            texture[i]->update();
        }

        col->update();
    }

    return 0;
}
