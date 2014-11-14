/*
 * FRAM.c
 *
 * Created: 17/08/2014 12:51:33 PM
 *  Author: Samuel
 */ 

/*
 * Could improve usability of the FRAM read and write functions.
 * Instead of needing to call FRAM_Enable...() before each FRAM_Read/Write(), 
 * keep track of if the FRAM is already enabled to read or write using a local static variable.
 * This will allow other functions to simply call FRAM_Read/Write() without having to worry about
 * enabling it beforehand.
 *
 * The FRAM chip will also internally increment the address if you keep
 * giving it a clock. 
 * Is there a speed difference between sending an address every time, or checking the 
 * current address is sequential to the last one and not sending the address?
 */

#include <stdint.h>
#include "fram.h"
#include "spi.h"
#include "defines.h"

/* Initialize FRAM pins */
void fram_init() {
	FRAM_PORT_DIR |= FRAM_PINS_MASK;
	FRAM_PORT |= _BV(FRAM_WP); // disable writes to the status register
	FRAM_PORT |= _BV(FRAM_CS); // disable chip select at startup
	FRAM_PORT |= _BV(FRAM_HOLD); // don't hold any operations yet
}

/* Writes a single byte 'data' to 'address' in the FRAM. 
 * This function assumes the caller has already enabled the FRAM with
 * its Chip Select input, and also sent the WREN (Write Enable) opcode and WRITE opcode
 * This can be done by calling FRAM_Enable_Write() */
 void fram_write(uint16_t address, uint8_t data) {
	 fram_enable_write();
	 spi_transmit((address >> 8) & 0xFF);  // transfer upper byte
	 spi_transmit(address & 0xFF);		   // transfer lower byte
	 spi_transmit(data);
	 fram_disable();
 }

/* Reads and returns a single byte from 'address' in the FRAM. 
 * This function assumes the caller has already enabled the FRAM with
 * its Chip Select input
 * This can be done by calling FRAM_Enable_Read() */
uint8_t fram_read(uint16_t address) {
	fram_enable_read();
	spi_transmit((address >> 8) & 0xFF);
	spi_transmit(address & 0xFF);
	uint8_t data = spi_transmit(SPI_DUMMY);
	fram_disable();
	return data;
}

/* Sends appropriate opcode to enable writing to the FRAM */
void fram_enable_write() {
	// Chip select
	FRAM_PORT &= ~_BV(FRAM_CS);
	spi_transmit(FRAM_WREN_OPCODE); // WREN opcode to enable writing
	FRAM_PORT |= _BV(FRAM_CS); // Toggle chip select in between opcodes
	
	FRAM_PORT &= ~_BV(FRAM_CS);
	spi_transmit(FRAM_WRITE_OPCODE);
}

/* Sends appropriate opcode to enable reading from the FRAM */
void fram_enable_read() {
	// Enable chip select
	FRAM_PORT &= ~_BV(FRAM_CS);	
	spi_transmit(FRAM_READ_OPCODE);
}

void fram_disable() {
	// Disable chip select
	FRAM_PORT |= _BV(FRAM_CS);
}

/* Read status register in FRAM. This contains information
 * about block protection and write enable status. */
uint8_t fram_read_status_reg() {
	spi_transmit(FRAM_READ_STATUS_OPCODE);
	return spi_transmit(SPI_DUMMY);
}

/* The status register can be used to completely disable software
   from writing any data to the main FRAM memory. */
void fram_write_status_reg(uint8_t reg_value) {
	FRAM_PORT |= _BV(FRAM_WP);
	FRAM_PORT &= ~_BV(FRAM_CS);
	spi_transmit(FRAM_WREN_OPCODE);
	FRAM_PORT |= _BV(FRAM_CS);
	spi_transmit(FRAM_WRITE_STATUS_OPCODE);
	spi_transmit(reg_value);
	
	FRAM_PORT |= _BV(FRAM_CS);
	//FRAM_PORT &= ~_BV(FRAM_WP);
}

/* Clear data at every FRAM address */
void fram_clear_all() {
	uint16_t addr;
	for(addr = 0; addr < FRAM_MAX_ADDR; addr++) {
		fram_write(addr, CLEAR);
	}
}