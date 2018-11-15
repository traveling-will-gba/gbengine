#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <bitset>
#include <map>
#include <unordered_map>

using namespace std;

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

struct tile {
    uint8_t pixel[32];
};

struct palette
{
    void *raw;
    void *offset;
};

struct charblock
{
    void *raw;
    void *offset;
};

struct screenblock
{
    void *raw;
    void *offset;
};

class MemoryManager {
    private:
        // palette members
        volatile uint8_t* background_palette;
        volatile uint8_t* texture_palette;

        bitset<512> background_palette_used;
        bitset<512> texture_palette_used;

        volatile struct tile *texture_mem;
        volatile struct attr *oam_mem;

        // bool cb[4];
        volatile struct charblock charblock_mem[4];
        volatile struct screenblock screenblock_mem[4][8];
        // static struct palette palette_bg_mem;

        bitset<4> charblock_used;
        bitset<32> screenblock_used;

        unordered_map <volatile void *, uint32_t> memory_map;

        MemoryManager() {
            // rename to texture_palette_mem
            texture_palette = (volatile uint8_t *)0x05000200;
            texture_palette_used.reset();

            oam_mem = (volatile struct attr *)0x07000000;
            texture_mem = (volatile struct tile *)0x06010000;

            // rename to background_palette_mem
            background_palette = (volatile uint8_t *)0x05000000;
            background_palette_used.reset();

            // palette_bg_mem.raw = palette_bg_mem.offset = (void *)0x05000000;

            for (int i = 0; i < 4; i++)
            {
                charblock_mem[i].raw = charblock_mem[i].offset =
                    (void *)0x06000000 + i * 16 * 1024;
            }

            for (int i = 0; i < 32; i++)
            {
                screenblock_mem[i / 8][i % 8].raw = screenblock_mem[i / 8][i % 8].offset =
                    (void *)0x06000000 + i * 2 * 1024;
            }

            charblock_used.reset();
            screenblock_used.reset();
        }

        volatile uint8_t *alloc_palette(bitset<512> &used, volatile uint8_t *palette, size_t size);
        void free_palette(volatile uint8_t *ptr, bitset<512> &used, volatile uint8_t *palette);

      public:
        static MemoryManager *get_memory_manager();
        static MemoryManager *instance;

        // palette allocation
        volatile uint8_t *alloc_background_palette(size_t size);
        volatile uint8_t *alloc_texture_palette(size_t size);

        void free_background_palette(volatile uint8_t *background_pal_ptr);
        void free_texture_palette(volatile uint8_t *texture_pal_ptr);


        volatile struct attr *alloc_oam_entry();
        void free_oam_entry(volatile struct attr *oam_ptr);

        volatile struct tile *alloc_texture(size_t size);
        void free_texture(volatile struct tile *texture_ptr);

        volatile void *alloc_background_tiles(size_t tile_size, int *cb_used);
        volatile void *alloc_background_map(size_t map_size);

        volatile struct tile *base_texture_mem() {
            return texture_mem;
        }
};

#endif
