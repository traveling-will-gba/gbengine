#include "input.h"
#include "video.h"
#include "texture.h"
#include "utils.h"

#include "menu_bg.h"
#include "will_idle.h"
#include "collectable.h"
#include "metr.h"
#include "platform_base.h"
#include "platform_middle.h"

#include "tw_will.h"
#include "game.h"

#include <unistd.h>
#include <string.h>
#include <time.h>

#include <vector>

//FIXME Remove this include
#include "physics.h"

#define REG_BG2HOFS         *(vu16*)(REG_BASE+0x0018)
#define REG_BG2VOFS         *(vu16*)(REG_BASE+0x001A)

int main(){
/*    reset_dispcnt();
    set_video_mode(0);
    enable_background(2);

    //set_background(menu_bgPal, menu_bgPalLen, menu_bgTiles, menu_bgTilesLen, menu_bgMap, menu_bgMapLen);
    set_background(background_1Pal, background_1PalLen, background_1Tiles, background_1TilesLen, background_1Map, background_1MapLen);

    volatile uint32_t *reg_dispcnt = (volatile uint32_t *)REG_BASE+0x0000;

    volatile uint16_t *reg_bg0_pos_x = (volatile uint16_t *)REG_BASE+0x0010;
    volatile uint16_t *reg_bg0_pos_y = (volatile uint16_t *)REG_BASE+0x0012;

    volatile uint16_t *reg_bg1_pos_x = (volatile uint16_t *)REG_BASE+0x0014;
    volatile uint16_t *reg_bg1_pos_y = (volatile uint16_t *)REG_BASE+0x0016;

    volatile uint16_t *reg_bg2_pos_x = (volatile uint16_t *)REG_BASE+0x0018;
    volatile uint16_t *reg_bg2_pos_y = (volatile uint16_t *)REG_BASE+0x001A;

    volatile uint16_t *reg_bg3_pos_x = (volatile uint16_t *)REG_BASE+0x001C;
    volatile uint16_t *reg_bg3_pos_y = (volatile uint16_t *)REG_BASE+0x001E;

    *reg_dispcnt |= DCNT_OBJ | DCNT_OBJ_1D;

    memset(sprite_pal, 0, 512);

    TWWill *will = new TWWill(0, 144);

    TWWill *will2 = new TWWill(17, 144);

    Physics::get_physics()->set_target(will);

//    vector <Texture *> texture;
//
  //  for (int i = 0; i < 1; i++) {
    //    Texture *t;
      //  if (i)
 //           t = new Texture(texture[0]);
  //      else
   //         t = new Texture(6, will_idlePal, will_idlePalLen, will_idleTiles, will_idleTilesLen, _4BPP);
//
 //       t->metadata.pr = 0;
  //      t->metadata.cm = 0;
        t->metadata.om = 0;
   //     t->metadata.sh = 0; // square
   //     t->metadata.sz = 1;
        t->metadata.x = 30 * i;
    //    t->metadata.y = 144;
//
 //       texture.push_back(t);
  //  }

    Texture *col = new Texture(8, collectablePal, collectablePalLen, collectableTiles, collectableTilesLen, _4BPP);

    col->metadata.pr = 0;
    col->metadata.cm = 0;
    col->metadata.om = 0;
    col->metadata.sh = 0; // square
    col->metadata.sz = 2;
    col->metadata.x = 30 * 1;
    col->metadata.y = 60;

    Texture *platform_base = new Texture(1, platform_basePal, platform_basePalLen,
                                         platform_baseTiles, platform_baseTilesLen, _4BPP);
    platform_base->metadata.pr = 0;
    platform_base->metadata.cm = 0;
    platform_base->metadata.om = 0;
    platform_base->metadata.sh = 2; // square
    platform_base->metadata.sz = 3;
    platform_base->metadata.x = 100;
    platform_base->metadata.y = 114;


    Texture *platform_middle = new Texture(1, platform_middlePal, platform_middlePalLen,
                                           platform_middleTiles, platform_middleTilesLen, _4BPP);

    platform_middle->metadata.pr = 0;
    platform_middle->metadata.cm = 0;
    platform_middle->metadata.om = 0;
    platform_middle->metadata.sh = 2; // square
    platform_middle->metadata.sz = 3;
    platform_middle->metadata.x = 100;
    platform_middle->metadata.y = 50;

    uint16_t x = 0, y = 0;
    while(1) {
//        for (int i = 0; i < 8; i++) {
//            REG_BG2HOFS = x;
//            x += 1;
//            vsync();
//        }

        will->update();
        will->draw();

        will2->update();
        will2->draw();

        Physics::get_physics()->do_collisions();
//        for (size_t i = 0; i < texture.size(); i++) {
//            texture[i]->update();
//        }

        col->update();

        platform_base->update();
        platform_middle->update();
    }
*/
    reset_dispcnt();

    Texture::init_sprite_attr_mem();

    Game game;
    game.run();

    return 0;
}
