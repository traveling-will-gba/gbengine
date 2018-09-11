#ifndef SPRITE_H
#define SPRITE_H

#include <stdbool.h>
#include <stdio.h>

uint8_t *sprite_pal;
volatile void *obj_attr_mem;

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

void set_sprite_attrs(int sprite_idx, struct attr *custom_attrs);
bool set_sprite_pal(const void *pal, int pal_len);
bool set_sprite(const void *tiles, int tiles_len, int *tile_used);
void set_sprite_attr(uint32_t sprite_idx);

#endif
