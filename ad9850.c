#include <avr/io.h>
#include <avr/interrupt.h>

#include "ad9850.h"

#define DDS_PORT PORTB
#define DDS_DDR DDRB
#define DDS_CLOCK PORTB0
#define DDS_RESET PORTB3
#define DDS_LOAD PORTB1 // Also called FQ_UD (Frequency Update)
#define DDS_DATA PORTB2
#define DDS_CLOCK_DDR DDB0
#define DDS_RESET_DDR DDB3
#define DDS_LOAD_DDR DDB1 // Also called FQ_UD (Frequency Update)
#define DDS_DATA_DDR DDB2

static const float DDS_REF = 125e6;

void dds_setup(void)
{
    DDS_DDR |= (1 << DDS_CLOCK_DDR);
    DDS_DDR |= (1 << DDS_RESET_DDR);
    DDS_DDR |= (1 << DDS_DATA_DDR);
    DDS_DDR |= (1 << DDS_LOAD_DDR);
}

void dds_reset(void)
{
    // Set everything low first
    DDS_PORT &= ~(1 << DDS_CLOCK);
    DDS_PORT &= ~(1 << DDS_LOAD);
    DDS_PORT &= ~(1 << DDS_DATA);
    DDS_PORT &= ~(1 << DDS_RESET);

    // Pulse reset
    DDS_PORT |=  (1 << DDS_RESET);
    DDS_PORT &= ~(1 << DDS_RESET);

    // Pulse clock
    DDS_PORT |=  (1 << DDS_CLOCK);
    DDS_PORT &= ~(1 << DDS_CLOCK);

    // Pulse load
    DDS_PORT |=  (1 << DDS_LOAD);
    DDS_PORT &= ~(1 << DDS_LOAD);
}

void dds_write(uint8_t byte)
{
    uint8_t i;
    uint8_t bit;
    for(i = 0; i < 8; i++) {
        bit = ((byte >> i) & 1);
        if(bit == 1)
            DDS_PORT |=  (1 << DDS_DATA);
        else
            DDS_PORT &= ~(1 << DDS_DATA);

        DDS_PORT |=  (1 << DDS_CLOCK);
        DDS_PORT &= ~(1 << DDS_CLOCK);
    }
}

void dds_update_freq(float freq)
{
    // Updates DDS output frequency. Supply frequency in Hz.

    cli();
    uint32_t tuning_word = (freq * 4294967295UL) / DDS_REF;
    dds_write(tuning_word & 0xFF);
    dds_write((tuning_word >> 8) & 0xFF);
    dds_write((tuning_word >> 16) & 0xFF);
    dds_write((tuning_word >> 24) & 0xFF);
    dds_write(0);

    DDS_PORT |=  (1 << DDS_LOAD);
    DDS_PORT &= ~(1 << DDS_LOAD);
    sei();
}
