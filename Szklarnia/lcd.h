#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdio.h>

#ifndef LCD_PORT
#define LCD_PORT PORTA
#endif

#ifndef LCD_PORT_DIR
#define LCD_PORT_DIR DDRA
#endif

#ifndef LCD_E
#define LCD_E PA3
#endif

#ifndef LCD_RS
#define LCD_RS PA2
#endif


void lcdinit(void);
void lcd_write_command(uint8_t data);
void lcd_clear(void);
void lcd_write_data(uint8_t data);
void lcd_set_xy(uint8_t row, uint8_t col);
void lcd_write_text_xy(uint8_t row, uint8_t col, char *text );
void lcd_write_text_P(const char *text );
#endif
