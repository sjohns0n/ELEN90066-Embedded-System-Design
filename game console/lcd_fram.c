/* 
 * Storing the LCD_Buffer in FRAM instead of the SRAM in the Atmega.
 * The Atmega only has 1kbyte of SRAM, and the LCD_Buffer[][] uses ~800 bytes.
 * This does not leave enough space to safely store stack variables and other runtime variables.
 * 
 * The FRAM should be fast enough to send and retrieve relevant buffer information.
 * 
 * The idea is to update the data in the FRAM buffer, and then to update the LCD, grab one page
 * of information at a time, store it locally in the Atmega SRAM and then send it the LCD. This 
 * should limit the need for large chunks of SRAM, allowing the rest of the program to run smoothly.
 * 
 * 
 * 
 * For functions that modify the buffer, they will need to read/write to the external FRAM instead
 * of a global variable.
 * 
 * At the moment the location of the buffer is from address 0x0000 to 0x1FFF 
 * This is the first 816 bytes of the FRAM.
 * Each page is stored sequentially, with 102 bytes per page
 * 
 * - Address checking before modifying?
 *	 ie:	 
 * - Interrupt driven FRAM updates?  - too much work for this application
 */

// Used by util/delay.h
#define F_CPU 8000000 // 8MHz

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "fram.h"

#define LCD_PORT PORTB#define FRAM_PORT PORTB

#define FRAM_BOTTOM 0x0000
//#define FRAM_TOP    0x1FFF // FOR 64Kbit FRAM
#define FRAM_TOP	0x07FF // FOR 2Kbit FRAM (as in kit)

#define LCD_BUFFER_START_ADDRESS 0x0000
#define LCD_BUFFER_STOP_ADDRESS 0x032F
#define PAGE0_START 0x0000 
#define PAGE1_START 0x0065 
#define PAGE2_START 0x00CB 
#define PAGE3_START 0x0131 
#define PAGE4_START 0x0197
#define PAGE5_START 0x01FD
#define PAGE6_START 0x0263
#define PAGE7_START 0x02C9

#define COLUMN_OFFSET 30 // Used if display is inverted

// Initialise the buffer in FRAM.
void
lcd_buffer_init() {
	uint16_t addr;
		
	// Set all values in buffer to zero (nothing to display)
	for(addr = LCD_BUFFER_START_ADDRESS; addr <= LCD_BUFFER_STOP_ADDRESS; addr++) {
		fram_write(addr, 0);
	}
}

// Set all bits in the LCD buffer to zero
void lcd_buffer_clear() {
	uint16_t addr;
	
	for(addr = LCD_BUFFER_START_ADDRESS; addr <= LCD_BUFFER_STOP_ADDRESS; addr++) {
		fram_write(addr, 0);
	}
}



//------- START LCD_UPDATE() ------------//
//------- 
/* Two methods for updating the LCD
 * 
 * 1. Each time the interrupt is triggered, update the entire LCD.
 *	  This will retrieve the entire buffer from the FRAM, sending the whole
 *	  thing to the LCD.
 *	  
 *
 * 2. Each time the interrupt is triggered, only send one page to the LCD.
 *    This will retrieve one page and send it to the LCD. To update the 
 *    entire LCD will take 8 interrupt routines.
 *    
 * For each method you should configure the interrupt frequency.
 * Method 1 - less often
 * Method 2 - ~8 times as often
 * 
 * For each method, instead of getting a page of data in one go, get and send
 * each byte as you go.
 * This probably isn't as fast, as you need to enable/disable both devices and
 * enable Read for the FRAM each time you get a byte
 */

#define LCD_PAGE_OPCODE 0xB0

/*
void
lcd_update() {
	// 	METHOD 1
	// Enable LCD, set Page, set Column
	uint8_t page, col;
	uint8_t page_data[PAGE_WIDTH];
	
	for(page = 0; page < NUM_PAGES; page++) {				
		// Retrieve whole page data
		fram_enable_read();
		for(col = 0; col < PAGE_WIDTH; col++) {
			page_data[col] = fram_read(page*PAGE_WIDTH + col);
		}
		fram_disable();
		
		lcd_enable();
		
		// Set the Page
		spi_transmit(LCD_PAGE_OPCODE + page);
				
		// Write whole Page to LCD
		for(col = 0; col < NUM_COLUMNS; col++) {
			// Set column to write to
			// Need to send two bytes for upper and lower nibbles of column address in SRAM
			// Due to display orientation, the column addresses are from 30..131 (+30 offset)
			LCD_PORT &= ~_BV(LCD_COMMAND_PIN); // commands
			spi_transmit(0x00 + (0x0F & (col + COLUMN_OFFSET))); // LSB
			spi_transmit(0x10 + (0xF0 & (col + COLUMN_OFFSET))); // MSB
			
			// Send data
			LCD_PORT |= _BV(LCD_COMMAND_PIN);
			spi_transmit(page_data[col]);
		}
	}
	
	lcd_disable();
}
}*/


