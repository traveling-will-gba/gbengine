#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdarg.h>

int print(const char *fmt, ...);
void mem16cpy(void *dest, const void *src, size_t n);

#endif
