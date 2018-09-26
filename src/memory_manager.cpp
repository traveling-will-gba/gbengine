#include "memory_manager.h"

MemoryManager *MemoryManager::get_memory_manager() {
    static MemoryManager *instance = new MemoryManager();

    return instance;
}

uint8_t *MemoryManager::alloc_background_pal(size_t size) {
    for (size_t i = 0; i < background_pal_used.size(); i++) {
        if (background_pal_used[i]) continue;

        uint32_t available_pal_len = background_pal_used.size() - i;

        if (size <= available_pal_len) {
            for (size_t j = 0; j < size; j++) {
                background_pal_used[i + j] = true;
            }

            memory_map[background_pal + i] = size;

            return background_pal + i;
        }
    }

    return NULL;
}

uint8_t *MemoryManager::alloc_texture_pal(size_t size) {
    for (size_t i = 0; i < texture_pal_used.size(); i++) {
        if (memory_map.find(texture_pal + i) != memory_map.end()) continue;

        uint32_t available_pal_len = texture_pal_used.size() - i;

        if (size <= available_pal_len) {
            for (size_t j = 0; j < size; j++) {
                texture_pal_used[i + j] = true;
            }

            memory_map[texture_pal + i] = size;

            return texture_pal + i;
        }
    }

    return NULL;
}

struct attr *MemoryManager::alloc_oam_entry() {
    const uint32_t oam_entry_num = 128;
    const uint32_t oam_entry_size = 8 * 1024;

    for (size_t i = 0; i < oam_entry_num; i++) {
        if (memory_map.find(oam_mem + i) == memory_map.end()) {
            memory_map[oam_mem + i] = oam_entry_size;
            return oam_mem + i;
        }
    }

    return NULL;
}

void MemoryManager::free_background_pal(uint8_t *background_pal_ptr) {
    uint32_t size = memory_map[background_pal_ptr];
    for (size_t j = 0; j < size; j++) {
        background_pal_used[background_pal_ptr + j - background_pal] = false;
    }

    memory_map.erase(background_pal_ptr);
}

void MemoryManager::free_texture_pal(uint8_t *texture_pal_ptr) {
    uint32_t size = memory_map[texture_pal_ptr];
    for (size_t j = 0; j < size; j++) {
        texture_pal_used[texture_pal_ptr + j - texture_pal] = false;
    }

    memory_map.erase(texture_pal_ptr);
}

void MemoryManager::free_oam_entry(struct attr *oam_ptr) {
    memory_map.erase(oam_ptr);
}
