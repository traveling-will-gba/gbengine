#include <gba.h>

#include "sound.h"
#include <maxmod.h>
#include "soundbank.h"
#include "soundbank_bin.h"

#include "utils.h"

Sound* Sound::instance;

Sound::Sound() {
	init();

    irqInit();

    irqSet( IRQ_VBLANK, mmVBlank );
    irqEnable(IRQ_VBLANK);

    mmInitDefault( (mm_addr)soundbank_bin, 8);
}

Sound *Sound::get_sound() {
    if (!instance) {
        instance = new Sound();
    }

    return instance;
}

void Sound::play_music() {
    mmFrame();
}

void Sound::load_music(int level) {
    switch (level) {
        case LEVEL_1:
            mmStart(MOD_LEVEL1, MM_PLAY_ONCE);
            break;
        case LEVEL_2:
            mmStart(MOD_LEVEL2, MM_PLAY_ONCE);
            break;
        case LEVEL_3:
            mmStart(MOD_LEVEL3, MM_PLAY_ONCE);
            break;
        case LEVEL_4:
            mmStart(MOD_LEVEL1, MM_PLAY_ONCE);
            break;
        case LEVEL_5:
            mmStart(MOD_LEVEL1, MM_PLAY_ONCE);
            break;
        case LEVEL_6:
            mmStart(MOD_LEVEL1, MM_PLAY_ONCE);
            break;
        case MENU_VICTORY:
            mmStart(MOD_VICTORY, MM_PLAY_LOOP);
            break;
        case MENU_DEFEAT:
            mmStart(MOD_LOSING, MM_PLAY_LOOP);
            break;
        default:;
            /* Unknown Level */
            stop_music();
            //print("Unknown level");
    }
}

void Sound::stop_music() {
    mmStop();
    mmPosition(1);
}

void Sound::init() {
	// turn sound on
	REG_SNDSTAT= SSTAT_ENABLE;
	// snd1 on left/right ; both full volume
	REG_SNDDMGCNT = SDMG_BUILD_LR(SDMG_SQR1, 7);
	// DMG ratio to 100%
	REG_SNDDSCNT= SDS_DMG100;

	// no sweep
	REG_SND1SWEEP= SSW_OFF;
	// envelope: vol=12, decay, max step time (7) ; 50% duty
	REG_SND1CNT= SSQR_ENV_BUILD(12, 0, 7) | SSQR_DUTY1_2;
	REG_SND1FREQ= 0;
}

void Sound::load_from_file(int notes_len, const int* notes, int tempos_len, const int* tempos)
{
    this->notes = notes;
    this->notes_len = notes_len;
    this->tempos = tempos;
    this->tempos_len = tempos_len;

}

void Sound::play_note(int raw_note, int tempo) {
	int note = raw_note % 12;
	int octave = raw_note / 12;

	REG_SND1FREQ = SFREQ_RESET | SND_RATE(note, octave);

	for(int i=0; i<8*tempo; i++) {
		vsync();
	}
}

void Sound::play() {
	for(int i=0; i < notes_len; i++) {
		// print("note %d tempo %d\n", notes[i], tempos[i]);
		play_note(notes[i], tempos[i]);
	}
}
