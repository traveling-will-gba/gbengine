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

void TWGame::run(int level) {
    current_level = level;
    m_level = new TWLevel(current_level, false);

    uint64_t dt = 0;
    while (true) {
        vsync();

        check_buttons_states();

        Physics::get_physics()->do_collisions();

        m_level->update(dt);
        m_level->draw();

        if (m_level->done()) {
            m_level->dispose();

            current_level++;
            bool is_playable = current_level > 0;
            m_level = new TWLevel(current_level, is_playable);
        }

        dt++;
    }
}
