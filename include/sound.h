#ifndef SOUND_H
#define SOUND_H

#include <vector>
#include <string>

using namespace std;

class Sound {
    private:
        int notes_len, tempos_len;
        const int *notes, *tempos;

        void play_note(int raw_note, int tempo);

    public:
        Sound();

        void init();
        void load_from_file(int notes_len, const int* notes, int tempos_len, const int* tempos);
        void play();
};

#endif
