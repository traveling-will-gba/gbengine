#ifndef GAME_H
#define GAME_H

#include "tw_level.h"

class TWGame {
    private:
        TWLevel *m_level;

    public:
        void run();
};

#endif
