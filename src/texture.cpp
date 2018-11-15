#include "texture.h"
#include "utils.h"

#include <string.h>
#include <stdlib.h>

// pass this to memory manager
uint8_t* Texture::sprite_pal;
volatile void* Texture::obj_attr_mem;

void Texture::init_sprite_attr_mem()
{
    obj_attr_mem = (void *)0x07000000;
    sprite_pal = (uint8_t *)0x05000200;

    //FIXME
    volatile struct attr *sprite_attr = (volatile struct attr *)malloc(sizeof(struct attr));
    sprite_attr->om = 2;
    for (int i = 0; i < 128; i++)
    {
        mem16cpy(((volatile struct attr *)obj_attr_mem) + i, (struct attr *)sprite_attr, sizeof(struct attr));
    }
}

Texture::Texture(uint32_t num_sprites, const uint16_t *pallete, uint32_t pallete_len,
        const unsigned int *tiles, uint32_t tiles_len, enum bits_per_pixel bpp = _8BPP)
{
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
    metadata.pb = pallete_id;
}

Texture::Texture(const Texture *texture)
{
    this->num_sprites = texture->num_sprites;
    this->pallete = texture->pallete;
    this->pallete_len = texture->pallete_len;
    this->tiles = texture->tiles;
    this->tiles_len = texture->tiles_len;
    this->bpp = texture->bpp;
    this->pallete_id = texture->pallete_id;
    this->num_tiles = texture->num_tiles;
    this->tiles_per_sprite = texture->tiles_per_sprite;
    this->tile_base = texture->tile_base;

    memory_manager = MemoryManager::get_memory_manager();

    oam_entry = memory_manager->alloc_oam_entry();

    metadata.tid = tile_base * ((bpp == _4BPP) ? 1 : 2);
    metadata.pb = pallete_id;
}

bool Texture::set_sprite_pal() {
    volatile uint8_t *teste = memory_manager->alloc_texture_palette(32);
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
