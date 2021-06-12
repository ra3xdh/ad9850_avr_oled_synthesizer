#include <avr/io.h>
#include <avr/interrupt.h>

#include "adc.h"

void init_adc(void)
{
    ADCSRA |= (1<<ADEN);
    ADCSRA |= (1<<ADPS1)|(1<<ADPS2);
    ADMUX |= (1<<REFS1)|(1<<REFS0);

    //DDRA |= 0x07;
}

uint16_t read_adc(uint8_t channel)
{
    ADMUX &= 0xC0;
    ADMUX |= (channel & 0x07);
    ADCSRA |= (1<<ADSC);
    while ((ADCSRA & (1<<ADSC)));
    return (uint16_t) ADC;
}


