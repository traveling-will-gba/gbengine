#include "input.h"
#include "video.h"
#include "texture.h"
#include "utils.h"

#include "menu_bg.h"
#include "will_idle.h"
#include "collectable.h"
#include "metr.h"

#include "tw_will.h"
#include "tw_game.h"

#include <unistd.h>
#include <string.h>
#include <time.h>

#define LEVEL_MENU 0
#define LEVEL_1 1
#define LEVEL_2 2
#define LEVEL_3 3
#define LEVEL_4 4
#define LEVEL_5 5
#define LEVEL_6 6

int main(){
    reset_dispcnt();

    Texture::init_sprite_attr_mem();

    TWGame game;
    game.run(LEVEL_MENU);

    return 0;
}
