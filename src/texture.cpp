#include "texture.h"
#include "utils.h"

#include <string.h>
#include <stdlib.h>

volatile void *obj_attr_mem = (void *)0x07000000;
uint8_t *sprite_pal = (uint8_t *)0x05000200;

void init_sprite_attr_mem()
{
    //FIXME
    volatile struct attr *sprite_attr = (volatile struct attr *) malloc(sizeof(struct attr));
    sprite_attr->om = 2;
    for (int i = 0; i < 128; i++) {
        mem16cpy(((volatile struct attr *)obj_attr_mem) + i, (struct attr *)sprite_attr, sizeof(struct attr));
    }
}

bool Texture::set_sprite_pal() {
    volatile uint8_t *teste = memory_manager->alloc_texture_pal(32);
    mem16cpy(teste, pallete, 32);

    this->pallete_id = (teste - (volatile uint8_t *)0x05000200) / 32;

    //print("pal: %d\n", this->pallete_id);

    return true;
}

bool Texture::set_sprite() {
    volatile struct tile *teste = memory_manager->alloc_texture(tiles_len);

    mem16cpy((volatile struct tile *)teste, tiles, tiles_len);
    tile_base = teste - memory_manager->base_texture_mem();

    //print("tile: %d\n", tile_base);

    return true;
}

void Texture::update_metadata() {
    mem16cpy(oam_entry, &metadata, sizeof(struct attr));
}

void Texture::update() {
    uint32_t offset = (bpp == _4BPP) ? 1 : 2;
    update_metadata();
    metadata.tid = (metadata.tid + tiles_per_sprite * offset) % (num_tiles * offset + tile_base);
    metadata.tid = max(metadata.tid, tile_base);
}

void Texture::set_priority(int priority) {
    metadata.pr = priority;
}
