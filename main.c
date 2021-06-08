#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "ad9850.h"

#define LED_PIN PORTB4

int main(void)
{
    _delay_ms(500);

    dds_setup();
    dds_reset();
    dds_update_freq(15e6);


    DDRB |= (1<<DDB4);
    for(;;) {
        PORTB |= (1 << LED_PIN);
        _delay_ms(1000);
        PORTB &= ~(1 << LED_PIN);
        _delay_ms(1000);
    }
}
