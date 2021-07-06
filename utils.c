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
        if (i<l) bar[i+1] = '+';
        else bar[i+1] = ' ';
    }
}

void swr2str(uint16_t fw, uint16_t rv, char *ss)
{
    uint16_t swr = get_swr(fw,rv);

    uint16_t vfw = (fw*2*0x100)/0x3FF+300; // bridge volatge mV
    uint16_t vl = vfw*2; // vload*10
    uint32_t d = vl*vl;
    uint16_t pwr = d/50/10; // pwr = W*10
    pwr = pwr/2;

    uint8_t d1 = swr/100;
    uint8_t d2 = (swr/10)%10;
    uint8_t d3 = swr%10;

    ss[0] = 'S'; ss[1] = 'W'; ss[2] = 'R';
    ss[3] = dig2char(d1);
    ss[4] = '.';
    ss[5] = dig2char(d2);
    ss[6] = dig2char(d3);
    ss[7] = ' ';

    d1 = pwr/100;
    d2 = (pwr/10)%10;
    d3 = pwr%10;

    if (d1 != 0) ss[8] = dig2char(d1);
    else ss[8] = ' ';
    ss[9] = dig2char(d2);
    ss[10] = '.';
    ss[11] = dig2char(d3);
    ss[12] = 'W';
    ss[13] = 0x00;

}
