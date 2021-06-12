#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

inline char dig2char(uint8_t d)
{
    return (0x30+d);
}

inline uint16_t get_swr(uint16_t fw, uint16_t rv)
{
    return ((fw+rv)*100)/(fw-rv);
}

void swr2str(uint16_t fw, uint16_t rv, char *ss);

void freq2str(uint32_t freq, char *s);
void adc2bar(uint16_t adc, char *bar, uint8_t size);

#endif

