#ifndef LEVEL_H
#define LEVEL_H

#include "game_object.h"

#include <stdio.h>

class Level : public GameObject {
    protected:
        int m_x, m_y;
        bool m_done;
        int m_next;
};

#endif
