#include "tw_level.h"
#include "video.h"
#include "level1_b0.h"
#include "level1_b1.h"
#include "level1_b2.h"
#include "physics.h"
#include "tw_platform.h"
#include "tw_collectable.h"

#include "level1.h"
#include "menu.h"
#include "input.h"

const int max_platforms_loaded = 16;
const int platform_width = 16;
const int collectable_width = 8;
const int screen_width = 240;

TWLevel::TWLevel(int level, bool playable = true) {
    reset_dispcnt();
    set_video_mode(0);
    enable_background(0);
    enable_background(1);
    enable_background(2);

    volatile uint32_t *reg_dispcnt = (volatile uint32_t *)REG_BASE + 0x0000;
    *reg_dispcnt |= DCNT_OBJ | DCNT_OBJ_1D;

    m_current_level = level;
    m_playable = playable;
    m_done = false;
    m_is_level_ending = false;

    Texture::init_sprite_attr_mem();

    if (m_playable) {
        will = new TWWill(10, 127);
    }

    load_level_design(level);
    load_backgrounds(level);

    if (m_playable) {
        add_child(will);
        Physics::get_physics()->set_target(will);
    }
}

void TWLevel::dispose() {
    MemoryManager *manager = MemoryManager::get_memory_manager();

    manager->reset_memory();
}

void TWLevel::update_self(uint64_t dt) {
    if (m_playable) {
        while (1) {
            if (platform_idx * platform_width <= m_backgrounds[0]->x() + screen_width) {
                auto plat = q.front();
                q.pop();

                plat->set_x(platform_idx * platform_width - m_backgrounds[0]->x());
                plat->set_y(platform_height[platform_idx]);

                plat->collectable()->set_y(collectable_height[platform_idx]);
                plat->collectable()->set_visibility(collectable_present[platform_idx]);

                q.push(plat);
            } else break;

            platform_idx++;
        }

        int outer_x = screen_width + 10;

        if (will->x() >= outer_x) {
            m_done = true;
            print("level ended\n");
            // FIXME remove this exit() call
            exit(1);
        }

        if (platform_idx == platform_num && !m_is_level_ending) {
            int level_speed_x = m_backgrounds[0]->speed_x();

            will->set_speed_x(level_speed_x);

            for (int i=0; i<m_backgrounds.size();i++) {
                m_backgrounds[i]->set_speed_x(0);
            }

            m_is_level_ending = true;
        }
        else if (!m_is_level_ending) {
            if (dt % 2 == 0) {
                for (int i = 0; i < max_platforms_loaded; i++) {
                    platforms[i]->set_x(platforms[i]->x() - 1);
                }
            }
        }
    } else {
        // control menus
        if (pressed(BUTTON_START)) {
            m_done = true;
        }
    }
}

void TWLevel::draw_self() {

}

void TWLevel::load_backgrounds(int level) {
    m_backgrounds.clear();

    switch(level) {
        case 0: // menu
            m_backgrounds.push_back(new Background(menuPal, menuPalLen, menuTiles, menuTilesLen, menuMap, menuMapLen, 0, 0, 0, 0, 0));
            break;
        case 1: // level 1
            m_backgrounds.push_back(new Background(level1_b0Pal, level1_b0PalLen, level1_b0Tiles, level1_b0TilesLen, level1_b0Map, level1_b0MapLen, 0, 0, 0, 1, 0));
            m_backgrounds.push_back(new Background(level1_b1Pal, level1_b1PalLen, level1_b1Tiles, level1_b1TilesLen, level1_b1Map, level1_b1MapLen, 1, 0, 0, 1, 0));
            m_backgrounds.push_back(new Background(level1_b2Pal, level1_b2PalLen, level1_b2Tiles, level1_b2TilesLen, level1_b2Map, level1_b2MapLen, 2, 0, 0, 2, 0));

            m_backgrounds[0]->set_frames_to_skip(2);
            break;
        default:
            break;
    }

    for (auto background : m_backgrounds)
    {
        add_child(background);
    }
}

void TWLevel::load_level_design(int level) {
    switch(level) {
        case 0: // menu
            // do nothing
            break;
        case 1:
            load_level_objects(level1_len, level1_platform_heights, level1_collectable_heights, level1_collectable_present);
            break;
        default:
            break;
    }
}

void TWLevel::load_level_objects(const int level_len, const int *platform_heights, const int *collectable_heights, const int *collectables_present)
{
    platform_num = level_len;
    platform_idx = max_platforms_loaded;

    // load only platform_num platforms at a time
    for (int i = 0; i < platform_num; i++)
    {
        platform_height[i] = 160 - platform_heights[i] / 3;       // 480 -> 160
        collectable_height[i] = 160 - collectable_heights[i] / 3; // 480 -> 160
        collectable_present[i] = collectables_present[i];
    }

    for (int i = 0; i < max_platforms_loaded; i++)
    {
        if (i == 0)
        {
            floor_plats[i] = new TWPlatform(i * platform_width, 142, true);
        }
        else
        {
            floor_plats[i] = new TWPlatform(i * platform_width, 142, floor_plats[0]->textures(), true);
        }

        add_child(floor_plats[i]);
    }

    for (int i = 0; i < max_platforms_loaded; i++)
    {
        if (i == 0)
        {
            platforms[i] = new TWPlatform(i * platform_width, platform_height[i]);
            collectables[i] = new TWCollectable(i * platform_width + platform_width / 2 - collectable_width / 2,
                collectable_height[i]);
        }
        else
        {
            platforms[i] = new TWPlatform(i * platform_width, platform_height[i], platforms[0]->textures());
            collectables[i] = new TWCollectable(i * platform_width + platform_width / 2 - collectable_width / 2,
                collectable_height[i], collectables[0]->texture());
        }

        platforms[i]->set_collectable(collectables[i]);
        collectables[i]->set_visibility(collectable_present[i]);

        add_child(platforms[i]);
        q.push(platforms[i]);
    }
}