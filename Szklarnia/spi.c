#include "spi.h"

void SPI_MasterInit(void)
{
	
	//Konfiguracja I/O
	DDRB|=(1<<SS)|(1<<MOSI)|(1<<SCK);
	PORTB=(1<<SS);
	DDRB&=~(1<<MISO);
	//Włączanie SPI
	SPCR|=(1<<SPE);
	//Master mode
	SPCR|=(1<<MSTR);
	//Ustawianie prescalera -> 16 żeby był mniejszy niż f=1.8MHZ konwertera
	SPCR|=(1<<SPR0);
}
uint8_t SPI_MasterTransmit(uint8_t data)
{
	SPDR=data;
	
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}
