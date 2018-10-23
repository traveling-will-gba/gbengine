#include "input.h"
#include "video.h"
#include "sprite.h"
#include "utils.h"
#include "sound.h"

#include "fase1.h"

int main(){
    reset_dispcnt();
    set_video_mode(0);
    enable_background(2);

    Sound *s = new Sound();

    s->load_from_file(fase1_notes_len, fase1_notes, fase1_tempos_len, fase1_tempos);
    s->play();

    return 0;
}
