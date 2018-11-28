#include "background.h"

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
                        int background, int start_x = 0, int start_y = 0,
                        int start_speed_x = 0, int start_speed_y = 0)
{
    this->pallete = pallete;
    // FIXME pallete_len should not be hardcoded
    this->pallete_len = 32;
    this->tiles = tiles;
    this->tiles_len = tiles_len;
    this->map = map;
    this->map_len = map_len;
    this->background_id = background;

    memory_manager = MemoryManager::get_memory_manager();

    set_palette(this->pallete, this->pallete_len);
    set_tiles();
    set_map();

    m_x = start_x;
    m_y = start_y;
    m_speed_x = start_speed_x;
    m_speed_y = start_speed_y;

    set_background_register(this->background_id);
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
        break;
    }
}

bool Background::set_palette(const unsigned short *pallete, uint32_t pallete_len)
{
    volatile uint8_t *address = memory_manager->alloc_background_palette(pallete_len);

    if (!address)
    {
        return false;
    }

    mem16cpy(address, pallete, 32);

    return true;
}

bool Background::set_tiles()
{
    volatile void *address = memory_manager->alloc_background_tiles(tiles_len, &tiles_cb_used);

    if (!address)
    {
        return false;
    }

    mem16cpy((void *)address, tiles, tiles_len);

    return true;
}

bool Background::set_map()
{
    volatile void *address = memory_manager->alloc_background_map(map_len, &map_se_used);


    if (!address)
    {
        return false;
    }

    mem16cpy((void *)address, map, map_len);

    return true;
}

void Background::set_speed(int x, int y) {
    this->m_speed_x = x;
    this->m_speed_y = y;
}

void Background::update_self(uint64_t dt) {
    //print("oi oi oi %d %d %d\n", this->background_id, m_x, m_y);

    if (dt % frames_to_skip == 0) {
        m_x += m_speed_x;
        m_y += m_speed_y;
    }

    switch(this->background_id) {
        case 0:
            REG_BG0HOFS = m_x;
            REG_BG0VOFS = m_y;
            break;
        case 1:
            REG_BG1HOFS = m_x;
            REG_BG1VOFS = m_y;
            break;
        case 2:
            REG_BG2HOFS = m_x;
            REG_BG2VOFS = m_y;
            break;
        case 3:
            REG_BG3HOFS = m_x;
            REG_BG3VOFS = m_y;
            break;
        default:
            print("Invalid background id\n");
            break;
    }
}

const int Background::x() const {
    return m_x;
}

const int Background::y() const{
    return m_y;
}

const int Background::speed_x() const {
    return m_speed_x;
}

const int Background::speed_y() const {
    return m_speed_y;
}
