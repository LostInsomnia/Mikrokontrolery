#include "eeprom.h"

void EE_write_byte(uint16_t addr, uint8_t data)
{
	I2C_start();
	I2C_write(EE_ADDR_W);
	I2C_write(addr>>8); //MSB
	I2C_write(addr);
	I2C_write(data);
	I2C_stop();
	_delay_ms(10);
}
uint8_t EE_read_byte(uint16_t addr)
{
	uint8_t data;
	I2C_start();
	I2C_write(EE_ADDR_W);
	I2C_write(addr>>8); //MSB
	I2C_write(addr);
	I2C_start();
	I2C_write(EE_ADDR_R);
	I2C_read(&data, NO_ACK);
	I2C_stop();
	return data;
}

void EE_write_multi(uint16_t addr, uint8_t len, uint8_t *ptr)
{
	I2C_start();
	I2C_write(EE_ADDR_W);
	I2C_write(addr>>8); //MSB
	I2C_write(addr);
	for(uint8_t i =0; i<len; i++){
		I2C_write(*(ptr++));
	}
	
	I2C_stop();
	_delay_ms(10);
}
void EE_read_multi(uint16_t addr, uint8_t len, uint8_t *ptr)
{
	I2C_start();
	I2C_write(EE_ADDR_W);
	I2C_write(addr>>8); //MSB
	I2C_write(addr);
	I2C_start();
	I2C_write(EE_ADDR_R);
	for(uint8_t i =0; i<len; i++){
		I2C_read(ptr++,ACK);
	}
	I2C_read(ptr, NO_ACK);
	I2C_stop();
	_delay_ms(10);
}
