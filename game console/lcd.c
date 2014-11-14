/*
 * lcd.c
 *
 * Created: forgot to write it down
 *  Author: Samuel
 */ 

#include "lcd.h"
#include "spi.h"
#include "fram.h"
#include "lcdbuffer.h"
#include "defines.h"

#define F_CPU 8000000
#include <util/delay.h>

/* Sets up the communication pins for the LCD and
 * sends initialisation codes to the LCD for correct operation.
 * This includes a RESET pin toggle to reset the LCD. */
void lcd_init() {
	// Setup input/output pins for LCD
	LCD_COMMAND_PORT_DIR |= _BV(LCD_COMMAND_PIN);
	LCD_CHIP_SELECT_PORT_DIR |= _BV(LCD_CHIP_SELECT_PIN);
	LCD_RESET_PORT_DIR |= _BV(LCD_RESET_PIN);
	
	// Disable LCD from receiving data
	LCD_COMMAND_PORT |= _BV(LCD_COMMAND_PIN);
	LCD_CHIP_SELECT_PORT |= _BV(LCD_CHIP_SELECT_PIN);
	LCD_RESET_PORT |= _BV(LCD_RESET_PIN);
	
	lcd_reset(); 

	// Send setup codes to the LCD
	lcd_send_command(0x40);//Display start line 0
	lcd_send_command(0xA0);//SEG direction for 12 o'clock view
	lcd_send_command(0xC8);//COM direction reverse COM63 - COM0
	lcd_send_command(0xA4);//Disable -> Set All Pixel to ON
	lcd_send_command(0xA6);//Display inverse off
	_delay_ms(120);
	lcd_send_command(0xA2);//Set LCD Bias Ratio A2/A3
	lcd_send_command(0x2F);//Set Power Control 28...2F
	lcd_send_command(0x27);//Set VLCD Resistor Ratio 20...27
	lcd_send_command(0x81);//Set Electronic Volume
	lcd_send_command(0x10);//Set Electronic Volume 00...3F
	lcd_send_command(0xFA);//Set Adv. Program Control
	lcd_send_command(0x90);//Set Adv. Program Control x00100yz yz column wrap x Temp Comp
	lcd_send_command(0xAF);//Display on
}

/* Toggles the LCD RESET pin to reset the LCD */
void lcd_reset() {
	LCD_RESET_PORT &= ~_BV(LCD_RESET_PIN);
	_delay_ms(10); // just to be safe
	LCD_RESET_PORT |= _BV(LCD_RESET_PIN);
}

/* Clears the screen. Does not alter the buffers. */
void lcd_screen_clear() {
	uint8_t page, column;
	for(page = 0; page < NUM_PAGES; page++) {
		lcd_set_page(page);
		for(column = 0; column < NUM_COLUMNS; column++) {
			lcd_set_column(column);
			lcd_send_data(0x00); // clear data
		}
	}	
}

// Chooses page to write data to
void lcd_set_page(uint8_t page) {
	lcd_send_command(LCD_PAGE_COMMAND | page);
}

// Chooses column to write data to
void lcd_set_column(uint8_t column) {
	lcd_send_command(LCD_COL_MSB | (((column + COLUMN_OFFSET) >> 4) & LOW_NIBBLE)); //MSB
	lcd_send_command(LCD_COL_LSB | ((column + COLUMN_OFFSET) & LOW_NIBBLE)); // LSB
}

void lcd_send_command(uint8_t command) {
	lcd_enable_command();
	spi_transmit(command);
	lcd_disable();
}

void lcd_send_data(uint8_t data) {
	lcd_enable_data();
	spi_transmit(data);
	lcd_disable();
}

/* Set appropriate pins for sending commands to the LCD */
void lcd_enable_command() {
	LCD_COMMAND_PORT &= ~_BV(LCD_COMMAND_PIN);
	LCD_CHIP_SELECT_PORT &= ~_BV(LCD_CHIP_SELECT_PIN);	
}

/* Set appropriate pins for sending data to the LCD */
void lcd_enable_data() {
	LCD_COMMAND_PORT |= _BV(LCD_COMMAND_PIN);
	LCD_CHIP_SELECT_PORT &= ~_BV(LCD_CHIP_SELECT_PIN);	
}

void lcd_disable() {
	LCD_CHIP_SELECT_PORT |= _BV(LCD_CHIP_SELECT_PIN);
}

// Flash display twice
void lcd_invert_flash() {
	lcd_set_display_inverse();
	_delay_ms(FLASH_TIME);
	lcd_set_display_normal();
	_delay_ms(FLASH_TIME);
	lcd_set_display_inverse();
	_delay_ms(FLASH_TIME);
	lcd_set_display_normal();
}

// LCD to show inverse SRAM content
void lcd_set_display_inverse() {
	lcd_send_command(LCD_INVERT_DISPLAY);
}

// LCD to show normal SRAM content
void lcd_set_display_normal() {
	lcd_send_command(LCD_NORMAL_DISPLAY);
}