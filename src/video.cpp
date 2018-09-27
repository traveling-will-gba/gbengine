#include "video.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

volatile uint32_t *reg_dispcnt = (volatile uint32_t *)REG_BASE+0x0000;

void reset_dispcnt() {
	*reg_dispcnt = 0;
}

void set_video_mode(int video_mode) {
	*reg_dispcnt |= video_mode;
}

void enable_background(int background) {
	switch (background) {
		case 0:
			*reg_dispcnt |= 0x0100;
		case 1:
			*reg_dispcnt |= 0x0200;
		case 2:
			*reg_dispcnt |= 0x0400;
		case 3:
			*reg_dispcnt |= 0x0800;
	}
}

// duplicate of sprite
struct pallete {
    void *raw;
    void *offset;
};

struct charblock {
    void *raw;
    void *offset;
};

struct screenblock {
    void *raw;
    void *offset;
};

uint32_t available_len(void *raw, void *offset) {
    return (uint8_t *)offset - (uint8_t *)raw;
}

bool cb[4];
struct charblock cb_mem[4];

// number of charblocks
const uint8_t cb_num = 4;
// number of screenblocks
const uint8_t se_num = 32;

bool set_charblock(const void *tiles, uint32_t tiles_len, uint32_t *cb_used) {
    uint32_t cb_size = 16*1024;

    for (int i = 0; i < cb_num; i++) {
        if (cb[i]) continue;

        uint32_t available_cb_len = (cb_num - i) * cb_size; 
        
        if (tiles_len > available_cb_len) {
            /* No more space */
            return false;
        }

        memcpy(cb_mem[i].offset, tiles, tiles_len);
        cb_mem[i].offset += tiles_len;

        memset(cb + i, 1, tiles_len / (16 * 1024) + (tiles_len % (16 * 1024)) ? 1 : 0);

        *cb_used = i;

        return true;
    }

    return false;
}

/* ccss ---- ---- -sss */

struct screenblock se_mem[4][8];
bool se[4][8];

bool set_screenblock(const void *map, uint32_t map_len, uint32_t *sb_used) {
    for (int i = 0; i < cb_num;) {
        if (cb[i]) {
            if (cb_mem[i].offset < cb_mem[i + 1].raw) {
                for (int j = 0; j < 8; j++) {
                    if (se_mem[i][j].raw > cb_mem[i].offset && !se[i][j]) {
                        memcpy(se_mem[i][j].offset, map, map_len);
                        se_mem[i][j].offset += map_len;
                        se[i][j] = true;
                        *sb_used = i * 8 + j;
                        return true;
                    }
                }
            }

            i += ((uint8_t *)cb_mem[i].offset - (uint8_t *)cb_mem[i].raw) / (16 * 1024);
            continue;
        }
        break;
    }

    for (int i = se_num - 1; i >= 0; i--) {
        uint32_t cur_cb = i / 8;
        if (!se[cur_cb][i % 8]) {
            memcpy(se_mem[cur_cb][i % 8].offset, map, map_len);
            se_mem[cur_cb][i % 8].offset += map_len;
            se[cur_cb][i % 8] = true;
            *sb_used = i;
            return true;
        }
    }

    return false;
}

struct pallete pal_bg_mem;

void set_background(const void *pal, int pal_len, const void *tiles, int tiles_len, const void *map, int map_len) {
    pal_bg_mem.raw = pal_bg_mem.offset = (void *) 0x05000000;

    uint32_t available_pal_len = available_len(pal_bg_mem.raw, pal_bg_mem.offset);
    if (pal_len > available_pal_len) {
        print("%d\n", available_pal_len);
        print("No more space for pallete\n");
    }
    memcpy(pal_bg_mem.offset, pal, pal_len);
    pal_bg_mem.offset += pal_len;

    uint32_t cb_used = 0, sb_used = 0;

    for (int i = 0; i < 4; i++) {
        cb_mem[i].raw = cb_mem[i].offset = (void *)0x06000000 + i * 16 * 1024;
    }

     for (int i = 0; i < 32; i++) {
        se_mem[i / 8][i % 8].raw = se_mem[i / 8][i % 8].offset = (void *)0x06000000 + i * 2 * 1024; 
    }

    set_charblock(tiles, tiles_len, &cb_used);
    set_screenblock(map, map_len, &sb_used);

	REG_BG2CNT = BG_CBB(cb_used) | BG_SBB(sb_used) | BG_8BPP | BG_REG_64x32;
}
