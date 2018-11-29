#ifndef TW_LEVEL_H
#define TW_LEVEL_H

#include "level.h"
#include "tw_platform.h"
#include "background.h"
#include "tw_will.h"

#include <stdio.h>
#include <vector>
#include <queue>

using std::vector;

class TWLevel : public Level {
    public:
        TWLevel(int level);

        void update_self(uint64_t dt);
        void draw_self();
        void set_platform_num(int num) { platform_num = num; }
        void load_level(int level);
        void load_backgrounds(int level);
        void load_level_design(int level);
        void load_level_objects(const int level_len, const int *platform_heights,
            const int *collectable_heights, const int *collectables_present);

    private:
        uint32_t n_platforms;
        TWPlatform *platforms[50];
        TWWill *will;

        queue <TWPlatform *> q;
        int platform_height[500];
        int collectable_height[500];
        bool collectable_present[500];

        vector<Background *> m_backgrounds;

        int platform_idx;
        int platform_num;

        int mx1, my1;
        int mx2, my2;

        bool m_is_level_ending;
};

#endif
