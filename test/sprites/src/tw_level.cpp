#include "tw_level.h"
#include "video.h"
#include "background_0.h"
#include "background_1.h"
#include "background_2.h"
#include "b0.h"
#include "b1.h"
#include "b2.h"
#include "tw_will.h"
#include "physics.h"
#include "tw_platform.h"

#define REG_BG2HOFS *(vu16*)(REG_BASE+0x0018)
#define REG_BG2VOFS *(vu16*)(REG_BASE+0x001A)

#define REG_BG0HOFS *(vu16*)(REG_BASE+0x0010)
#define REG_BG0VOFS *(vu16*)(REG_BASE+0x0012)

#define REG_BG1HOFS *(vu16*)(REG_BASE+0x0014)
#define REG_BG1VOFS *(vu16*)(REG_BASE+0x0016)

TWLevel::TWLevel() {
    reset_dispcnt();
    set_video_mode(0);
    enable_background(0);
    enable_background(1);
    enable_background(2);

    bla(b2Pal, b2Tiles, b2TilesLen, b2Map, b2MapLen,
        b1Pal, b1Tiles, b1TilesLen, b1Map, b1MapLen,
        b0Pal, b0Tiles, b0TilesLen, b0Map, b0MapLen);

//    set_background0(background_1Pal, background_1PalLen, background_1Tiles, background_1TilesLen, background_1Map, background_1MapLen);
  //  set_background(background_2Pal, background_2PalLen, background_2Tiles, background_2TilesLen, background_2Map, background_2MapLen);
    //set_background2(background_1Pal, background_1PalLen, background_1Tiles, background_1TilesLen, background_1Map, background_1MapLen);
    //set_background(background_0Pal, background_0PalLen, background_0Tiles, background_0TilesLen, background_0Map, background_0MapLen);

    volatile uint32_t *reg_dispcnt = (volatile uint32_t *)REG_BASE+0x0000;
    *reg_dispcnt |= DCNT_OBJ | DCNT_OBJ_1D;

    m_x = m_y = 0;
    mx1 = 3;
    my1 = 0;
    mx2 = my2 = 0;
    m_done = false;

    init_sprite_attr_mem();
    
    TWWill *will = new TWWill(10, 128);

    platform_idx = 0;
    n_platforms = 90;


    for (register int i = 0; i < 30; i++) {
        if (i)
            platforms[i] = new TWPlatform(i * 8, platform_height[i], platforms[0]->texture());
        else
            platforms[i] = new TWPlatform(i * 8, platform_height[i]);

//        add_child(platforms[i]);
    }

    add_child(will);
    Physics::get_physics()->set_target(will);
}

void TWLevel::update_self() {
    /*while (platform_idx * 8 < m_x + 30 * 8 && platform_idx < n_platforms) {
        platforms[platform_idx % 30]->set_x(platform_idx * 8 - m_x);
        platforms[platform_idx % 30]->set_y(platform_height[platform_idx]);

        platform_idx++;
    }*/

//    print("before: %d\n", platform_idx);
//    while (platform_idx * 8 - m_x + 8 < 0) platform_idx++;
//    print("after: %d\n", platform_idx);
    
    bool flag = false;
    for (int i = platform_idx, c = 0; i < platform_idx + 30; i++, c++) {
        //if (not flag) print("idx: %d, m_x: %d\n", i, m_x);

//        if (not flag)
     //   print("pos %d\n", i*8-m_x);
        flag=true;
        platforms[c]->set_x(i * 8 - m_x);
        platforms[c]->set_y(platform_height[i]);
        platforms[c]->update_bounding_box();
    }

    /*
    for (size_t i = 0; i < n_platforms; i++) {
        platforms[i]->set_x(i * 8 - m_x);
        platforms[i]->update_bounding_box();
    }*/

    REG_BG0HOFS = m_x;
    m_x += 3;

    REG_BG1HOFS = mx1;
    mx1 += 2;

    REG_BG2HOFS = mx2;
    mx2 += 1;
}

void TWLevel::draw_self() {

}
