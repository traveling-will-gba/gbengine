#include "sprite.h"
#include "utils.h"

#include <string.h>
#include <stdlib.h>

// duplicate
struct pallete {
    void *raw;
    void *offset;
};

bool sprite_av[512];
struct pallete sprite_pal_mem;

struct attr sprite_attr_mem[128];

volatile void *obj_attr_mem = (void *)0x07000000;

uint8_t *sprite_pal = (uint8_t *)0x05000200;
bool sprite_pal_av[512];
uint32_t max_sprite_pal_entry = 512;

void init_sprite_attr_mem()
{
    //FIXME
    struct attr *sprite_attr = (struct attr *) malloc(sizeof(struct attr));
    sprite_attr->om = 2;
    for (int i = 0; i < 128; i++) {
        mem16cpy(((struct attr *)obj_attr_mem) + i, sprite_attr, sizeof(struct attr));
    }
}

void set_sprite_attrs(int sprite_idx, struct attr *custom_attrs)
{
    mem16cpy(((struct attr *)obj_attr_mem) + sprite_idx, custom_attrs, sizeof(struct attr));
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

volatile struct tile *sprite_mem = (volatile struct tile *)0x06010000;
int max_sprite_tiles = (16 * 1024 * 2) / 64; // 32 kb / 64 bytes (size of tile in 8bpp)

bool set_sprite(const void *tiles, int tiles_len, uint32_t *tile_used)
{
    for (int i = 0; i < max_sprite_tiles; i++) {
        if (sprite_av[i]) continue;

        uint32_t available_tile_bytes = (max_sprite_tiles - i) * 64;

        if (tiles_len > available_tile_bytes) {
            /* No more space */
            return false;
        }

        mem16cpy(sprite_mem + i, tiles, tiles_len);

        memset(sprite_av + i, true, (tiles_len / 64) + (tiles_len % 64 != 0));
        *tile_used = i;

        return true;
    }

    return false;
}
