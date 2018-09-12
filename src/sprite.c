#include "sprite.h"

#include <vbaprint.h>
#include <string.h>
#include <stdlib.h>

// duplicate
struct pallete {
    void *raw;
    void *offset;
};

void print3(char *label, int n) {
    char buffer[500];
    sprintf(buffer, "%s: %d\n", label, n);
    vbaprint(buffer);
}

bool sprite_av[512];
struct pallete sprite_pal_mem;

struct attr sprite_attr_mem[128];

volatile void *obj_attr_mem = (void *)0x07000000;

uint8_t *sprite_pal = (void *)0x05000200;
bool sprite_pal_av[512];
uint32_t max_sprite_pal_entry = 512;

void mem16cpy(void *dest, const void *src, size_t n)
{
    if (n & 1) {
       vbaprint("Size must be even"); 
    }

    for (int i = 0; i < n / 2; i++) {
        *(((uint16_t *)dest) + i) = *(((uint16_t *)src) + i);
    }
}

void init_sprite_attr_mem()
{
    //FIXME
    struct attr *sprite_attr = malloc(sizeof(struct attr));
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

struct tile {
    uint8_t pixel[64];
};

struct tile *sprite_mem = (void *)0x06010000;
int max_sprite_tiles = (16 * 1024 * 2) / 64; // 32 kb / 64 bytes (size of tile in 8bpp)

bool set_sprite(const void *tiles, int tiles_len, int *tile_used)
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
