#include "memory_manager.h"

#include "utils.h"

MemoryManager* MemoryManager::instance;

MemoryManager *MemoryManager::get_memory_manager() {
    if (!instance) {
        instance = new MemoryManager();
    }

    return instance;
}

volatile uint8_t* MemoryManager::alloc_palette(bitset<512>& used, volatile uint8_t* palette, size_t size) {
    int used_size = used.size();

    for (size_t i = 0; i < used_size; i++) {

        // if this position is taken, skip all used blocks for this address
        if (memory_map.find(palette + i) != memory_map.end()) {
            i += memory_map[palette + i];
            continue;
        }

        uint32_t available_pal_len = used_size - i;

        // if there is no space to allocate this pallete, skip it
        if (size > available_pal_len) {
            continue;
        }

        for (size_t j = 0; j < size; j++) {
            used[i + j] = true;
        }

        memory_map[palette + i] = size;

        return palette + i;
    }

    return NULL;
}

volatile uint8_t* MemoryManager::alloc_background_palette(size_t size)
{
    return alloc_palette(background_palette_used, background_palette, size);
}

volatile uint8_t* MemoryManager::alloc_texture_palette(size_t size) {
    return alloc_palette(texture_palette_used, texture_palette, size);
}

void MemoryManager::free_palette(volatile uint8_t *ptr, bitset<512>& used, volatile uint8_t *palette)
{
    uint32_t size = memory_map[ptr];

    for (size_t i = 0; i < size; i++) {
        used[ptr + i - palette] = false;
    }

    memory_map.erase(ptr);
}

void MemoryManager::free_background_palette(volatile uint8_t *background_pal_ptr)
{
    free_palette(background_pal_ptr, background_palette_used, background_palette);
}

void MemoryManager::free_texture_palette(volatile uint8_t *texture_pal_ptr)
{
    free_palette(texture_pal_ptr, texture_palette_used, texture_palette);
}

volatile struct tile* MemoryManager::alloc_texture(size_t size) {
    const uint32_t total_texture_bytes = (16 * 1024 * 2);

    for (size_t i = 0; i < total_texture_bytes;) {
        uint32_t tile_offset = i / sizeof(struct tile);
        volatile struct tile *address = (struct tile *)texture_mem + tile_offset;

        if (memory_map.find(address) == memory_map.end()) {
            uint32_t available_tile_bytes = (total_texture_bytes - i);

            if (size > available_tile_bytes) {
                return NULL;
            }

            memory_map[address] = size;

            return address;
        }

        i += memory_map[address];
    }

    return NULL;
}

volatile void *MemoryManager::alloc_background_tiles(size_t tile_size, int *cb_used) {
    const int charblock_size = 16 * 1024; // one charblock has 16Kb
    const int screenblock_size = 2 * 1024; // one charblock has 16Kb
    const int charblock_num = 4; // there are 4 charblocks for backgrounds in VRAM
    const int screenblock_num = 32;
    const int screenblocks_per_charblock = 16 / 2;

    for(int i=0; i < charblock_num; i++) {
        if (charblock_used[i]) {
            continue;
        }

        int free_charblocks = charblock_num - i; // number of free charblocks including current one

        // there is not enough space to alloc these tiles
        if (tile_size > free_charblocks * charblock_size) {
            return NULL;
        }

        int charblocks_used = (tile_size / charblock_size) + (tile_size % charblock_size ? 1 : 0);
        int cur_charblock = i;

        while(charblocks_used--) {
            charblock_used[cur_charblock++] = true;
        }

        int screenblock_entries_used = (tile_size / screenblock_size) + (tile_size  % charblock_size ? 1 : 0);
        int cur_screenblock = i * screenblocks_per_charblock;

        while (screenblock_entries_used--) {
            screenblock_used[cur_screenblock++] = true;
        }

        // FIXME fix this
        *cb_used = 29;

        return charblock_mem[i].offset;
    }

    return NULL;
}

volatile void *MemoryManager::alloc_background_map(size_t map_size) {
    const int screenblock_size = 2 * 1024; // one screenblock has 2Kb
    const int screenblock_num = 32; // there are 32 screenblocks in background VRAM
    const int charblock_num = 4;
    const int screenblocks_per_charblock = 16 / 2;

    const int screenblocks_used = (map_size / screenblock_size) + (map_size % screenblock_size ? 1 : 0);

    for (int i=0; i<screenblock_num; i++) {
        // print("i = %d\n", i);
        if (screenblock_used[i] == false) {
            int cur_screenblock = i;
            bool enough_space = true;
            int used = screenblocks_used;

            while(used--) {
                // print("used = %d\n", used);
                if (screenblock_used[cur_screenblock++] == false) {
                    enough_space = false;
                    break;
                }
            }

            if (enough_space) {
                int used = screenblocks_used;
                int cur_screenblock = i;

                while (used--)
                {
                    int cur_charblock = (used / screenblocks_per_charblock + 1);
                    charblock_used[cur_charblock] = true;
                    screenblock_used[cur_screenblock++] = true;
                }

                int start_charblock = (i / 8 + 1);
                int relative_screenblock = i - (start_charblock - 1) * screenblocks_per_charblock;

                print("char used: %d screen used: %d\n", start_charblock, relative_screenblock);

                return screenblock_mem[start_charblock][relative_screenblock].offset;
            }
        }
    }

    return NULL;
}

void MemoryManager::free_texture(volatile struct tile *texture_ptr)
{
    memory_map.erase((struct tile *)texture_ptr);
}

volatile struct attr *MemoryManager::alloc_oam_entry()
{
    const uint32_t oam_entry_num = 128;
    const uint32_t oam_entry_size = 8 * 1024;

    for (size_t i = 0; i < oam_entry_num; i++)
    {
        if (memory_map.find(oam_mem + i) == memory_map.end())
        {
            memory_map[oam_mem + i] = oam_entry_size;
            return oam_mem + i;
        }
    }

    return NULL;
}

void MemoryManager::free_oam_entry(volatile struct attr *oam_ptr) {
    memory_map.erase(oam_ptr);
}
