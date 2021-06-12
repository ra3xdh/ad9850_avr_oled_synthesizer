#include "utils.h"

void freq2str(uint32_t freq, char *s)
{
    uint32_t f = freq;
    uint32_t k = 10000000UL;
    uint8_t d[8];

    for (int i = 0; i < 8; i++) {
        d[i] = f/k;
        f = f - d[i]*k;
        k = k/10;
    }

    if(d[0] == 0) s[0] = ' ';
    else s[0] = dig2char(d[0]);
    s[1] = dig2char(d[1]);
    s[2] = '.';

    for (int i = 2; i < 7; i++) {
        s[i+1]=dig2char(d[i]);
    }

    //s[8] = ' '; s[9] = 'M'; s[10] = 'H'; s[11] = 'z';
}
