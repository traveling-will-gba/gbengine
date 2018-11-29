#include "tw_level.h"

#include "tw_platform.h"
#include "tw_collectable.h"

#include "video.h"
#include "physics.h"
#include "input.h"

#include "menu.h"
#include "victory.h"
#include "defeat.h"

#include "level1.h"
#include "level1_b0.h"
#include "level1_b1.h"
#include "level1_b2.h"

#include "level2.h"
#include "level2_b0.h"
#include "level2_b1.h"
#include "level2_b2.h"

#include "level3.h"
#include "level4.h"
#include "level5.h"
#include "level6.h"

const int max_platforms_loaded = 16;
const int platform_width = 16;
const int collectable_width = 8;
const int screen_width = 240;

TWLevel::TWLevel(int level, bool playable = true) {
    print("level %d is playable? %d\n", level, playable);
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

TWLevel::~TWLevel() {
    while (!q.empty()) {
        q.pop();
    }

    m_backgrounds.clear();

    for(auto child : m_children) {
        remove_child(child);
    }

    MemoryManager *manager = MemoryManager::get_memory_manager();

    manager->reset_memory();
}

void TWLevel::update_self(uint64_t dt) {
    if (m_playable) {
        if (pressed(BUTTON_SELECT)) {
            m_done = true;
            m_next = MENU_VICTORY;
        }

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
            m_next = MENU_VICTORY;
        }

        if (platform_idx == platform_num && !m_is_level_ending) {
            int level_speed_x = m_backgrounds[0]->speed_x();

            will->set_speed_x(level_speed_x);

            int backgrounds_size = m_backgrounds.size();
            for (int i=0; i<backgrounds_size;i++) {
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
        if (m_current_level == LEVEL_MENU) {
            if (pressed(BUTTON_START)) {
                m_done = true;
                m_next = LEVEL_1;
            }
        }

        if (m_current_level == MENU_VICTORY) {
            if (pressed(BUTTON_B)) {
                m_done = true;
                m_next = LEVEL_MENU;
            }

            if (pressed(BUTTON_A)) {
                m_done = true;
                m_next = NEXT_LEVEL;
            }
        }
    }
}

void TWLevel::draw_self() {
}

void TWLevel::load_backgrounds(int level) {
    m_backgrounds.clear();

    switch(level) {
        case LEVEL_MENU:
            m_backgrounds.push_back(new Background(menuPal, menuPalLen, menuTiles, menuTilesLen, menuMap, menuMapLen, 0, 0, 0, 0, 0));
            break;
        case MENU_VICTORY:
            m_backgrounds.push_back(new Background(victoryPal, victoryPalLen, victoryTiles, victoryTilesLen, victoryMap, victoryMapLen, 0, 0, 0, 0, 0));
            break;
        case MENU_DEFEAT:
            m_backgrounds.push_back(new Background(defeatPal, defeatPalLen, defeatTiles, defeatTilesLen, defeatMap, defeatMapLen, 0, 0, 0, 0, 0));
            break;
        case LEVEL_1:
            m_backgrounds.push_back(new Background(level1_b0Pal, level1_b0PalLen, level1_b0Tiles, level1_b0TilesLen, level1_b0Map, level1_b0MapLen, 0, 0, 0, 1, 0));
            m_backgrounds.push_back(new Background(level1_b1Pal, level1_b1PalLen, level1_b1Tiles, level1_b1TilesLen, level1_b1Map, level1_b1MapLen, 1, 0, 0, 1, 0));
            m_backgrounds.push_back(new Background(level1_b2Pal, level1_b2PalLen, level1_b2Tiles, level1_b2TilesLen, level1_b2Map, level1_b2MapLen, 2, 0, 0, 2, 0));

            m_backgrounds[0]->set_frames_to_skip(2);
            break;
        case LEVEL_2:
            m_backgrounds.push_back(new Background(level2_b0Pal, level2_b0PalLen, level2_b0Tiles, level2_b0TilesLen, level2_b0Map, level2_b0MapLen, 0, 0, 0, 1, 0));
            m_backgrounds.push_back(new Background(level2_b1Pal, level2_b1PalLen, level2_b1Tiles, level2_b1TilesLen, level2_b1Map, level2_b1MapLen, 1, 0, 0, 1, 0));
            m_backgrounds.push_back(new Background(level2_b2Pal, level2_b2PalLen, level2_b2Tiles, level2_b2TilesLen, level2_b2Map, level2_b2MapLen, 2, 0, 0, 2, 0));

            m_backgrounds[0]->set_frames_to_skip(2);
            break;
        case LEVEL_3:
            // m_backgrounds.push_back(new Background(level3_b0Pal, level3_b0PalLen, level3_b0Tiles, level3_b0TilesLen, level3_b0Map, level3_b0MapLen, 0, 0, 0, 1, 0));
            // m_backgrounds.push_back(new Background(level3_b1Pal, level3_b1PalLen, level3_b1Tiles, level3_b1TilesLen, level3_b1Map, level3_b1MapLen, 1, 0, 0, 1, 0));
            // m_backgrounds.push_back(new Background(level3_b2Pal, level3_b2PalLen, level3_b2Tiles, level3_b2TilesLen, level3_b2Map, level3_b2MapLen, 2, 0, 0, 2, 0));

            // m_backgrounds[0]->set_frames_to_skip(2);
            break;
        case LEVEL_4:
            // m_backgrounds.push_back(new Background(level4_b0Pal, level4_b0PalLen, level4_b0Tiles, level4_b0TilesLen, level4_b0Map, level4_b0MapLen, 0, 0, 0, 1, 0));
            // m_backgrounds.push_back(new Background(level4_b1Pal, level4_b1PalLen, level4_b1Tiles, level4_b1TilesLen, level4_b1Map, level4_b1MapLen, 1, 0, 0, 1, 0));
            // m_backgrounds.push_back(new Background(level4_b2Pal, level4_b2PalLen, level4_b2Tiles, level4_b2TilesLen, level4_b2Map, level4_b2MapLen, 2, 0, 0, 2, 0));

            // m_backgrounds[0]->set_frames_to_skip(2);

            break;
        case LEVEL_5:
            // m_backgrounds.push_back(new Background(level5_b0Pal, level5_b0PalLen, level5_b0Tiles, level5_b0TilesLen, level5_b0Map, level5_b0MapLen, 0, 0, 0, 1, 0));
            // m_backgrounds.push_back(new Background(level5_b1Pal, level5_b1PalLen, level5_b1Tiles, level5_b1TilesLen, level5_b1Map, level5_b1MapLen, 1, 0, 0, 1, 0));
            // m_backgrounds.push_back(new Background(level5_b2Pal, level5_b2PalLen, level5_b2Tiles, level5_b2TilesLen, level5_b2Map, level5_b2MapLen, 2, 0, 0, 2, 0));

            // m_backgrounds[0]->set_frames_to_skip(2);

            break;
        case LEVEL_6:
            // m_backgrounds.push_back(new Background(level6_b0Pal, level6_b0PalLen, level6_b0Tiles, level6_b0TilesLen, level6_b0Map, level6_b0MapLen, 0, 0, 0, 1, 0));
            // m_backgrounds.push_back(new Background(level6_b1Pal, level6_b1PalLen, level6_b1Tiles, level6_b1TilesLen, level6_b1Map, level6_b1MapLen, 1, 0, 0, 1, 0));
            // m_backgrounds.push_back(new Background(level6_b2Pal, level6_b2PalLen, level6_b2Tiles, level6_b2TilesLen, level6_b2Map, level6_b2MapLen, 2, 0, 0, 2, 0));

            // m_backgrounds[0]->set_frames_to_skip(2);

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
        case LEVEL_MENU:
        case MENU_DEFEAT:
        case MENU_VICTORY:
            // do nothing
            break;
        case LEVEL_1:
            load_level_objects(level, level1_len, level1_platform_heights, level1_collectable_heights, level1_collectable_present);
            break;
        case LEVEL_2:
            load_level_objects(level, level2_len, level2_platform_heights, level2_collectable_heights, level2_collectable_present);
            break;
        case LEVEL_3:
            load_level_objects(level, level3_len, level3_platform_heights, level3_collectable_heights, level3_collectable_present);
            break;
        case LEVEL_4:
            load_level_objects(level, level4_len, level4_platform_heights, level4_collectable_heights, level4_collectable_present);
            break;
        case LEVEL_5:
            load_level_objects(level, level5_len, level5_platform_heights, level5_collectable_heights, level5_collectable_present);
            break;
        case LEVEL_6:
            load_level_objects(level, level6_len, level6_platform_heights, level6_collectable_heights, level6_collectable_present);
            break;
        default:
            break;
    }
}

void TWLevel::load_level_objects(int level, const int level_len, const int *platform_heights, const int *collectable_heights, const int *collectables_present)
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
            floor_plats[i] = new TWPlatform(level, i * platform_width, 142, true);
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
            platforms[i] = new TWPlatform(level, i * platform_width, platform_height[i]);
            collectables[i] = new TWCollectable(level, i * platform_width + platform_width / 2 - collectable_width / 2,
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