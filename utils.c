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

void adc2bar(uint16_t adc, char *bar, uint8_t size)
{
    uint8_t l = (adc*size)/0xFF;

    bar[0] = 'S';
    for (uint8_t i = 0; i < size; i++)
    {
        if (i<l) bar[i+1] = 0xFF;
        else bar[i+1] = ' ';
    }
}

void swr2str(uint16_t fw, uint16_t rv, char *ss)
{
    uint16_t swr = get_swr(fw,rv);

    uint8_t d1 = swr/100;
    uint8_t d2 = (swr/10)%10;
    uint8_t d3 = swr%10;

    ss[0] = 'S'; ss[1] = 'W'; ss[2] = 'R'; ss[3] = ' ';
    ss[4] = dig2char(d1);
    ss[5] = '.';
    ss[6] = dig2char(d2);
    ss[7] = dig2char(d3);
    ss[8] = 0x00;
}
