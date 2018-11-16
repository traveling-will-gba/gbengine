#include "tw_level.h"
#include "video.h"
#include "b0.h"
#include "b1.h"
#include "b2.h"
#include "tw_will.h"
#include "physics.h"
#include "tw_platform.h"
#include "utils.h"

TWLevel::TWLevel()
{
    print("teste");
    reset_dispcnt();
    set_video_mode(0);
    enable_background(0);
    enable_background(1);
    enable_background(2);

    m_backgrounds.clear();
    m_backgrounds.push_back(new Background(b0Pal, b0PalLen, b0Tiles, b0TilesLen, b0Map, b0MapLen, 0));
    m_backgrounds.push_back(new Background(b1Pal, b1PalLen, b1Tiles, b1TilesLen, b1Map, b1MapLen, 1));
    m_backgrounds.push_back(new Background(b2Pal, b2PalLen, b2Tiles, b2TilesLen, b2Map, b2MapLen, 2));

    // m_backgrounds[0]->set_speed(1, 0);
    m_backgrounds[1]->set_speed(2, 0);
    // m_backgrounds[2]->set_speed(3, 0);

    volatile uint32_t *reg_dispcnt = (volatile uint32_t *)REG_BASE + 0x0000;
    *reg_dispcnt |= DCNT_OBJ | DCNT_OBJ_1D;

    m_x = m_y = 0;
    mx1 = 3;
    my1 = 0;
    mx2 = my2 = 0;
    m_done = false;

    Texture::init_sprite_attr_mem();

    TWWill *will = new TWWill(10, 128);

    // platform_idx = 0;
    // n_platforms = 90;

    // for (register int i = 0; i < 30; i++) {
    //     if (i)
    //         platforms[i] = new TWPlatform(i * 8, platform_height[i], platforms[0]->texture());
    //     else
    //         platforms[i] = new TWPlatform(i * 8, platform_height[i]);

    //    add_child(platforms[i]);
    // }

    add_child(will);
    Physics::get_physics()->set_target(will);
}

void TWLevel::update_self()
{
    /*while (platform_idx * 8 < m_x + 30 * 8 && platform_idx < n_platforms) {
        platforms[platform_idx % 30]->set_x(platform_idx * 8 - m_x);
        platforms[platform_idx % 30]->set_y(platform_height[platform_idx]);

        platform_idx++;
    }*/

    //    print("before: %d\n", platform_idx);
    //    while (platform_idx * 8 - m_x + 8 < 0) platform_idx++;
    //    print("after: %d\n", platform_idx);

    bool flag = false;
    for (int i = platform_idx, c = 0; i < platform_idx + 30; i++, c++)
    {
        //if (not flag) print("idx: %d, m_x: %d\n", i, m_x);

        //        if (not flag)
        //   print("pos %d\n", i*8-m_x);
        flag = true;
        platforms[c]->set_x(i * 8 - m_x);
        platforms[c]->set_y(platform_height[i]);
        platforms[c]->update_bounding_box();
    }

    /*
    for (size_t i = 0; i < n_platforms; i++) {
        platforms[i]->set_x(i * 8 - m_x);
        platforms[i]->update_bounding_box();
    }*/

    // for (int i=0; i < m_backgrounds.size(); i++) {
    //     m_backgrounds[i]->update_self();
    // }

    m_backgrounds[1]->update_self();
}

void TWLevel::draw_self()
{
}
