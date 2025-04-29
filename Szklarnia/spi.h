#ifndef _SPI_H_
#define _SPI_H_

#include <avr/io.h>
#define SS PB4
#define MOSI PB5
#define MISO PB6
#define SCK PB7

#define SS_ENABLE() {PORTB&=~(1<<SS);}
#define SS_DISABLE() {PORTB |=(1<<SS);}

void SPI_MasterInit(void);
uint8_t SPI_MasterTransmit(uint8_t data);

#endif
