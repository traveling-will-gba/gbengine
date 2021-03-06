#ifndef VIDEO_H
#define VIDEO_H

#include <stdbool.h>
#include <stdio.h>
#include "base_types.h"

void vsync();
void reset_dispcnt();
void set_video_mode(int video_mode);
void enable_background(int background);

// --- secondary typedefs ---

typedef u16 COLOR;
typedef u16 SCR_ENTRY;
typedef struct { uint32_t data[8]; } TILE;

typedef SCR_ENTRY	SCREENBLOCK[1024];
typedef TILE		CHARBLOCK[512];

#define MEM_IO		0x04000000
#define MEM_PAL		0x05000000		// no 8bit write !!
#define MEM_VRAM	0x06000000		// no 8bit write !!

#define PAL_SIZE	0x00400
#define VRAM_SIZE	0x18000

// --- sizes ---
#define SCREEN_WIDTH	240
#define SCREEN_HEIGHT	160

// --- registers ------------------------------------------------------

#define REG_BASE	MEM_IO

#define REG_DISPCNT			*(vu32*)(REG_BASE+0x0000)	// display control
#define REG_DISPSTAT		*(vu16*)(REG_BASE+0x0004)	// display interupt status
#define REG_VCOUNT			*(vu16*)(REG_BASE+0x0006)	// vertical count

// --- REG_DISPCNT ---

#define DCNT_MODE0				 0	//!< Mode 0; bg 0-4: reg
#define DCNT_MODE1			0x0001	//!< Mode 1; bg 0-1: reg; bg 2: affine
#define DCNT_MODE2			0x0002	//!< Mode 2; bg 2-2: affine
#define DCNT_MODE3			0x0003	//!< Mode 3; bg2: 240x160\@16 bitmap
#define DCNT_MODE4			0x0004	//!< Mode 4; bg2: 240x160\@8 bitmap
#define DCNT_MODE5			0x0005	//!< Mode 5; bg2: 160x128\@16 bitmap
#define DCNT_BG0			0x0100	//!< Enable bg 0
#define DCNT_BG1			0x0200	//!< Enable bg 1
#define DCNT_BG2			0x0400	//!< Enable bg 2
#define DCNT_BG3			0x0800	//!< Enable bg 3

#define DCNT_OBJ_1D			0x0040	//!< OBJ-VRAM as array
#define DCNT_OBJ			0x1000	//!< Enable objects

#endif
