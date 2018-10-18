#ifndef SOUND_H
#define SOUND_H

#include <vector>
#include <string>

using namespace std;

class Sound {
    private:
        vector<int> notes, tempos;

        void play_note(int raw_note, int tempo);

    public:
        Sound();

        void init();
        void load_from_file(string sound_path);
        void play();
};

#endif
