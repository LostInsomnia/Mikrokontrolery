#include "rs232.h" 

volatile uint8_t sign =0;

volatile char *buffer;
volatile uint8_t bufferRead[MAXSIZE];
volatile uint8_t index=0;
volatile uint8_t end=0;

void USART_init(uint8_t ubrr)
{
	//Ustawianie baud
	UBRRH = (uint8_t)ubrr>>8;//MSB
	UBRRL = (uint8_t)ubrr;//LSB
	
	//Odbiornik i Transmiter
	UCSRB |=(1<<RXEN)|(1<<TXEN);
	
	//Przerwanie RX
	UCSRB |=(1<<RXCIE);
	
	//Ustawianie formatu
	UCSRC |=(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
}
void USART_wait_for_empty(void)
{
	//Czekanie na flagę UDRE -> buffer UDR jest pusty
	while(!(UCSRA & (1<<UDRE)));
}
void USART_send(char* text)
{
	USART_wait_for_empty();
	buffer = (uint8_t *)text;
	//przerwanie -> transmisja
	UCSRB|=(1<<UDRIE);
}

ISR(USART_RXC_vect)
{
	sign=UDR;
	if(index>=(MAXSIZE-1)) index =0;
	bufferRead[index]=sign;
	index++;
	if(sign =='\n' || sign == '\r') end = 1;
	else end=0;
}

ISR(USART_UDRE_vect)
{
	if(*buffer) UDR=*(buffer++);
	else UCSRB &=~(1<<UDRIE);//wyłączenie przerwania gdy buffer pusty
}
