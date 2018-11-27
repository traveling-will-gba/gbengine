#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "memory_manager.h"

#define OFFSET_DOUBLED_8BPP 2

enum bits_per_pixel {
    _4BPP = 0,
    _8BPP
};

class Texture {
    private:
        MemoryManager *memory_manager;

        const unsigned short *pallete;
        uint32_t pallete_len;

        const unsigned int *tiles;
        uint32_t tiles_len;

        uint32_t num_sprites;
        uint32_t num_tiles;
        uint32_t tiles_per_sprite;
        enum bits_per_pixel bpp;

        volatile struct attr *oam_entry;

        bool set_sprite_pal();
        bool set_sprite();
        void update_metadata();

    public:
        uint32_t id;
        uint16_t tile_base;
        struct attr metadata;
        uint32_t pallete_id;

        Texture() {}

        Texture(volatile struct attr *oam_entry, uint32_t num_sprites, const uint16_t *pallete, uint32_t pallete_len,
                const unsigned int *tiles, uint32_t tiles_len, enum bits_per_pixel bpp);
        Texture(const Texture *texture);
        Texture(uint32_t num_sprites, const uint16_t *pallete, uint32_t pallete_len,
            const unsigned int *tiles, uint32_t tiles_len, enum bits_per_pixel bpp);

        void update(uint64_t dt);
        void set_priority(int priority);

        static uint8_t *sprite_pal;
        static volatile void *obj_attr_mem;
        static void init_sprite_attr_mem();

        volatile struct attr *get_oam_entry();
};

#endif
