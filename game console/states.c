/*
 * States.c
 *
 * Created: 17/08/2014 2:21:46 PM
 *  Author: Samuel
 *  
 *
 */ 

// LCD buffer is no longer stored in the Atmega flash, it is
// already stored in FRAM.

/*
Variables to store:

lcd buffer - in FRAM
current backlight brightness (value of OCR0)

game states:
sketch:
	- current buffer
	- x position
	- y position

snake:
	- snake length
	- head x position
	- head y position
	- food x position
	- food y position
	- current score (if implemented)

rays:
	- player x position
	- player y position
	- player view angle

heli:
	- player x position
	- player y position
	- player score

*/

#include <stdint.h>
#include "states.h"
#include "lcd.h"
#include "fram.h"
#include "sketch.h"
#include "spi.h"

void 
save_state() {
		/* Data to save:
		LCD_Buffer   816 bytes
		sketch_x       1 byte
		sketch_y	   1 byte
		backlight      1 byte
		what program was previously running (if more than one)
		*/
		
		uint8_t i, j;
		
		fram_enable_write();
		
		// Prepare for data, start at address 0x000
		spi_transmit(0x02);	// Memory Write opcode with MSB of address (0)
		spi_transmit(0x00); // Transmit Address
		
		// Can pass all data after first address command, addresses are incremented automatically in the FRAM
		
		// First write the LCD buffer array, Page0, Page1 .. Page7
		for(i = 0; i < NUM_COLUMNS; i++) {
				for(j = 0; j < NUM_PAGES; j++) {
						spi_transmit(LCD_Buffer[i][j]);
				}
		}
		
		// Store Sketch cursor position and backlight level
		spi_transmit(sketch_x);
		spi_transmit(sketch_y);
		
		fram_disable();
}

//=> NOT ENOUGH SPACE IN FRAM TO STORE ENTIRE LCD BUFFER
void
read_state() {
		// Reads all user data from the FRAM
		
		uint8_t i, j;
		
		fram_enable_read();

		// Prepare for data read, start at address 0x000		
		spi_transmit(0x03); // Memory Write opcode with MSB of address (0)
		spi_transmit(0x00); // Transmit Address
		
		// Read LCD Buffer from memory
		for(i = 0; i < NUM_COLUMNS; i++) {
				for(j = 0; j < NUM_PAGES; j++) {
						LCD_Buffer[i][j] = spi_transmit_receive(0x00); // Transmit anything, FRAM ignores SI line
				}
		}
		
		// Retrieve sketch cursor position and backlight level
		sketch_x = spi_transmit_receive(0x00);
		sketch_y = spi_transmit_receive(0x00);
		
		fram_disable();
}