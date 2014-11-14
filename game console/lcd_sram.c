/*
 * LCD.c
 *
 * Created: 17/08/2014 12:37:47 PM
 *  Author: Samuel
 */ 

#define F_CPU 8000000

#include "lcd.h"
#include <util/delay.h>
#include <avr/interrupt.h>

void lcd_buffer_init() {
	uint8_t i, j;
	for(i = 0; i < NUM_COLUMNS; i++) {
		for(j = 0; j < NUM_PAGES; j++) {
			LCD_Buffer[i][j] = 0;
		}
	}
}

void
lcd_init() {
	//lcd_buffer_init();
		/*  Example initialisation codes from page 6 of the LCD DOGS module datasheet,
			excluding the temperature compensation config */
		uint8_t init_opcodes[NUM_LCD_OPCODES] = {
				0x40, // Display start line 0
				0xA0, // Seg 'normal'. Sets correct orientation for display 
				0xC8, // Reversed COM direction, as screen is 'upside down'
				0xA4, // Show SRAM content
				0xA6, // Display inverse OFF
				0xA2, // Set bias 1/9
				0x2F, // Booster, regulator and follower ON
				0x27, //
				0x81, // Set contrast
				0x10, //
				0xAF  // Display ON
		};
		
		// Enable output for LCD pins
		LCD_COMMAND_PORT_DIR |= _BV(LCD_COMMAND_PIN);
		LCD_CHIP_SELECT_PORT_DIR |= _BV(LCD_CHIP_SELECT_PIN);
		
		// Enable LCD, sending commands only 
		LCD_CHIP_SELECT_PORT &= ~_BV(LCD_CHIP_SELECT_PIN);
		LCD_COMMAND_PORT &= ~_BV(LCD_COMMAND_PIN);
		
		// Transmit codes to LCD
		uint8_t i;
		for(i = 0; i < NUM_LCD_OPCODES; i++) {
			spi_transmit(init_opcodes[i]);
			if(i == 3) _delay_ms(120);			
		}
		
		// Disable LCD
		LCD_CHIP_SELECT_PORT |= _BV(LCD_CHIP_SELECT_PIN);
}

// Flash display
void lcd_invert_flash() {
	lcd_set_display_inverse();
	_delay_ms(FLASH_TIME);
	lcd_set_display_normal();
	_delay_ms(FLASH_TIME);
	lcd_set_display_inverse();
	_delay_ms(FLASH_TIME);
	lcd_set_display_normal();
}

void lcd_set_display_inverse() {
	lcd_send_command(LCD_INVERT_DISPLAY);
}

void lcd_set_display_normal() {
	lcd_send_command(LCD_NORMAL_DISPLAY);
}

void lcd_enable() {
	LCD_CHIP_SELECT_PORT &= ~_BV(LCD_CHIP_SELECT_PIN);
}
void lcd_disable() {
	LCD_CHIP_SELECT_PORT |= _BV(LCD_CHIP_SELECT_PIN);
}

/* Sends the current buffer to the LCD */
void
lcd_update() {
		uint8_t i, j, data;
		
		// Enable LCD
		LCD_CHIP_SELECT_PORT &= ~_BV(LCD_CHIP_SELECT_PIN);
		
		for(i = 0; i < NUM_PAGES; i++) { // cycle through pages 0..7
				// Set PAGE to write to
				LCD_COMMAND_PORT &= ~_BV(LCD_COMMAND_PIN); // command
				spi_transmit(0xB0 + i);
				
				for(j = 0; j < NUM_COLUMNS; j++) { // cycle through column address
						// Set column to write to
						// Need to send two bytes for upper and lower nibbles of column address in SRAM
						// Due to display orientation, the column addresses are from 30..131 (+30 offset)
						LCD_COMMAND_PORT &= ~_BV(LCD_COMMAND_PIN); // commands
						spi_transmit(0x00 + (0x0F & (j + 30))); // LSB
						spi_transmit(0x10 + (0xF0 & (j + 30))); // MSB
						
						LCD_COMMAND_PORT |= _BV(LCD_COMMAND_PIN); // data
						data = LCD_Buffer[j][i]; // get data to send from buffer					
						spi_transmit(data);
				}
		}
		
		// Disable LCD
		LCD_CHIP_SELECT_PORT |= _BV(LCD_CHIP_SELECT_PIN);
}
  
/* Sets all bits in the LCD buffer to zero (all pixels OFF) */
void
lcd_buffer_clear() {
	uint8_t i, j;
	for(i = 0; i < NUM_COLUMNS; i++) {
		for(j = 0; j < NUM_PAGES; j++) {
			LCD_Buffer[i][j] = 0;
		}
	}
}
 
void 
lcd_send_data(uint8_t data) {
		// Enable LCD, sending data
		LCD_CHIP_SELECT_PORT &= ~_BV(LCD_CHIP_SELECT_PIN);
		LCD_COMMAND_PORT |= _BV(LCD_COMMAND_PIN);
		
		spi_transmit(data);
		
		// Disable LCD
		LCD_CHIP_SELECT_PORT |= _BV(LCD_CHIP_SELECT_PIN);
}

void 
lcd_send_command(uint8_t command) {
		// Enable LCD, sending command
		LCD_CHIP_SELECT_PORT &= ~_BV(LCD_CHIP_SELECT_PIN);
		LCD_COMMAND_PORT &= ~_BV(LCD_COMMAND_PIN);
		
		spi_transmit(command);
		
		// Disable LCD
		LCD_CHIP_SELECT_PORT |= _BV(LCD_CHIP_SELECT_PIN);
}
		

void
lcd_reset() {
		// Enable LCD, sending a command
		LCD_CHIP_SELECT_PORT &= ~_BV(LCD_CHIP_SELECT_PIN);
		LCD_COMMAND_PORT &= ~_BV(LCD_COMMAND_PIN);
		
		// Send reset command code
		spi_transmit(0xE2);
		
		// Disable LCD
		LCD_CHIP_SELECT_PORT |= _BV(LCD_CHIP_SELECT_PIN);
}

void
lcd_set_all_on() {
		// Enable LCD, sending a command
		LCD_CHIP_SELECT_PORT &= ~_BV(LCD_CHIP_SELECT_PIN);
		LCD_COMMAND_PORT &= ~_BV(LCD_COMMAND_PIN);
		
		// Send all drivers ON command
		spi_transmit(0xA5);
	
		// Disable LCD
		LCD_CHIP_SELECT_PORT |= _BV(LCD_CHIP_SELECT_PIN);
}