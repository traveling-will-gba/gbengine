#include <gba.h>

#include "sound.h"
#include <maxmod.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "utils.h"

Sound* Sound::instance;

Sound::Sound() {
    irqInit();

    irqSet( IRQ_VBLANK, mmVBlank );
    irqEnable(IRQ_VBLANK);

    mmInitDefault( (mm_addr)soundbank_bin, 8);
    mmStart( MOD_MUSIC43K, MM_PLAY_LOOP );
}

Sound *Sound::get_sound() {
    if (!instance) {
        instance = new Sound();
    }

    return instance;
}

void Sound::play() {
    mmFrame();
}

void Sound::stop() {
    mmStop();
}
