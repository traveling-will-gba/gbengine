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

  //  volatile uint32_t *reg_dispcnt = (volatile uint32_t *)REG_BASE+0x0000;

    REG_DISPCNT |= DCNT_OBJ | DCNT_OBJ_1D;
//    *reg_dispcnt |= DCNT_OBJ | DCNT_OBJ_1D;

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
    
//    print("%d", ((uint16_t *)sprite_mem)[0]);

    while(1) {
        for (int i=0; i < 8;i++){
            vsync();
        }

        texture.update();
    }

    return 0;
}
