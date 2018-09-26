#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <bitset>
#include <map>

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

class MemoryManager {
    private:
        // FIXME: Change this to volatile
        uint8_t *background_pal;
        uint8_t *texture_pal;
        struct attr *oam_mem;

        map <void *, uint32_t> memory_map;

        bitset<512> background_pal_used;
        bitset<512> texture_pal_used;

        MemoryManager() {
            background_pal = (uint8_t *) 0x05000000;
            background_pal_used.reset();

            texture_pal = (uint8_t *)0x05000200;
            texture_pal_used.reset();

            oam_mem = (struct attr *)0x07000000;
        }

    public:
        static MemoryManager *get_memory_manager();
        
        uint8_t *alloc_background_pal(size_t size);
        uint8_t *alloc_texture_pal(size_t size);
        struct attr *alloc_oam_entry();

        void free_background_pal(uint8_t *background_pal_ptr);
        void free_texture_pal(uint8_t *texture_pal_ptr);
        void free_oam_entry(struct attr *oam_ptr);
};

#endif
