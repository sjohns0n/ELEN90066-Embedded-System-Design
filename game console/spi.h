/*
 * SPI.h
 *
 * Created: 17/08/2014 12:11:56 PM
 *  Author: Samuel
 */ 

#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>
#include <avr/io.h>

#define SPI_PORT	 PORTB
#define SPI_DIR_PORT DDRB
#define SPI_CLK		 PB7
#define SPI_MISO	 PB6
#define SPI_MOSI	 PB5
#define SPI_SS		 PB4

void spi_init(void);
uint8_t spi_transmit(uint8_t data);
uint8_t spi_transmit_receive(uint8_t data);

#endif /* SPI_H_ */