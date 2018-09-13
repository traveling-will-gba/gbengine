#include "utils.h"
#include "vbaprint.h"

void mem16cpy(void *dest, const void *src, size_t n)
{
    if (n & 1) {
        print("Size must be even");
    }

    for (int i = 0; i < n / 2; i++) {
        *(((uint16_t *)dest) + i) = *(((uint16_t *)src) + i);
    }
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

