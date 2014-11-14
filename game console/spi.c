/*
 * SPI.c
 *
 * Created: 17/08/2014 12:09:24 PM
 *  Author: Samuel
 */ 

#include <stdint.h>
#include "spi.h"

/* Initialises the SPI data and clock lines.
   The uC is set as the master, peripherals (RAM, LCD) are slaves */
void spi_init() {
		// SPI Clock and SPI MOSI as outputs
		// SPI MISO auto configured as input
		SPI_DIR_PORT |= _BV(SPI_CLK) | _BV(SPI_MOSI);
		
		// Set SS pin as output for proper Master operation
		SPI_DIR_PORT |= _BV(SPI_SS);
		
		SPCR |= _BV(SPE) | _BV(MSTR); // Enable SPI, Configure Atmega16 as Master,
		//SPCR |= _BV(SPR1) | _BV(SPR0); // Fosc / 128
				
		SPSR |= _BV(SPI2X); 		  // Double SCK frequency		
		
		// Setting correct SPI mode for test LCD communication
		// SPI mode 3
		SPCR |= _BV(CPOL) | _BV(CPHA);
}

/* Transmits one byte over SPI. */
uint8_t spi_transmit(uint8_t data) {
		// Writing to the SPDR register automatically starts transmission
		SPDR = data;
		
		// Wait for the transmission to complete.
		while(!(SPSR & _BV(SPIF)));
		
		return SPDR;
}