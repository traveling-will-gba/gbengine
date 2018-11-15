#include "background.h"

// void Background::init_background_mem() {
//     palette_bg_mem.raw = palette_bg_mem.offset = (void *)0x05000000;

//     for (int i = 0; i < 4; i++)
//     {
//         charblock_mem[i].raw = charblock_mem[i].offset =
//             (void *)0x06000000 + i * 16 * 1024;
//     }

//     for (int i = 0; i < 32; i++)
//     {
//         screenblock_mem[i / 8][i % 8].raw = screenblock_mem[i / 8][i % 8].offset =
//             (void *)0x06000000 + i * 2 * 1024;
//     }
// }

Background::Background(const unsigned short *pallete, uint32_t pallete_len,
                       const unsigned int *tiles, uint32_t tiles_len,
                       const unsigned short *map, uint32_t map_len,
                       int background)
{
    Background(pallete, pallete_len, tiles, tiles_len, map, map_len, background, 0, 0, 0, 0);
}

Background::Background(const unsigned short *pallete, uint32_t pallete_len,
                        const unsigned int *tiles, uint32_t tiles_len,
                        const unsigned short *map, uint32_t map_len,
                        int background, int start_x, int start_y,
                        int start_speed_x, int start_speed_y)
{
    this->pallete = pallete;
    this->pallete_len = pallete_len;
    this->tiles = tiles;
    this->tiles_len = tiles_len;
    this->map = map;
    this->map_len = map_len;

    memory_manager = MemoryManager::get_memory_manager();

    print("test background constructor\n");

    set_palette();
    set_tiles();
    set_map();

    m_x = start_x;
    m_y = start_y;
    m_speed_x = start_speed_x;
    m_speed_y = start_speed_y;

    set_background_register(background);
}

void Background::set_background_register(int background) {
    switch(background) {
        case 0:
            REG_BG0CNT = BG_CBB(tiles_cb_used) | BG_SBB(map_se_used) | BG_4BPP | BG_REG_32x32;
            break;
        case 1:
            REG_BG1CNT = BG_CBB(tiles_cb_used) | BG_SBB(map_se_used) | BG_4BPP | BG_REG_32x32;
            break;
        case 2:
            REG_BG2CNT = BG_CBB(tiles_cb_used) | BG_SBB(map_se_used) | BG_4BPP | BG_REG_32x32;
            break;
        case 3:
            REG_BG3CNT = BG_CBB(tiles_cb_used) | BG_SBB(map_se_used) | BG_4BPP | BG_REG_32x32;
            break;
        default:
            print("Invalid option");
            break;
    }
}

bool Background::set_palette()
{
    volatile uint8_t *address = memory_manager->alloc_background_palette(pallete_len);

    print("\npalette background address: %p\n", address);

    if (!address)
    {
        return false;
    }

    // why 32?
    mem16cpy(address, pallete, 32);

    return true;
}

bool Background::set_tiles()
{
    volatile void *address = memory_manager->alloc_background_tiles(tiles_len, &tiles_cb_used);

    print("\ntiles background address: %p\n", address);

    if (!address)
    {
        return false;
    }

    memcpy((void *)address, tiles, tiles_len);

    return true;
}

bool Background::set_map()
{
    print("\n wtf\n");
    volatile void *address = memory_manager->alloc_background_map(map_len);

    print("\nmap background address: %p\n", address);

    if (!address)
    {
        return false;
    }

    memcpy((void *)address, map, map_len);

    return true;
}

void Background::update_self()
{
}