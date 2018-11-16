#include "game.h"

#include "tw_level.h"
#include "physics.h"

//FIXME: ERASE THIS, PLEASE
#include "platform.h"
#include "texture.h"

#include "tw_platform.h"

#include <stdlib.h>

#include "time.h"

#include "video.h"
#include "input.h"

void Game::run() {
    //FIXME: THE ENGINE SHOULD NOT CALL THE GAME
    
    TWLevel level;

    uint64_t dt = 0;
    while (true) {
        vsync();

        check_buttons_states();

        Physics::get_physics()->do_collisions();

        level.update(dt);
        level.draw();

        dt++;
    }
}
