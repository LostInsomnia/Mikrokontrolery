#ifndef _TWI_H_
#define _TWI_H_

#include <avr/io.h>

#define F_SCL 100000
//TWPS=0

#define TWBR_VAL ((F_CPU/(2*F_SCL))-8)

#define ACK 0x01
#define NO_ACK 0x00

void I2C_init(void);
uint8_t I2C_start(void);
void I2C_stop(void);
uint8_t I2C_write(uint8_t byte);
uint8_t I2C_read(uint8_t *value, uint8_t ack);



#endif
