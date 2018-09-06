#include "video.h"

#include "aux.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void print2(char *label, int n) {
    char buffer[500];
    sprintf(buffer, "%s: %d\n", label, n);
    vbaprint(buffer);
}

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

/*
struct sprite {
	void *raw;
	void *offset;
};
*/

bool sprite_av[512];
struct pallete sprite_pal_mem;
//struct obj_attr_mem sprite_attr[128];

struct tile {
    uint8_t pixel[64];
};

struct tile *sprite_mem = (void *)0x06010000;
//struct attr *sprite_attr_mem = (void *)0x07000000;
void *oam_mem = (void *)0x07000000;
struct attr sprite_attr_mem[128];

int max_sprite_tiles = (16 * 1024 * 2) / 64; // 32 kb / 64 bytes (size of tile in 8bpp)

void init_sprite_mem()
{
    memset(sprite_av, 0, sizeof sprite_av);
}

uint8_t *sprite_pal = (void *)0x05000200;
bool sprite_pal_av[512];
uint32_t max_sprite_pal_entry = 512;

void mem16cpy(void * dest, const void * src, size_t n)
{
    if (n & 1) {
       vbaprint("Size must be even"); 
    }

    for(int i=0;i<8;i++) {
        print2("antes", *(((char *)src) + i));
    }

    for (int i = 0; i < n / 2; i++) {
        *(((uint16_t *)dest) + i) = *(((uint16_t *)src) + i);
    }

    for(int i=0;i<8;i++) {
        print2("depois", *(((char *)dest) + i));
    }
}

void set_sprite_attrs(int sprite_idx, struct attr *custom_attrs)
{
    mem16cpy(((struct attr *)oam_mem) + sprite_idx, custom_attrs, 8);
}

bool set_sprite_pal(const void *pal, int pal_len)
{
    for (int i = 0; i < max_sprite_pal_entry; i++) {
        if (sprite_pal_av[i]) continue;

        uint32_t available_pal_len = max_sprite_pal_entry - i;

        if (pal_len > available_pal_len) {
            /* No more space */
            return false;
        }

        memcpy(sprite_pal + i, pal, pal_len);
        memset(sprite_pal_av + i, true, pal_len);

        return true;
    }

    return false;
}

bool set_sprite(const void *tiles, int tiles_len, int *tile_used)
{
	//init_sprite_mem();

    for (int i = 0; i < max_sprite_tiles; i++) {
        if (sprite_av[i]) continue;

        uint32_t available_tile_bytes = (max_sprite_tiles - i) * 64;

        if (tiles_len > available_tile_bytes) {
            /* No more space */
            return false;
        }
            
        memcpy(sprite_mem + i, tiles, tiles_len);
        memset(sprite_av + i, true, (tiles_len / 64) + (tiles_len % 64 != 0));
        *tile_used = i;

        return true;
    }

    return false;
}

void oam_copy(struct attr *dst, const struct attr *src, int count) {
    while(count--)
        *dst++ = *src++;
}

void set_sprite_attr(uint32_t sprite_idx) {
    int tid = sprite_idx * 64;

//	struct attr *sprite_attr = sprite_attr_mem;
//    memset(sprite_attr, 0, sizeof(struct attr));
    sprite_attr_mem[0].om = 0;
	sprite_attr_mem[0].sh = 0; // square
	sprite_attr_mem[0].sz = 3; // 11 -> size 64x64	
	sprite_attr_mem[0].tid = tid;
	sprite_attr_mem[0].pb = 0;
	sprite_attr_mem[0].x = 30;
	sprite_attr_mem[0].y = 40;
/*
    sprite_attr_mem[1].om = 0;
	sprite_attr_mem[1].sh = 0; // square
	sprite_attr_mem[1].sz = 3; // 11 -> size 64x64	
	sprite_attr_mem[1].tid = 1 * 64;
	sprite_attr_mem[1].pb = 0;
	sprite_attr_mem[1].x = 100;
	sprite_attr_mem[1].y = 40;
*/
    mem16cpy(oam_mem, sprite_attr_mem, 128 * 8);

    //oam_copy(oam_mem, sprite_attr_mem, 128);

    vbaprint("oam:\n");
    for (int i = 0; i < 8; i++){
        char abcd2[500];
        sprintf(abcd2, "%d\n", *(((char *)oam_mem) + i));
        vbaprint(abcd2);
    }
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

/*    char abcd[512], abcd2[512];

    sprintf(abcd, "%p\n", &sprite_attr_mem[0]);
    sprintf(abcd2, "%p\n", &sprite_attr_mem[1]);

    vbaprint(abcd);
    vbaprint(abcd2);
  */  
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
