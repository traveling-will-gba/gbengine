#include "tw_level.h"
#include "video.h"
#include "b0.h"
#include "b1.h"
#include "b2.h"
#include "tw_will.h"
#include "physics.h"
#include "tw_platform.h"
#include "tw_collectable.h"

#include "level1.h"

const int max_platforms_loaded = 16;
const int platform_width = 16;
const int screen_width = 240;

TWLevel::TWLevel() {
    reset_dispcnt();
    set_video_mode(0);
    enable_background(0);
    enable_background(1);
    enable_background(2);

    m_backgrounds.clear();
    m_backgrounds.push_back(new Background(b0Pal, b0PalLen, b0Tiles, b0TilesLen, b0Map, b0MapLen, 0, 0, 0, 1, 0));
    m_backgrounds.push_back(new Background(b1Pal, b1PalLen, b1Tiles, b1TilesLen, b1Map, b1MapLen, 1, 0, 0, 1, 0));
    m_backgrounds.push_back(new Background(b2Pal, b2PalLen, b2Tiles, b2TilesLen, b2Map, b2MapLen, 2, 0, 0, 2, 0));

    m_backgrounds[0]->set_frames_to_skip(2);

    volatile uint32_t *reg_dispcnt = (volatile uint32_t *)REG_BASE+0x0000;
    *reg_dispcnt |= DCNT_OBJ | DCNT_OBJ_1D;

    m_done = false;

    Texture::init_sprite_attr_mem();

    TWWill *will = new TWWill(10, 127);

    TWPlatform *floor_plats[max_platforms_loaded];

    for (int i = 0; i < max_platforms_loaded; i++) {
        if (i == 0)
            floor_plats[i] = new TWPlatform(i * platform_width, 148, true);
        else
            floor_plats[i] = new TWPlatform(i * platform_width, 148, floor_plats[0]->textures(), true);

        add_child(floor_plats[i]);
    }

    platform_num = level1_len;
    platform_idx = max_platforms_loaded;

    for (int i = 0; i < platform_num; i++) {
        platform_height[i] = 160 - level1_platform_heights[i] / 3; // 480 -> 160
        collectable_height[i] = 160 - level1_collectable_heights[i] / 3; // 480 -> 160
        collectable_present[i] = level1_collectable_present[i];
    }

    for (int i = 0; i < max_platforms_loaded; i++) {
        if (i == 0)
            platforms[i] = new TWPlatform(i * platform_width, platform_height[i]);
        else
            platforms[i] = new TWPlatform(i * platform_width, platform_height[i], platforms[0]->textures());

        add_child(platforms[i]);
        q.push(platforms[i]);
    }

    add_child(will);

    TWCollectable *cols[max_platforms_loaded];
    for (int i = 0; i < max_platforms_loaded; i++) {
        if (i == 0)
            cols[i] = new TWCollectable(i * platform_width, collectable_height[i]);
        else
            cols[i] = new TWCollectable(i * platform_width, collectable_height[i], cols[0]->texture());

        platforms[i]->set_collectable(cols[i]);
        cols[i]->set_visibility(collectable_present[i]);
    }

    for (auto background : m_backgrounds) {
        add_child(background);
    }

    Physics::get_physics()->set_target(will);
}

void TWLevel::update_self(uint64_t dt) {
    while (1) {
        if (platform_idx * platform_width <= m_backgrounds[0]->x() + screen_width) {
            auto plat = q.front();
            q.pop();

            plat->set_x(platform_idx * platform_width - m_backgrounds[0]->x());
            plat->set_y(platform_height[platform_idx]);

            plat->collectable()->set_y(collectable_height[platform_idx]);

            q.push(plat);
        } else break;

        platform_idx++;
    }

    if (dt % 2 == 0) {
        for (int i = 0; i < max_platforms_loaded; i++) {
            platforms[i]->set_x(platforms[i]->x() - 1);
//            platforms[i]->update_bounding_box();
        }
    }
}

void TWLevel::draw_self() {

}
