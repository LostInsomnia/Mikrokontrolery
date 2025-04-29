#include "owi.h"

uint8_t OW_reset(void)
{
	uint8_t presence;
	OW_low;
	_delay_us(480);
	OW_high;
	_delay_us(70);
	//sprawdzanie urządzeń -> 0 - podlączone
	presence = OW_check;
	_delay_us(410);
	return presence;
}

void OW_send(uint8_t byte)
{
	uint8_t i;
	for(i=0; i<8; i++)
	{
		if(byte & 0x01)
		{
			OW_low;
			_delay_us(6);
			OW_high;
			_delay_us(64);
		}
		else
		{
			OW_low;
			_delay_us(60);
			OW_high;
			_delay_us(10);
		}
		byte>>=1;
	}
}

uint8_t OW_recv(void)
{
	uint8_t byte=0;
	uint8_t i;
	
	for(i=0; i<8; i++)
	{
		byte>>=1;
		OW_low;
		_delay_us(6);
		OW_high;
		_delay_us(9);
		if(OW_check) byte|=0x80;
		_delay_us(55);
				
	}
	return byte;
}
