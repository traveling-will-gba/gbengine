#include "tw_game.h"

#include "physics.h"

//FIXME: ERASE THIS, PLEASE
#include "platform.h"
#include "texture.h"

#include "tw_platform.h"

#include <stdlib.h>

#include "time.h"

#include "video.h"
#include "input.h"
#include "utils.h"

#define LEVEL_MENU 0
#define LEVEL_1 1
#define LEVEL_2 2
#define LEVEL_3 3
#define LEVEL_4 4
#define LEVEL_5 5
#define LEVEL_6 6
#define MENU_VICTORY 7
#define MENU_DEFEAT 8

void TWGame::run() {
    current_level = LEVEL_MENU;
    m_level = new TWLevel(current_level, false);

    uint64_t dt = 0;
    while (true) {
        vsync();

        check_buttons_states();

        Physics::get_physics()->do_collisions();

        m_level->update(dt);
        m_level->draw();

        if (m_level->done()) {
            current_level = m_level->next();

            m_level->dispose();

            bool is_playable = current_level != LEVEL_MENU && current_level != MENU_VICTORY
                && current_level != MENU_DEFEAT;

            m_level = new TWLevel(current_level, is_playable);
        }

        dt++;
    }
}
