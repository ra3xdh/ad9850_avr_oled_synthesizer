#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

inline char dig2char(uint8_t d)
{
    return (0x30+d);
}

void freq2str(uint32_t freq, char *s);

#endif

