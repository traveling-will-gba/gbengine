#ifndef SOUND_H
#define SOUND_H

#include <vector>
#include <string>

using namespace std;

class Sound {
    private:
        Sound();

    public:
        static Sound *get_sound();
        static Sound *instance;

        void teste();
};

#endif
