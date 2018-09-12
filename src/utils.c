#include "utils.h"
#include "vbaprint.h"

void mem16cpy(void *dest, const void *src, size_t n)
{
    if (n & 1) {
       vbaprint("Size must be even"); 
    }

    for (int i = 0; i < n / 2; i++) {
        *(((uint16_t *)dest) + i) = *(((uint16_t *)src) + i);
    }
}

void print(char *label, uint64_t n) {
    char buffer[500];
    sprintf(buffer, "%s: %llu\n", label, n);
    vbaprint(buffer);
}
