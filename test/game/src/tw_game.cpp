#include <stdlib.h>

#include "tw_game.h"

#include "physics.h"
#include "sound.h"

#include "input.h"
#include "utils.h"

void TWGame::run() {
    previous_playable_level = -1;
    current_level = LEVEL_1;

    bool is_playable = current_level != LEVEL_MENU && current_level != MENU_VICTORY
        && current_level != MENU_DEFEAT;

    m_level = new TWLevel(current_level, is_playable);

    uint64_t dt = 0;
    while (true) {
        vsync();

        // if (current_level == LEVEL_1) {
        Sound::get_sound()->play_music();
        // }

        check_buttons_states();

        Physics::get_physics()->do_collisions();

        if (REG_VCOUNT < 160) print("WHAT!?\n");

        m_level->update(dt);
        m_level->draw();

        if (m_level->done()) {
            if (m_level->next() == NEXT_LEVEL) {
                current_level = (previous_playable_level + 1) % (LOADED_LEVELS + 1);
                if (current_level == 0)
                    current_level++;
            }
            else {
                previous_playable_level = current_level;
                current_level = m_level->next();
            }

            delete m_level;

            Physics::get_physics()->clear_list();

            is_playable = current_level != LEVEL_MENU && current_level != MENU_VICTORY
                && current_level != MENU_DEFEAT;

            m_level = new TWLevel(current_level, is_playable);
        }

        dt++;
    }
}
