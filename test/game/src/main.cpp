#include "input.h"
#include "video.h"
#include "texture.h"
#include "utils.h"

#include "menu_bg.h"
#include "will_idle.h"
#include "metr.h"

#include "tw_will.h"
#include "tw_game.h"

#include <unistd.h>
#include <string.h>
#include <time.h>

int main(){
    reset_dispcnt();

    Texture::init_sprite_attr_mem();

    TWGame game;

    game.run();

    return 0;
}
