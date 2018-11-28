#include "input.h"
#include "video.h"
#include "texture.h"
#include "utils.h"

#include "menu_bg.h"
#include "will_idle.h"
#include "collectable.h"
#include "metr.h"
#include "platform_base.h"
#include "platform_middle.h"

#include "plat1.h"

#include "tw_will.h"
#include "tw_game.h"

#include <unistd.h>
#include <string.h>
#include <time.h>

#include <vector>

//FIXME Remove this include
#include "physics.h"

#define REG_BG2HOFS         *(vu16*)(REG_BASE+0x0018)
#define REG_BG2VOFS         *(vu16*)(REG_BASE+0x001A)

int main(){
    reset_dispcnt();

    Texture::init_sprite_attr_mem();

    TWGame game;
    game.run();

    return 0;
}
