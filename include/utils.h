#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdarg.h>

#define LEVEL_MENU 0
#define LEVEL_1 1
#define LEVEL_2 2
#define LEVEL_3 3
#define LEVEL_4 4
#define LEVEL_5 5
#define LEVEL_6 6
#define MENU_VICTORY 7
#define MENU_DEFEAT 8
#define NEXT_LEVEL 42
#define LOADED_LEVELS 6

int print(const char *fmt, ...);
void mem16cpy(volatile void *dest, const void *src, size_t n);
void vsync();

#endif
