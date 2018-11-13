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
    vector <TWPlatform *> platforms;
    
    srand(10);

    /*for (int i = 0; i < 30; i++) {
        int aux = 12;

        TWPlatform *platform;

        if (i)
            platform = new TWPlatform(i * 8, 159 - aux, platforms[0]->texture());
        else
            platform = new TWPlatform(i * 8, 159 - aux);

        platforms.push_back(platform);
    }*/
    
    TWLevel level;

    /*
    for (int i = 0; i < 10; i++) {
        int aux = rand() % 32;

        //print("rand: %d\n", aux);

        for (int j = 0; j < 2; j++) {
            TWPlatform *platform;

            platform = new TWPlatform((i * 4 + j) * 8, 150 - aux, platforms[0]->texture());

            platforms.push_back(platform);
        }
    }
    */

    while (true) {
        vsync();

        check_buttons_states();

        Physics::get_physics()->do_collisions();

        level.update();
        level.draw();

        for (auto it : platforms) {
            it->update();
        }
   }
}
