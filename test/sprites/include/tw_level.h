#ifndef TW_LEVEL_H
#define TW_LEVEL_H

#include "level.h"
#include "tw_platform.h"

#include <stdio.h>
#include <vector>

using std::vector;

class TWLevel : public Level {
    public:
        TWLevel();

        void update_self();
        void draw_self();
    private:
        uint32_t n_platforms;
        TWPlatform *platforms[100];
        int platform_height[110] = {147, 147, 147, 147, 147, 147, 147, 147, 147, 147,
                                    118, 118, 118, 118, 118, 130, 130, 130, 130, 130,
                                    118, 118, 118, 118, 118, 122, 122, 122, 122, 122,
                                    122, 130, 130, 130, 130, 118, 118, 118, 118, 118,
                                    118, 118, 118, 118, 118, 130, 130, 130, 130, 130,
                                    118, 118, 118, 118, 118, 130, 130, 130, 130, 130,
                                    118, 118, 118, 118, 118, 130, 130, 130, 130, 130,
                                    147, 147, 147, 147, 147, 147, 147, 147, 147, 147,
                                    0, 0, 0, 0, 0, 147, 147, 147, 147, 147,
                                    147, 147, 147, 147, 147, 147, 147, 147, 147, 147};

        int platform_idx;

        int mx1, my1;
        int mx2, my2;
};

#endif
