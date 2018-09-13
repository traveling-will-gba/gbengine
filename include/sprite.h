#ifndef SPRITE_H
#define SPRITE_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"

#define OFFSET_DOUBLED_8BPP 2

struct tile {
    uint8_t pixel[64];
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

extern uint8_t *sprite_pal;
extern volatile void *obj_attr_mem;
extern struct tile *sprite_mem;


void init_sprite_attr_mem();
void set_sprite_attrs(int sprite_idx, struct attr *custom_attrs);
bool set_sprite_pal(const void *pal, int pal_len);
bool set_sprite(const void *tiles, int tiles_len, uint32_t *tile_used);
void set_sprite_attr(uint32_t sprite_idx);

class Texture {
    private:
        const unsigned short *pallete;
        uint32_t pallete_len;

        const unsigned int *tiles;
        uint32_t tiles_len;

        bool set_sprite_pal() {
            // TODO: Use MemoryManager 
            const uint32_t max_sprite_pal_entry = 512;

            // TODO: Use MemoryManager 
            bool sprite_pal_av[512];
            memset(sprite_pal_av, 0, 512);

            for (int i = 0; i < max_sprite_pal_entry; i++) {
                if (sprite_pal_av[i]) continue;

                uint32_t available_pal_len = max_sprite_pal_entry - i;

                if (pallete_len > available_pal_len) {
                    /* No more space */
                    return false;
                }

                memcpy(sprite_pal + i, pallete, pallete_len);
                memset(sprite_pal_av + i, true, pallete_len);

                return true;
            }

            return false;
        } 

        bool set_sprite() {
            bool sprite_av[512];
            int max_sprite_tiles = (16 * 1024 * 2) / 64; // 32 kb / 64 bytes (size of tile in 8bpp)
            for (int i = 0; i < max_sprite_tiles; i++) {
                if (sprite_av[i]) continue;

                uint32_t available_tile_bytes = (max_sprite_tiles - i) * 64;

                if (tiles_len > available_tile_bytes) {
                    /* No more space */
                    return false;
                }

                mem16cpy(sprite_mem + i, tiles, tiles_len);

                memset(sprite_av + i, true, (tiles_len / 64) + (tiles_len % 64 != 0));
                tile_base = i;

                return true;
            }

            return false;
        }

    public:
        uint32_t id;
        uint32_t tile_base;
        struct attr metadata;
        uint32_t pallete_id;

        Texture(const unsigned short *pallete, uint32_t pallete_len, const unsigned int *tiles, uint32_t tiles_len) {
            this->pallete = pallete;
            this->pallete_len = pallete_len;
            this->pallete_id = 0;

            this->tiles = tiles;
            this->tiles_len = tiles_len;

            // TODO: Use MemoryManager 
            this->id = 0;

            set_sprite_pal();
            set_sprite();

            metadata.tid = tile_base * OFFSET_DOUBLED_8BPP;
        }
};

#endif
