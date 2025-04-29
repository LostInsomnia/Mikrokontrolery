#ifndef _OWI_H_
#define _OWI_H_

#include <avr/io.h>
#include <util/delay.h>

#define OW_PIN PB3
#define OW_DIR DDRB
#define OW_PORT PORTB
#define OW_IN PINB

#define OW_low OW_DIR|=(1<<OW_PIN)
#define OW_high OW_DIR&=~(1<<OW_PIN)
#define OW_check (OW_IN & (1<<OW_PIN))

uint8_t OW_reset(void);
void OW_send(uint8_t byte);
uint8_t OW_recv(void);

#endif
