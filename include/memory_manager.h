#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <bitset>
#include <map>

using namespace std;

class MemoryManager {
    private:
        uint8_t *background_pal;
        uint8_t *texture_pal;

        map <uint8_t *, uint32_t> memory_map;

        bitset<512> background_pal_used;
        bitset<512> texture_pal_used;

        MemoryManager() {
            background_pal = (uint8_t *) 0x05000000;
            background_pal_used.reset();

            texture_pal = (uint8_t *)0x05000200;
            texture_pal_used.reset();
        }

    public:
        static MemoryManager *get_memory_manager();
        
        uint8_t *alloc_background_pal(size_t size);
        uint8_t *alloc_texture_pal(size_t size);

        void free_background_pal(uint8_t *background_pal_ptr);
        void free_texture_pal(uint8_t *texture_pal_ptr);
};

#endif
