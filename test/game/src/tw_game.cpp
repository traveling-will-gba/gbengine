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
    m_level = new TWLevel(1);

    uint64_t dt = 0;
    while (true) {
        vsync();

        check_buttons_states();

        Physics::get_physics()->do_collisions();

        m_level->update(dt);
        m_level->draw();

        dt++;
    }
}
