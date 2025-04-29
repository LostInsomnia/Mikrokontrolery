#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"
#include "owi.h"
#include "temp.h"
#include "rs232.h"
#include "spi.h"

#define MAX_VAL 10

#define BAUD 1000000
#define UBRR_VALUE (F_CPU/(16*BAUD)-1)
double tem = 0;
char bufferSend[16];

#define SERVO_DDR DDRD
#define SERVO PD5

#define WAVE 39999 //20ms
#define MID 2999 //1.5ms
#define MIN 1500 //0.5ms 
#define MAX 4500 //2.5ms

volatile uint16_t val =0;
uint8_t state = 2;
double voltage = 0;
volatile uint8_t wilg = 0;
volatile uint8_t value_change=0;
uint16_t values[MAX_VAL];
volatile uint8_t ind=0;
volatile uint8_t full=0;
volatile uint16_t ms =0;
volatile 	uint8_t temp =0;

ISR(TIMER0_COMP_vect)
{
	uint8_t temp;

	ms+=1;
	if(ms>=1000){
		SS_ENABLE();
		//Start komunikacji
		SPI_MasterTransmit(0x01);
		//Wysyłanie wartości SGL=1, ODD=1, MSBF=1, Ch0
		//tryb single-ended, najpierw MSB
		temp = SPI_MasterTransmit(0xa0);
		val = ((temp & 0x0f)<<8);
		temp = SPI_MasterTransmit(0x00);
		val|=temp;
		SS_DISABLE();
		
		value_change=1;
		ms=0;
	}
	
}





int main(void)
{
	
	uint16_t servo = MID;
	SERVO_DDR |=(1<<SERVO);
	
	TCCR1A|=(1<<WGM11);
	TCCR1B|=(1<<WGM13)|(1<<WGM12);
	TCCR1A|=(1<<COM1A1);
	TCCR1B|=(1<<CS11);//prescaler 8
	ICR1=WAVE;
	
	OCR1A=MID;
	_delay_ms(2000);
	
	SPI_MasterInit();
	_delay_ms(1000);
	
	TCCR0 =(1<<CS01)|(1<<CS00);
	OCR0=6;
	TIMSK=(1<<OCIE0);
	sei();
	
	USART_init(UBRR_VALUE);
	sei();
	USART_send("Hello!\r\n");
	int16_t temperature;
	
	lcdinit();
	temp_init();

	while(1)
	{
		temp_start();
		while(! OW_check);
		temperature = temp_read();
		
		
		//lcd_set_xy(1,0);
		//printf("T=%5.1f \337C     ", ((double)temperature)*0.0625);
		
		
		lcd_set_xy(0,0);
		printf("T=%3d.%04d \337C      ", temperature >> 4, (temperature & 0x0f)*625);
		
		
		if(value_change)
		{
			voltage=5*val/4096.0;
			wilg = voltage*20;
			value_change=0;
			
			lcd_set_xy(1,0);
			printf("WIlg: %d \%", wilg);
			
		}
			
		
		if(end)
		{
			if(strncmp((void *)bufferRead, "temp", 4)==0)
			{
				sprintf(bufferSend, "\r\nT=%5.1f \337C     \r\n ",((double)temperature)*0.0625);
				USART_send(bufferSend);
			}
			else if(strncmp((void *)bufferRead, "wilg", 4)==0)
			{
				sprintf(bufferSend, "\r\nWilg = %d     \r\n ",wilg);
				USART_send(bufferSend);
			}
			else USART_send("\r\nUnknown command\r\n ");
			end=0;
			index=0;
			memset((void *)bufferRead,0,MAXSIZE);
			
		}
		
		if((wilg>70 || (((double)temperature)*0.0625)>=25)){
			
			while(servo<=MAX){

				servo++;
				OCR1A=servo;
				_delay_us(500);
			}
		}
		if(wilg<70 && (((double)temperature)*0.0625)<25){
			
			while(servo>=MIN){
				
				servo--;
					OCR1A=servo;
				_delay_us(500);
			}
			
		}
		
	}

	return 0;
}
