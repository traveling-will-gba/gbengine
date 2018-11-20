#include "tw_level.h"
#include "video.h"
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

    volatile uint32_t *reg_dispcnt = (volatile uint32_t *)REG_BASE+0x0000;
    *reg_dispcnt |= DCNT_OBJ | DCNT_OBJ_1D;

    m_x = m_y = 0;
    mx1 = 3;
    my1 = 0;
    mx2 = my2 = 0;
    m_done = false;

    init_sprite_attr_mem();
    
    TWWill *will = new TWWill(10, 128);

    platform_idx = 9;
    n_platforms = 90;

    srand(0);
    for (int i = 0; i < 500 / 4; i++) {
        int aux = rand() % 160;
        for (int j = 0; j < 4; j++) {
            platform_height[i * 4 + j] = 145;
        }
    }


    for (int i = 0; i < 9; i++) {
        if (i == 0)
            platforms[i] = new TWPlatform(i * 32, platform_height[i]);
        else
            platforms[i] = new TWPlatform(i * 32, platform_height[i], platforms[0]->textures());

        add_child(platforms[i]);
        q.push(platforms[i]);
    }

    add_child(will);
    Physics::get_physics()->set_target(will);
}

void TWLevel::update_self(uint64_t dt) {
    while (1) {
        print("%d\n", platform_idx);
        if (platform_idx * 32 <= m_x + 240) {
            auto aux = q.front();
            q.pop();

            aux->set_x(platform_idx * 32 - m_x);
            aux->set_y(platform_height[platform_idx]);

            q.push(aux);
        } else break;
        platform_idx++;
    }

    for (int i = 0; i < 10; i++) {
        platforms[i]->set_x(platforms[i]->x() - 2);
    }

    REG_BG0HOFS = m_x;
    m_x += 2;

    REG_BG1HOFS = mx1;
    mx1 += 1;

    REG_BG2HOFS = mx2;
    if (dt % 2 == 0) mx2++;
}

void TWLevel::draw_self() {

}
