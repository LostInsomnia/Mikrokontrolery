#ifndef _RS232_H_
#define _RS232_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#define MAXSIZE 32

extern volatile uint8_t sign;

extern volatile char *buffer;
extern volatile uint8_t bufferRead[MAXSIZE];
extern volatile uint8_t index;
extern volatile uint8_t end;

void USART_init(uint8_t ubrr);
void USART_wait_for_empty(void);
void USART_send(char* text);

#endif
