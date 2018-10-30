#include "game.h"

#include "tw_level.h"
#include "physics.h"

void Game::run() {
    //FIXME: THE ENGINE SHOULD NOT CALL THE GAME
    TWLevel level;

    while (true) {
        level.update();
        level.draw();

        Physics::get_physics()->do_collisions();
    }
}
