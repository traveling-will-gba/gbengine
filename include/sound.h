#ifndef SOUND_H
#define SOUND_H

#include <vector>
#include <string>

using namespace std;

const uint32_t __snd_rates[12]=
{
	8013, 7566, 7144, 6742, // C , C#, D , D#
	6362, 6005, 5666, 5346, // E , F , F#, G
	5048, 4766, 4499, 4246  // G#, A , A#, B
};

#define REG_SND1FREQ		*(vu16*)(REG_BASE+0x0064)
#define REG_SNDSTAT			*(vu16*)(REG_BASE+0x0084)
#define SSTAT_ENABLE		0x0080
#define REG_SNDDMGCNT		*(vu16*)(REG_BASE+0x0080)
#define REG_SNDDSCNT		*(vu16*)(REG_BASE+0x0082)
#define SDS_DMG100			0x0002
#define SDMG_SQR1			0x01
#define SDMG_BUILD_LR(_mode, _vol) SDMG_BUILD(_mode, _mode, _vol, _vol)
#define REG_SND1SWEEP		*(vu16*)(REG_BASE+0x0060)
#define SSW_OFF         	0x0008
#define REG_SND1CNT			*(vu16*)(REG_BASE+0x0062)
#define SSQR_ENV_BUILD(ivol, dir, time)             \
	(  ((ivol)<<12) | ((dir)<<11) | (((time)&7)<<8) )
#define SSQR_DUTY1_2		0x0080
#define SFREQ_RESET			0x8000
#define SND_RATE(note, oct) ( 2048-(__snd_rates[note]>>(4+(oct))) )
#define SDMG_BUILD(_lmode, _rmode, _lvol, _rvol)    \
	( ((_rmode)<<12) | ((_lmode)<<8) | (((_rvol)&7)<<4) | ((_lvol)&7) )


class Sound {
    private:
        Sound();

        int notes_len, tempos_len;
        const int *notes, *tempos;

        void play_note(int raw_note, int tempo);


    public:
        static Sound *get_sound();
        static Sound *instance;


        void play_music();
        void stop_music();


        void init();
        void load_from_file(int notes_len, const int* notes, int tempos_len, const int* tempos);
        void play();
};

#endif
