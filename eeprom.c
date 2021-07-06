#include <avr/io.h>

#include "eeprom.h"


void EEPROM_write_byte(uint16_t addr, uint8_t data)
{
    while (EECR & (1<<EEPE));
    EEAR = addr;
    EEDR = data;
    EECR |= (1 << EEMPE);
    EECR |= (1 << EEPE);
}

uint8_t EEPROM_read_byte(uint16_t addr)
{
    while (EECR & (1<<EEPE));
    EEAR = addr;
    EECR |= (1 << EERE);
    return EEDR;
}

void EEPROM_write_block(uint16_t addr, uint8_t *data, uint8_t size)
{
    for (uint8_t i = 0; i < size; i++) {
        EEPROM_write_byte(addr+i, data[i]);
    }
}

void EEPROM_read_block(uint16_t addr, uint8_t *buf, uint8_t size)
{
    for (uint8_t i = 0; i < size; i++ ) {
        buf[i] = EEPROM_read_byte(addr+i);
    }
}
