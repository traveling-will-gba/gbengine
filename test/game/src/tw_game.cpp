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

void TWGame::run() {
    previous_playable_level = -1;
    current_level = LEVEL_MENU;
    m_level = new TWLevel(current_level, false);

    uint64_t dt = 0;
    while (true) {
        print("antes vsync\n");
        vsync();

        print("antes btn\n");
        check_buttons_states();

        print("antes do col\n");
        Physics::get_physics()->do_collisions();

        m_level->update(dt);
        m_level->draw();

        if (m_level->done()) {
            print("1\n");
            if (m_level->next() == NEXT_LEVEL) {
                print("2\n");
                current_level = (previous_playable_level + 1) % (LOADED_LEVELS + 1);
            }
            else {
                print("3\n");
                previous_playable_level = current_level;
                current_level = m_level->next();
            }

            print("4\n");
            delete m_level;

            print("5\n");
            bool is_playable = current_level != LEVEL_MENU && current_level != MENU_VICTORY
                && current_level != MENU_DEFEAT;

            print("6\n");
            m_level = new TWLevel(current_level, is_playable);
            print("7\n");
        }

        dt++;
    }
}
