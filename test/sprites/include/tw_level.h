#ifndef TW_LEVEL_H
#define TW_LEVEL_H

#include "level.h"

#include <stdio.h>

class TWLevel : public Level {
    public:
        TWLevel();

        void update_self();
        void draw_self();
};

#endif
