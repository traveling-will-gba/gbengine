#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "memory_manager.h"
#include "game_object.h"
#include "video.h"

#define OFFSET_DOUBLED_8BPP 2

#define BG_4BPP 0      //!< 4bpp (16 color) bg (no effect on affine bg)
#define BG_8BPP 0x0080 //!< 8bpp (256 color) bg (no effect on affine bg)
#define BG_REG_32x32 0
#define BG_REG_64x32 0x4000 //!< reg bg, 64x32 (512x256 px)

#define BG_CBB_MASK 0x000C
#define BG_CBB_SHIFT 2
#define BG_CBB(n) ((n) << BG_CBB_SHIFT)

#define BG_SBB_MASK 0x1F00
#define BG_SBB_SHIFT 8
#define BG_SBB(n) ((n) << BG_SBB_SHIFT)

// --- background ---
#define REG_BG0CNT *(vu16 *)(REG_BASE + 0x0008) // bg 0-3 control
#define REG_BG1CNT *(vu16 *)(REG_BASE + 0x000A)
#define REG_BG2CNT *(vu16 *)(REG_BASE + 0x000C)
#define REG_BG3CNT *(vu16 *)(REG_BASE + 0x000E)

// background scroll

#define REG_BG0HOFS *(vu16 *)(REG_BASE + 0x0010)
#define REG_BG0VOFS *(vu16 *)(REG_BASE + 0x0012)

#define REG_BG1HOFS *(vu16 *)(REG_BASE + 0x0014)
#define REG_BG1VOFS *(vu16 *)(REG_BASE + 0x0016)

#define REG_BG2HOFS *(vu16 *)(REG_BASE + 0x0018)
#define REG_BG2VOFS *(vu16 *)(REG_BASE + 0x001A)

#define REG_BG3HOFS *(vu16 *)(REG_BASE + 0x001C)
#define REG_BG3VOFS *(vu16 *)(REG_BASE + 0x001E)

// enum bits_per_pixel
// {
//     _4BPP = 0,
//     _8BPP
// };

class Background : public GameObject
{
    private:
      MemoryManager *memory_manager;

      const unsigned short *pallete;
      uint32_t pallete_len;

      const unsigned int *tiles;
      uint32_t tiles_len;

      const unsigned short *map;
      uint32_t map_len;

      volatile int background_id;

      // enum bits_per_pixel bpp;

      bool set_tiles();
      bool set_map();
      void set_background_register(int background);

    public:
        Background() {}

        Background(const unsigned short *pallete, uint32_t pallete_len,
            const unsigned int *tiles, uint32_t tiles_len,
            const unsigned short *map, uint32_t map_len, int background);

        Background(const unsigned short *pallete, uint32_t pallete_len,
            const unsigned int *tiles, uint32_t tiles_len,
            const unsigned short *map, uint32_t map_len,
            int background, int start_x, int start_y,
            int start_speed_x, int start_speed_y);

        void draw_self() {}
        void update_self(uint64_t dt);

        static void init_background_mem();

        bool set_palette(const unsigned short *pallete, uint32_t pallete_len);
        void set_speed(int x, int y);

        int tiles_cb_used;
        int map_se_used;
};

#endif
