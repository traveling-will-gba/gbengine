#ifndef TW_LEVEL_H
#define TW_LEVEL_H

#include "level.h"
#include "tw_platform.h"
#include "background.h"

#include <stdio.h>
#include <vector>
#include <queue>

using std::vector;

class TWLevel : public Level {
    public:
        TWLevel();

        void update_self(uint64_t dt);
        void draw_self();
        void set_platform_num(int num) { platform_num = num; }

    private:
        uint32_t n_platforms;
        TWPlatform *platforms[100];

        queue <TWPlatform *> q;
        int platform_height[10100];

        vector<Background *> m_backgrounds;

        int platform_idx;
        int platform_num;

        int mx1, my1;
        int mx2, my2;
};

#endif
