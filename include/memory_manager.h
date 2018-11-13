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

class MemoryManager {
    private:
        // FIXME: Change this to volatile
        volatile uint8_t *background_pal;
        volatile uint8_t *texture_pal;
        volatile struct tile *texture_mem;

        volatile struct attr *oam_mem;

        unordered_map <volatile void *, uint32_t> memory_map;

        bitset<512> background_pal_used;
        bitset<512> texture_pal_used;

        MemoryManager() {
            background_pal = (volatile uint8_t *) 0x05000000;
            background_pal_used.reset();

            texture_pal = (volatile uint8_t *)0x05000200;
            texture_pal_used.reset();

            oam_mem = (volatile struct attr *)0x07000000;
            texture_mem = (volatile struct tile *)0x06010000;
        }

    public:
        static MemoryManager *get_memory_manager();
        
        volatile uint8_t *alloc_background_pal(size_t size);
        volatile uint8_t *alloc_texture_pal(size_t size);
        volatile struct attr *alloc_oam_entry();
        volatile struct tile *alloc_texture(size_t size);

        void free_background_pal(volatile uint8_t *background_pal_ptr);
        void free_texture_pal(volatile uint8_t *texture_pal_ptr);
        void free_oam_entry(volatile struct attr *oam_ptr);
        void free_texture(volatile struct tile *texture_ptr);

        volatile struct tile *base_texture_mem() {
            return texture_mem;
        }
};

#endif
