#include "tw_level.h"
#include "video.h"
#include "background_1.h"
#include "tw_will.h"
#include "physics.h"

#define REG_BG2HOFS *(vu16*)(REG_BASE+0x0018)
#define REG_BG2VOFS *(vu16*)(REG_BASE+0x001A)

TWLevel::TWLevel() {
    reset_dispcnt();
    set_video_mode(0);
    enable_background(2);

    set_background(background_1Pal, background_1PalLen, background_1Tiles, background_1TilesLen, background_1Map, background_1MapLen);

    volatile uint32_t *reg_dispcnt = (volatile uint32_t *)REG_BASE+0x0000;
    *reg_dispcnt |= DCNT_OBJ | DCNT_OBJ_1D;

    m_x = m_y = 0;
    m_done = false;

    init_sprite_attr_mem();
    
    TWWill *will = new TWWill(0, 144);

    add_child(will);
    Physics::get_physics()->set_target(will);
}

void TWLevel::update_self() {
    for (int i = 0; i < 8; i++) {
        REG_BG2HOFS = m_x;
        m_x++;
        vsync();
    }
}

void TWLevel::draw_self() {

}
