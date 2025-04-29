#ifndef _EEPROM_H_
#define _EEPROM_H_

#include <avr/io.h>
#include <util/delay.h>
#include "twi.h"

#define EE_ADDR_W 0xa6
#define EE_ADDR_R 0xa7
void EE_write_byte(uint16_t addr, uint8_t data);
uint8_t EE_read_byte(uint16_t addr);

void EE_write_multi(uint16_t addr, uint8_t len, uint8_t *ptr);
void EE_read_multi(uint16_t addr, uint8_t len, uint8_t *ptr);

#endif