void
lcd_update() {
	// 	METHOD 2
	// Enable LCD, set Page, set Column
	static uint8_t page = 0; // current page to send
	uint8_t col;
	uint8_t PAGE_DATA[PAGE_WIDTH];
	
	// Retrieve whole page data
	for(col = 0; col < PAGE_WIDTH; col++) {
		PAGE_DATA[col] = fram_read(page*PAGE_WIDTH + col);
	}
	
	Enable_LCD();
	LCD_PORT &= ~_BV(LCD_CD);
	// Set the Page
	spi_transmit(LCD_PAGE_OPCODE + page);
	
	// Write whole Page to LCD
	for(col = 0; col < NUM_COLUMNS; col++) {
		// Set column to write to
		// Need to send two bytes for upper and lower nibbles of column address in SRAM
		// Due to display orientation, the column addresses are from 30..131 (+30 offset)
		LCD_PORT &= ~_BV(LCD_CD); // commands
		SPI_Transmit(0x00 + (0x0F & (col + COLUMN_OFFSET))); // LSB
		SPI_Transmit(0x10 + (0xF0 & (col + COLUMN_OFFSET))); // MSB
		
		// Send data
		LCD_PORT |= _BV(LCD_CD);
		SPI_Transmit(PAGE_DATA[col]);
	}	
	
	Disable_LCD();
	
	page++;
	if(page >= NUM_PAGES) {
		page = 0;
	}
	
}
//----------- END LCD_UPDATE() ------------//

void
lcd_init() {
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
				0x27, // VLCD Resistor Ratio	|
				0x81, // Set Electronic Volume	+--	Set contrast
				0x10, // Set Electronic Volume	|
			  //0xFA, // Temperature Compensation
			  //0x90, // Temperature Compensation
				0xAF  // Display ON
		};
		
		// Enable LCD, sending commands only 
		LCD_CHIP_SELECT_PORT &= ~_BV(LCD_CHIP_SELECT_PIN);
		LCD_PORT &= ~_BV(LCD_COMMAND_PIN);
		
		// Transmit codes to LCD
		uint8_t i;
		for(i = 0; i < NUM_LCD_OPCODES; i++) {
				spi_transmit(init_opcodes[i]);
		}
		
		// Disable LCD
		LCD_CHIP_SELECT_PORT |= _BV(LCD_CHIP_SELECT_PIN);
		
		// Initialise FRAM buffer by writing all data to zero
		lcd_buffer_init();
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

void lcd_enable() {
	LCD_CHIP_SELECT_PORT &= ~_BV(LCD_CHIP_SELECT_PIN);
}
void lcd_disable() {
	LCD_CHIP_SELECT_PORT |= _BV(LCD_CHIP_SELECT_PIN);
}

void
lcd_send_data(uint8_t data) {
	// Enable LCD, sending data
	LCD_CHIP_SELECT_PORT &= ~_BV(LCD_CHIP_SELECT_PIN);
	LCD_PORT |= _BV(LCD_COMMAND_PIN);
	
	spi_transmit(data);
	
	// Disable LCD
	LCD_CHIP_SELECT_PORT |= _BV(LCD_CHIP_SELECT_PIN);
}

void
lcd_send_command(uint8_t command) {
	// Enable LCD, sending command
	LCD_CHIP_SELECT_PORT &= ~_BV(LCD_CHIP_SELECT_PIN);
	LCD_PORT &= ~_BV(LCD_COMMAND_PIN);
	
	spi_transmit(command);
	
	// Disable LCD
	LCD_CHIP_SELECT_PORT |= _BV(LCD_CHIP_SELECT_PIN);
}

void
lcd_reset() {
	// Enable LCD, sending a command
	LCD_CHIP_SELECT_PORT &= ~_BV(LCD_CHIP_SELECT_PIN);
	LCD_PORT &= ~_BV(LCD_COMMAND_PIN);
	
	// Send reset command code
	spi_transmit(0xE2);
	
	// Disable LCD
	LCD_CHIP_SELECT_PORT |= _BV(LCD_CHIP_SELECT_PIN);
}

void
lcd_set_all_on() {
	// Enable LCD, sending a command
	LCD_CHIP_SELECT_PORT &= ~_BV(LCD_CHIP_SELECT_PIN);
	LCD_PORT &= ~_BV(LCD_COMMAND_PIN);
	
	// Send all drivers ON command
	spi_transmit(0xA5);
	
	// Disable LCD
	LCD_CHIP_SELECT_PORT |= _BV(LCD_CHIP_SELECT_PIN);
}


