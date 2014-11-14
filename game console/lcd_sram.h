/*
 * LCD.h
 *
 * Created: 17/08/2014 12:37:59 PM
 *  Author: Samuel
 */ 

#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>
#include <avr/io.h>

#include "spi.h"
#include "adc.h"

#define SCREEN_WIDTH 102
#define SCREEN_HEIGHT 64

#define LCD_CHIP_SELECT_PORT		PORTB
#define LCD_CHIP_SELECT_PORT_DIR	DDRB
#define LCD_CHIP_SELECT_PIN			PB4

#define LCD_COMMAND_PORT     PORTC
#define LCD_COMMAND_PORT_DIR DDRC
#define LCD_COMMAND_PIN      PC0

#define LCD_RESET_PORT	   PORTC
#define LCD_RESET_PORT_DIR DDRC
#define LCD_RESET_PIN	   PC7

#define LCD_BACKLIGHT_PORT		PORTB
#define LCD_BACKLIGHT_PORT_DIR  DDRB
#define LCD_BACKLIGHT_PIN		PB3

#define LCD_INVERT_DISPLAY 0xA7 // inverse SRAM content
#define LCD_NORMAL_DISPLAY 0xA6 // normal SRAM content
#define FLASH_TIME 100 // in ms

#define REFRESH_RATE 60 // In Hz

/// DOGS LCD data
#define NUM_PAGES       8
#define NUM_COLUMNS     102
#define NUM_LCD_OPCODES 11

#define PAGE_WIDTH 102

void lcd_init(void);
void lcd_reset(void);
void lcd_disable(void);
void lcd_enable(void);
void lcd_set_all_on(void);
void lcd_send_command(uint8_t command);
void lcd_send_data(uint8_t data);
void lcd_update(void);
void lcd_buffer_clear(void);
void lcd_set_display_inverse(void);
void lcd_set_display_normal(void);
void lcd_invert_flash(void);

//---- ONLY FOR SRAM STORAGE OF BUFFER ----//
//
// LCD display buffer
// Store the current state of each pixel in the LCD array,
// Use an interrupt to regularly update the display
// LCD has area 102 x 64 dots
// 102 columns
// 8 rows (pages)
// 

uint8_t LCD_Buffer[NUM_COLUMNS][NUM_PAGES];
// 
//---- ONLY FOR SRAM STORAGE OF BUFFER ----// 

#endif /* LCD_H_ */