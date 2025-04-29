#include "lcd.h"

static int lcd_print(char c, FILE *stream);

static FILE mystdout = FDEV_SETUP_STREAM(lcd_print, NULL, _FDEV_SETUP_WRITE);

static int lcd_print(char c, FILE *stream)
{
	lcd_write_data(c);
	return(0);
	
}

void lcdinit(void)
{
	LCD_PORT_DIR = 0xff;
	LCD_PORT = 0x00;
	_delay_ms(45);
	
	stdout = &mystdout;
	
	LCD_PORT &=~(1<<LCD_RS);
	
	
	for(uint8_t i=0; i<3; i++) //wysylanie 3 do lcd
	{
		LCD_PORT |=(1<<LCD_E);
		
		LCD_PORT = (LCD_PORT & 0x0f) | 0x30;
		_delay_us(1);
		
		LCD_PORT &=~(1<<LCD_E);
		_delay_ms(5);
	}
	
	LCD_PORT |=(1<<LCD_E); //wysylanie 2 do lcd
		
	LCD_PORT = (LCD_PORT & 0x0f) | 0x20;
	_delay_us(1);
		
	LCD_PORT &=~(1<<LCD_E);
	_delay_ms(100);

	lcd_write_command(0x28); // ustawianie lcd, 4bity 5x8 kropek
	//włączenie wyświetlacza
	//kursor nie miga
	lcd_write_command(0x0c); 
	//przejście na następne pole
	lcd_write_command(0x06); 
	
}

void lcd_write_command(uint8_t data)
{
	LCD_PORT &=~(1<<LCD_RS);
	
	//data na wyższych bitach

	
	LCD_PORT |=(1<<LCD_E);
	LCD_PORT = (LCD_PORT & 0x0f) | (data & 0xf0);
	_delay_us(1);
	LCD_PORT &=~(1<<LCD_E);
	
	_delay_us(100);
	
	//data na niższych bitach

	LCD_PORT |=(1<<LCD_E);
	LCD_PORT = (LCD_PORT & 0x0f) | (data & 0x0f)<<4;
	_delay_us(1);
	LCD_PORT &=~(1<<LCD_E);
	
	_delay_us(100);
}


void lcd_clear(void)
{
	lcd_write_command(1);
	_delay_ms(2);
}

void lcd_write_data(uint8_t data)
{
	LCD_PORT |=(1<<LCD_RS);
	
	//data na wyższych bitach
	
	LCD_PORT |=(1<<LCD_E);
	LCD_PORT = (LCD_PORT & 0x0f) | (data & 0xf0);
	_delay_us(1);
	LCD_PORT &=~(1<<LCD_E);
	
	_delay_us(100);
	
	//data na niższych bitach
	
	LCD_PORT |=(1<<LCD_E);
	LCD_PORT = (LCD_PORT & 0x0f) | (data & 0x0f)<<4;
	_delay_us(1);
	LCD_PORT &=~(1<<LCD_E);
	
	_delay_us(100);
}

void lcd_set_xy(uint8_t row, uint8_t col)
{
	lcd_write_command(0x80 | (0x40 * row + col));
}



void lcd_write_text_xy(uint8_t row, uint8_t col, char *text )
{
	lcd_set_xy(row,col);
	//wyświetlanie litera po literze
	while(*text!=0)
	{
		lcd_write_data((uint8_t)*text);
		//przesunięcie wskaźnika na następny element w pamięci
		text++;
	}
}


void lcd_write_text_P(const char *text )
{
	//register sprawia że zmienna jest w rejestrze
	register uint8_t ch;
	
	//text++ najpierw czyta pamięć potem zmienia adres
	while((ch=pgm_read_byte(text++)))
	{
		lcd_write_data(ch);
	}
}
