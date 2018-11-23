#include "utils.h"
#include "vbaprint.h"

// remove this
#include "video.h"

void mem16cpy(volatile void *dest, const void *src, size_t n)
{
    if (n & 1) {
        print("Size must be even");
    }

    for (int i = 0; i < n / 2; i++) {
        *(((volatile uint16_t *)dest) + i) = *(((uint16_t *)src) + i);
    }

//    print("%d\n", (uint16_t *)dest);
}

int print(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    char buffer[4096];

    int rc = vsnprintf(buffer, sizeof(buffer), fmt, args);

    vbaprint(buffer);

    va_end(args);

    return rc;
}

// FIXME REG_VCOUNT imported from video.h

void vsync() {
    while(REG_VCOUNT >= 160);
    while(REG_VCOUNT < 160);
}
