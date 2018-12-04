#include "input.h"
#include "video.h"
#include "utils.h"
#include "sound.h"

#include "fase5.h"

int main(){
    reset_dispcnt();
    set_video_mode(0);
    enable_background(2);

    Sound *s = Sound::get_sound();

    s->load_from_file(fase5_notes_len, fase5_notes, fase5_tempos_len, fase5_tempos);
    s->play();

    return 0;
}
