#include "video.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void reset_dispcnt() {
	REG_DISPCNT = 0;
}

void set_video_mode(int video_mode) {
	REG_DISPCNT |= video_mode;
}

void enable_background(int background) {
	switch (background) {
		case 0:
			REG_DISPCNT |= 0x0100;
		case 1:
			REG_DISPCNT |= 0x0200;
		case 2:
			REG_DISPCNT |= 0x0400;
		case 3:
			REG_DISPCNT |= 0x0800;
	}
}

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

inline uint32_t available_len(void *raw, void *offset) {
    return offset - raw;
}

bool cb[4];
struct charblock cb_mem[4];

// sprites

struct obj_attr_mem {
	void *raw;
	void *offset;
};

struct sprite {
	void *raw;
	void *offset;
};

struct attr {
    uint8_t y;
    uint8_t om : 2;
    uint8_t gm : 2;  
    uint8_t mos : 1;
    uint8_t cm : 1;
    uint8_t sh : 2;

    uint16_t x : 9;
    uint8_t aid : 5;
    uint8_t sz : 2;

    uint16_t tid : 10; 
    uint8_t pr : 2;
    uint8_t pb : 4;

    uint16_t filler;
};

bool sprite_av[512];
struct pallete sprite_pal_mem;
struct obj_attr_mem sprite_attr[128];
struct sprite sprite_mem[512];

int max_sprite_tiles = (16 * 1024 * 2) / 64; // 32 kb / 64 bytes (size of tile in 8bpp)

void init_sprite_mem()
{
    memset(sprite_av, 0, sizeof sprite_av);

    for(int i=0; i<max_sprite_tiles; i++) {
        sprite_mem[i].raw = sprite_mem[i].offset = (void *) 0x06010000 + i * 64;
    }

	for(int i=0;i<128;i++) {
		sprite_attr[i].raw = sprite_attr[i].offset = (void *) 0x07000000 + i * 8; // each obj attr entry is 8 bytes long
	}
}

void set_sprite(const void* pal, int pal_len, const void *tiles, int tiles_len)
{
	init_sprite_mem();

    sprite_pal_mem.raw = sprite_pal_mem.offset = (void *) 0x050000200;
	memcpy(sprite_pal_mem.offset, pal, pal_len);	
    sprite_pal_mem.offset += pal_len;

	memcpy(sprite_mem[0].offset, tiles, tiles_len);
	sprite_mem[0].offset += tiles_len;

	int tid = 0;

	struct attr *metr = &sprite_attr[0];
	metr->sh = 0; // square
	metr->sz = 3; // 11 -> size 64x64	
	metr->tid = tid;
	metr->pb = 0;
	metr->x = 1;
	metr->y = 40;

	REG_DISPCNT= DCNT_OBJ | DCNT_OBJ_1D;
}

// end sprites

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

            i += (cb_mem[i].offset - cb_mem[i].raw) / (16 * 1024);
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
        /* TODO: Log No more space for pallete */
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
