/*
 * FRAM.h
 *
 * Created: 17/08/2014 12:51:26 PM
 *  Author: Samuel
 */ 

#ifndef FRAM_H_
#define FRAM_H_

#include <avr/io.h>
#include <stdint.h>

/* Holding FRAM_WP HIGH will prevent any write operations to
 * the status register */

/* FRAM control pins */
#define FRAM_PORT     PORTB
#define FRAM_PORT_DIR DDRB
#define FRAM_CS 	  PB2
#define FRAM_WP		  PB1
#define FRAM_HOLD 	  PB0

#define FRAM_PINS_MASK (_BV(FRAM_CS) | \
						_BV(FRAM_WP) | \
						_BV(FRAM_HOLD))

/* Opcodes for interfacing with the FRAM */						
#define FRAM_WRITE_OPCODE 0x02
#define FRAM_WREN_OPCODE  0x06
#define FRAM_READ_OPCODE  0x03
#define FRAM_READ_STATUS_OPCODE 0x05
#define FRAM_WRITE_STATUS_OPCODE 0x01
#define SPI_DUMMY 0xFF
#define FRAM_MAX_ADDR 0x7FF						
								
void fram_init(void);
uint8_t fram_read(uint16_t address);
void fram_write(uint16_t address, uint8_t data);
uint8_t fram_read_status_reg(void);
void fram_write_status_reg(uint8_t reg_value);

void fram_enable_write(void);
void fram_enable_read(void);
void fram_disable(void);

void fram_clear_all(void);

#endif /* FRAM_H_ */