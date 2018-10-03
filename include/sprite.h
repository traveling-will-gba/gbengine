#ifndef SPRITE_H
#define SPRITE_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "memory_manager.h"

#define OFFSET_DOUBLED_8BPP 2

extern uint8_t *sprite_pal;
extern volatile void *obj_attr_mem;
extern volatile struct tile *sprite_mem;


void init_sprite_attr_mem();
void set_sprite_attrs(int sprite_idx, struct attr *custom_attrs);
bool set_sprite_pal(const void *pal, int pal_len);
bool set_sprite(const void *tiles, int tiles_len, uint32_t *tile_used);
void set_sprite_attr(uint32_t sprite_idx);

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

        bool set_sprite_pal() {
            volatile uint8_t *teste = memory_manager->alloc_texture_pal(pallete_len);
            mem16cpy(teste, pallete, pallete_len);

            return true;
        }

        bool set_sprite() {
            volatile struct tile *teste = memory_manager->alloc_texture(tiles_len);

            mem16cpy((volatile struct tile *)teste, tiles, tiles_len);
            tile_base = teste - memory_manager->base_texture_mem();
            return true;
        }

        void update_metadata() {
            mem16cpy(oam_entry, &metadata, sizeof(struct attr));
        }

    public:
        uint32_t id;
        uint32_t tile_base;
        struct attr metadata;
        uint32_t pallete_id;

        Texture() {}

        Texture(uint32_t num_sprites, const unsigned short *pallete, uint32_t pallete_len,
                const unsigned int *tiles, uint32_t tiles_len, enum bits_per_pixel bpp = _8BPP) {
            this->pallete = pallete;
            this->pallete_len = pallete_len;
            this->pallete_id = 0;
            this->bpp = bpp;
            this->num_sprites = num_sprites;
            this->num_tiles = tiles_len / ((bpp == _4BPP) ? 32 : 64);
            this->tiles_per_sprite = num_tiles / num_sprites;
            this->tiles = tiles;
            this->tiles_len = tiles_len;

            memory_manager = MemoryManager::get_memory_manager();

            set_sprite_pal();
            set_sprite();
            oam_entry = memory_manager->alloc_oam_entry();

            metadata.tid = tile_base * ((bpp == _4BPP) ? 1 : 2);
        }

        void update()
        {
            uint32_t offset = (bpp == _4BPP) ? 1 : 2;
            metadata.tid = (metadata.tid + tiles_per_sprite * offset) % (num_tiles * offset);
            update_metadata();
        }
};

#endif
