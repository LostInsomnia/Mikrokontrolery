#include "temp.h"

uint8_t temp_init(void)
{
	OW_reset();
	return OW_reset();
}

uint8_t temp_start(void)
{
	if(OW_reset()) return 1; //Niepodłączone urządzenie
	OW_send(0xCC); //Skip ROM
	OW_send(0x44);
	return 0;
}

int16_t temp_read(void)
{
	int16_t temperature;
	OW_reset();
	OW_send(0xCC);
	OW_send(0xBE);
	temperature = OW_recv();
	temperature |=((int16_t)OW_recv())<<8;
	return temperature;
}
