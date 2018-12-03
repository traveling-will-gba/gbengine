#include "background.h"

#include "sound.h"

Background::Background(const unsigned short *pallete, uint32_t pallete_len,
                       const unsigned int *tiles, uint32_t tiles_len,
                       const unsigned short *map, uint32_t map_len,
                       int background)
{
    m_bg_frame_speed = {0};
    m_frame_div = m_bg_frame_speed.size();

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

    m_speed_x = m_speed_y = 0;
    m_x = m_y = 0;

    m_frames_to_skip = 1;

    set_background_register(this->background_id);
}

Background::Background(const unsigned short *pallete, uint32_t pallete_len,
                       const unsigned int *tiles, uint32_t tiles_len,
                       const unsigned short *map, uint32_t map_len,
                       int background, vector <int> frame_speed)
{
    m_bg_frame_speed = frame_speed;
    m_frame_div = frame_speed.size();

    this->pallete = pallete;
    // FIXME pallete_len should not be hardcoded
    this->pallete_len = 32;
    this->tiles = tiles;
    this->tiles_len = tiles_len;
    this->map = map;
    this->map_len = map_len;
    this->background_id = background;
    
    memory_manager = MemoryManager::get_memory_manager();

    m_speed_x = m_speed_y = 0;
    m_x = m_y = 0;

    set_palette(this->pallete, this->pallete_len);
    set_tiles();
    set_map();

    m_frames_to_skip = 1;

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

const vector <int> Background::frame_speed() const {
    return this->m_bg_frame_speed;
}

const uint32_t Background::frame_div() const {
    return m_frame_div;
}

void Background::update_self(uint64_t dt) {
    m_speed_x = this->m_bg_frame_speed[dt % m_frame_div];

    m_x += m_speed_x;
    m_y += m_speed_y;

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
            print("Invalid background id %d\n");
            break;
    }
}

const int Background::x() const {
    return m_x;
}

const int Background::y() const{
    return m_y;
}

const int Background::frames_to_skip() const {
    return m_frames_to_skip;
}

const int Background::speed_x() const {
    return m_speed_x;
}

const int Background::speed_y() const {
    return m_speed_y;
}
