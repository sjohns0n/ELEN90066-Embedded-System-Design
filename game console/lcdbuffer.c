/*
 * lcdbuffer.c
 *
 * Created: 13/10/2014 4:30:22 PM
 *  Author: Samuel
 */ 
 
 /* Functions for reading/writing the lcd buffer stored in FRAM */

#include <stdint.h>
#include "fram.h"
#include "lcd.h"
#include "lcdbuffer.h"
#include "defines.h"

// Initialise the buffer in FRAM.
void buffers_init() {
	buffer_clear(FRAME0);
	buffer_clear(FRAME1);
}

// Set all bits in the selected LCD buffer to zero
void buffer_clear(uint8_t buffer)
{
	uint16_t addr, start_addr, stop_addr;
	if(buffer == FRAME0) {
		start_addr = BUFFER_0_START_ADDR;
		stop_addr = BUFFER_0_STOP_ADDR;
	} else {
		start_addr = BUFFER_1_START_ADDR;
		stop_addr = BUFFER_1_STOP_ADDR;
	}

	// Set all values in buffer to zero (nothing to display)
	for(addr = start_addr; addr <= stop_addr; addr++) {
		fram_write(addr, CLEAR);
	}
}

/* Sets a bit at position (x, y) in the buffer stored in FRAM.
 * This functions reads the current byte where the bit to be set is,
 * to make sure it does not clobber the existing bit values there. */
void buffer_set_bit(uint8_t x, uint8_t y, uint8_t buffer) {
	uint8_t page = y/NUM_PAGES; // find page bit is in
	uint16_t addr = page*PAGE_WIDTH + x + (buffer * BUFFER_SIZE); // address in FRAM
	uint8_t current_data = fram_read(addr); // get current bit value
	uint8_t data = current_data | _BV(y%8); // OR with bit to be written
	fram_write(addr, data); // write data
}

/* Returns the state of the bit at position (x, y) */
uint8_t buffer_get_bit(uint8_t x, uint8_t y, uint8_t buffer) {
	uint8_t page = y/NUM_PAGES;
	uint16_t addr = page*PAGE_WIDTH + x + (buffer * BUFFER_SIZE);
	uint8_t bit_state = (fram_read(addr) & _BV(y%8)) ? SET : CLEAR;
	return bit_state;
}

/* Clears a bit at position (x, y) in the buffer stored in FRAM.
 * This functions reads the current byte where the bit to be set is,
 * to make sure it does not clobber the existing bit values there. */
void buffer_clear_bit(uint8_t x, uint8_t y, uint8_t buffer) {
	uint8_t page = y/8;
	uint16_t addr = page*PAGE_WIDTH + x + (buffer * BUFFER_SIZE);
	uint8_t current_data = fram_read(addr);
	uint8_t data = (~_BV(y%8)) & current_data;
	fram_write(addr, data);
}

/* Set entire byte value at selected position */
void buffer_set_byte(uint8_t x, uint8_t page, uint8_t byte_val, uint8_t buffer)
{
	fram_write(page*PAGE_WIDTH + x + (buffer * BUFFER_SIZE), byte_val);
}

// Send all (NUM_PAGES) pages in the buffer to the LCD
void send_buffer_all(uint8_t buffer)
{
	uint8_t i;
	for(i = 0; i < NUM_PAGES; i++) {
		send_buffer_page(buffer);
	}
}

/* Send on page of the buffer to the LCD.
 * First reads in one entire page of data stored in the FRAM, then sends it on 
 * to the LCD. */
void send_buffer_page(uint8_t buffer) {
	uint8_t column;
	uint8_t page_data[NUM_COLUMNS];
	static uint8_t page = 0;
	
	// Get page data from FRAM
	for(column = 0; column < NUM_COLUMNS; column++) {
		page_data[column] = fram_read(page*PAGE_WIDTH + column + (buffer * BUFFER_SIZE));
	}
	
	// Write page data to the LCD
	lcd_set_page(page);	
	for(column = 0; column < NUM_COLUMNS; column++) {
		lcd_set_column(column);
		lcd_send_data(page_data[column]);
	}
	
	page++;
	if(page >= NUM_PAGES) {
		page = 0;
	}
}

// UNUSED
/*
void buffer_set_byte_xy(uint8_t x, uint8_t y, uint8_t byte_val, uint8_t buffer) {
	// Find what page the position (x, y) starts in
	uint8_t page = y/NUM_PAGES;
	uint8_t y_modulus = y%PAGE_HEIGHT;
	
	// If the position is aligned with the pages, write
	// directly to the fram
	if(y_modulus == 0) {
		fram_write(page*PAGE_WIDTH + x + (buffer * BUFFER_SIZE), byte_val);
		return;
	}
	
	// Else, it is not aligned, so find offset and the two bytes to write to
	uint16_t addr = page*PAGE_WIDTH + x + (buffer * BUFFER_SIZE);
	
	uint8_t data = (byte_val << y_modulus);
	fram_write(addr, data);
	
	// We want to write to the same column, but a page below.
	// We can just add the width of page to do this.
	addr = addr + PAGE_WIDTH;
	data = (byte_val >> (1-y_modulus));
	fram_write(addr, data);
}
*/