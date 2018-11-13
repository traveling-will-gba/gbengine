#include "memory_manager.h"

#include "utils.h"

MemoryManager *MemoryManager::get_memory_manager() {
    static MemoryManager *instance = new MemoryManager();

    return instance;
}

volatile uint8_t* MemoryManager::alloc_palette(bitset<512>& used, volatile uint8_t* palette, size_t size) {
    const int USED_SIZE = used.size();

    for (size_t i = 0; i < USED_SIZE; i++) {

        // if this position is taken, skip all used blocks for this address
        if (memory_map.find(palette + i) != memory_map.end()) {
            i += memory_map[palette + i];
            continue;
        }

        uint32_t available_pal_len = USED_SIZE - i;

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
    const uint32_t SIZE = memory_map[ptr];

    for (size_t i = 0; i < SIZE; i++) {
        used[ptr + i - palette] = false;
    }

    memory_map.erase(ptr);
}

void MemoryManager::free_background_pal(volatile uint8_t *background_pal_ptr)
{
    free_palette(background_pal_ptr, background_palette_used, background_palette);
}

void MemoryManager::free_texture_pal(volatile uint8_t *texture_pal_ptr)
{
    free_palette(texture_pal_ptr, texture_palette_used, texture_palette);
}

volatile struct attr *MemoryManager::alloc_oam_entry() {
    const uint32_t oam_entry_num = 128;
    const uint32_t oam_entry_size = 8 * 1024;

    for (size_t i = 0; i < oam_entry_num; i++) {
        if (memory_map.find(oam_mem + i) == memory_map.end()) {
            memory_map[oam_mem + i] = oam_entry_size;
            //print("oam: %p\n", oam_mem + i);
            return oam_mem + i;
        }
    }

    return NULL;
}

volatile struct tile *MemoryManager::alloc_texture(size_t size) {
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

void MemoryManager::free_oam_entry(volatile struct attr *oam_ptr) {
    memory_map.erase(oam_ptr);
}

void MemoryManager::free_texture(volatile struct tile *texture_ptr) {
    memory_map.erase((struct tile *)texture_ptr);
}
