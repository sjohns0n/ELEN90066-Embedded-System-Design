/*
 * lcd.h
 *
 * Created: forgot to write it down
 *  Author: Samuel
 */ 

#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include <stdint.h>

#define LCD_CHIP_SELECT_PORT		PORTB
#define LCD_CHIP_SELECT_PORT_DIR	DDRB
#define LCD_CHIP_SELECT_PIN			PB4

#define LCD_COMMAND_PORT     PORTC
#define LCD_COMMAND_PORT_DIR DDRC
#define LCD_COMMAND_PIN      PC0

#define LCD_RESET_PORT	   PORTC
#define LCD_RESET_PORT_DIR DDRC
#define LCD_RESET_PIN	   PC7

#define SCREEN_WIDTH 102 // in pixels
#define SCREEN_HEIGHT 64

#define NUM_COLUMNS SCREEN_WIDTH
#define NUM_PAGES 8
#define PAGE_WIDTH NUM_COLUMNS

#define LCD_PAGE_COMMAND 0xB0

// If display orientation is "12 o'clock", as in datasheet
#define COLUMN_OFFSET 30

#define FLASH_TIME 100
#define LCD_INVERT_DISPLAY 0xA7
#define LCD_NORMAL_DISPLAY 0xA6

void lcd_init(void);
void lcd_reset(void);
void lcd_screen_clear(void);
void lcd_send_command(uint8_t command);
void lcd_send_data(uint8_t data);
void lcd_enable_command(void);
void lcd_enable_data(void);
void lcd_disable(void);
void lcd_set_page(uint8_t page);
void lcd_set_column(uint8_t column);
void lcd_invert_flash(void);
void lcd_set_display_inverse(void);
void lcd_set_display_normal(void);

#endif //LCD_H_