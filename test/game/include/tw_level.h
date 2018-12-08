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
        TWLevel(int level, bool playable);
        ~TWLevel();

        void update_self(uint64_t dt);
        void draw_self();
        void set_platform_num(int num) { platform_num = num; }
        void load_level(int level);
        void load_backgrounds(int level);
        void load_level_design(int level);
        void load_level_objects(int level, const int level_len, const short *platform_heights,
            const short *collectable_heights, const bool *collectables_present);

        const bool done() const { return m_done; }
        const int next() const { return m_next; }
        void dispose();

        vector <int> &get_level_music();
    private:
        vector <int> level_songs;
        void load_level_music(int level);

        uint32_t n_platforms;
        TWPlatform *platforms[20];
        TWCollectable *collectables[20];
        TWPlatform *floor_plats[20];
        TWWill *will;

        queue <TWPlatform *> q;
        short platform_height[2000];
        short collectable_height[2000];
        bool collectable_present[2000];

        vector<Background *> m_backgrounds;

        void delete_platforms();
        void delete_backgrounds();

        int platform_idx;
        int platform_num;
        int m_current_level;
        int collectables_num;

        int mx1, my1;
        int mx2, my2;

        bool m_is_level_ending;
        bool m_playable;
};

#endif
