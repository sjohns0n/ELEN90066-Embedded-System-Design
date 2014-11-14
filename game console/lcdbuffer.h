/*
 * lcdbuffer.h
 *
 * Created: 14/10/2014 12:50:18 PM
 *  Author: Samuel
 */ 


#ifndef LCDBUFFER_H_
#define LCDBUFFER_H_

#include <stdint.h>

#define FRAME0 0
#define FRAME1 1

#define BUFFER_SIZE 816

#define BUFFER_0_START_ADDR 0x0000
#define BUFFER_0_STOP_ADDR  0x032F

#define BUFFER_1_START_ADDR 0x0330
#define BUFFER_1_STOP_ADDR  0x065F

#define LCD_BUFFERS_START_ADDR 0x0000
#define LCD_BUFFERS_STOP_ADDR  0x065F

#define LCD_COL_MSB 0x10
#define LCD_COL_LSB 0x00

#define PAGE_HEIGHT 8

void buffers_init(void);
void buffer_clear(uint8_t buffer);
void buffer_set_bit(uint8_t x, uint8_t y, uint8_t buffer);
uint8_t buffer_get_bit(uint8_t x, uint8_t y, uint8_t buffer);
void buffer_clear_bit(uint8_t x, uint8_t y, uint8_t buffer);
void send_buffer_page(uint8_t buffer);
void send_buffer_all(uint8_t buffer);
void buffer_set_byte(uint8_t x, uint8_t page, uint8_t byte_val, uint8_t buffer);

// UNUSED
//void buffer_set_byte_xy(uint8_t x, uint8_t y, uint8_t byte_val, uint8_t buffer);

#endif /* LCDBUFFER_H_ */