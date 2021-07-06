#ifndef EEPROM_H
#define EEPROM_H


void EEPROM_write_byte(uint16_t addr, uint8_t data);
uint8_t EEPROM_read_byte(uint16_t addr);

void EEPROM_write_block(uint16_t addr, uint8_t *data, uint8_t size);
void EEPROM_read_block(uint16_t addr, uint8_t *buf, uint8_t size);

#endif
