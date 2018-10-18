#include "input.h"
#include "video.h"
#include "sprite.h"
#include "utils.h"
#include "sound.h"

int main(){
    reset_dispcnt();
    set_video_mode(0);
    enable_background(2);

    Sound *s = new Sound();

    s->load_from_file("teste");
    s->play();

    return 0;
}
