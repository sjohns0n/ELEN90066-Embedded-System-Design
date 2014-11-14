/*
 * notes_random_code.c
 *
 * Created: 11/10/2014 11:44:21 PM
 *  Author: Samuel
 */ 

//uint8_t lcd_buffer[NUM_COLUMNS][NUM_PAGES];
//
//uint8_t i, j;
//for(i = 0; i < NUM_PAGES; i++) {
//for(j = 0; j < NUM_COLUMNS; j++) {
//lcd_buffer[j][i] = 0xFF;
//}
//}
//
// 


		//uint16_t addr = 0;
		//uint8_t val = 5;
		//uint8_t read_val;
		uint8_t x = 16;
		uint8_t y = 16;
		buffer_set_bit(x, y);
		send_buffer_page();
		
		_delay_ms(250);
		
		buffer_clear_bit(x, y);
		send_buffer_page();
		_delay_ms(250);
		
		// try reading the FRAM status register
		//fram_write_status_reg(_BV(2)); // set BP0
		//
		//uint8_t stat = fram_read_status_reg();
		//if(stat & _BV(2)) led_test_flash();
		
		/*
		//fram_enable_write();
		fram_write(addr, val);
		//fram_disable();
		
		//fram_enable_read();
		read_val = fram_read(addr);
		//fram_disable();		
		
		uint8_t i;
		for(i = 0; i < read_val; i++) {
			PORTC &= ~_BV(PC1);
			_delay_ms(100);
			PORTC |= _BV(PC1);
			_delay_ms(100);
		} */
		
		//if(read_val == 0) led_test_flash();
		//
		//if(read_val == write_val) {
			//led_test_flash();
		//}
		
		//_delay_ms(1000);
		
		
		
		
		
		/*
 * lcdbuffer.c
 *
 * Created: 13/10/2014 4:30:22 PM
 *  Author: Samuel
 */ 
/*
 * FUnctions for reading/writing the lcd buffer stored in FRAM */

#include <stdint.h>
#include "fram.h"
#include "lcd.h"
#include "lcdbuffer.h"

#define FRAM_BOTTOM 0x0000
#define FRAM_TOP	0x07FF // FOR 2Kbit FRAM (as in kit)

#define LCD_COL_MSB 0x01
#define LCD_COL_LSB 0x00

// Using two buffers for Conways Game of Life ('life.c')
#define LCD_BUFFER_0_START_ADDRESS 0x0000
#define LCD_BUFFER_0_STOP_ADDRESS 0x032F // 816 bytes from beginning

#define LCD_BUFFER_1_START_ADDRESS 0x0330
#define LCD_BUFFER_1_STOP_ADDRESS 0x0660 // 816 bytes from beginning

/* 
Have each buffer be an equal offset from each other

For multiple buffers
Add a parameter to each function so the user can choose which frame they want
to act on.
eg
#define BUFFER_SIZE 816 // 102 * 64 bits
#define LDC_BUFFERS_START_ADDR 0x0000

// clear all values in range buffer start address to buffer stop address
for buffer 0
start at 0
finish at 0 + BUFFER_SIZE

for buffer 1
start at BUFFER_SIZE
finish at BUFFER_SIZE + BUFFER_SIZE



void buffer_clear(uint8_t buffer_num) {
	uint8_t start_address = LCD_BUFFERS_START_ADDR + (buffer_num*BUFFER_SIZE);
	uint8_t end_address = LCD_BUFFERS_START_ADDR + ((buffer_num + 1)*BUFFER_SIZE);

	// strictly smaller than end_address
	for(addr = start_address; addr < end_address; addr++) {
		fram_write(addr, 0x00);
	}
}

void buffer_set_bit(uint8_t x, uint8_t y, uint8_t buffer_num) {
	uint8_t page = y/8;
	uint16_t addr = page*PAGE_WIDTH + x + (buffer_num * BUFFER_SIZE);
	uint8_t current_data = fram_read(addr);
	uint8_t data = _BV(y%8) | current_data;
	fram_write(addr, data);
}

uint8_t buffer_get_bit(uint8_t x, uint8_t y, uint8_t buffer_num) {
	uint16_t addr = (y/8)*PAGE_WIDTH + x + (buffer_num * BUFFER_SIZE);
	uint8_t state_byte = fram_read(addr);
	return (state_byte & _BV(y%8)); // return state of bit at offset position in byte
}



*/

#define BUFFER_SIZE 816
#define LCD_BUFFERS_START_ADDR 0x0000

// Initialise the buffer in FRAM.
void buffers_init(uint8_t buffer_num)
{
	uint16_t addr;
	uint16_t start_address = LCD_BUFFERS_START_ADDR + (buffer_num * BUFFER_SIZE);
	uint16_t end_address = LCD_BUFFERS_START_ADDR + ((buffer_num  + 1) * BUFFER_SIZE);
	
	// Set all values in buffer to zero (nothing to display)
	for(addr = start_address; addr <= end_address; addr++) {
		fram_write(addr, 0);
	}
}

// Set all bits in the LCD buffer to zero
void buffer_clear(uint8_t buffer)
{
	uint16_t addr;
	
	for(addr = LCD_BUFFER_0_START_ADDRESS; addr <= LCD_BUFFER_0_STOP_ADDRESS; addr++) {
		fram_write(addr, 0);
	}
}

/* Sets a bit at position (x, y) in the buffer stored in FRAM.
 * This functions reads the current byte where the bit to be set is,
 * to make sure it does not clobber the existing bit values there. */
void buffer_set_bit(uint8_t x, uint8_t y) {
	uint8_t page = y/8;
	uint16_t addr = page*PAGE_WIDTH + x;
	uint8_t current_data = fram_read(addr);
	uint8_t data = _BV(y%8) | current_data;
	fram_write(addr, data);
}

uint8_t buffer_get_bit(uint8_t x, uint8_t y, uint8_t buffer_num)
{
	uint16_t addr = (y/8)*PAGE_WIDTH + x;
	uint8_t state_byte = fram_read(addr);	
	return (state_byte & _BV(y%8)); // return state of bit at offset position in byte
}

void buffer_set_byte(uint8_t x, uint8_t page, uint8_t byte_val, uint8_t buffer)
{
	fram_write(page*PAGE_WIDTH + x, byte_val);
}

uint8_t buffer_get_byte(uint8_t column, uint8_t page, uint8_t buffer_num) {
	return fram_read(page*PAGE_WIDTH + column);
}

/* Clears a bit at position (x, y) in the buffer stored in FRAM.
 * This functions reads the current byte where the bit to be set is,
 * to make sure it does not clobber the existing bit values there. */
void buffer_clear_bit(uint8_t x, uint8_t y) {
	uint8_t page = y/8;
	uint16_t addr = page*PAGE_WIDTH + x;
	uint8_t current_data = fram_read(addr);
	uint8_t data = (~_BV(y%8)) & current_data;
	fram_write(addr, data);
}

// Send all (NUM_PAEGES) pages in the buffer to the LCD
void send_buffer_all(uint8_t buffer_num)
{
	uint8_t i;
	for(i = 0; i < NUM_PAGES; i++) {
		send_buffer_page();
	}
}

void send_buffer_page() {
	static uint8_t page = 0; // current page to send
	uint8_t column;
	uint8_t PAGE_DATA[PAGE_WIDTH];
	
	// Retrieve whole page data
	for(column = 0; column < PAGE_WIDTH; column++) {
		PAGE_DATA[column] = fram_read(page*PAGE_WIDTH + column);
	}
	
	lcd_send_command(LCD_PAGE_COMMAND | page);
	
	// Write whole Page to LCD
	for(column = 0; column < NUM_COLUMNS; column++) {
		// Set column to write to
		// Need to send two bytes for upper and lower nibbles of column address in SRAM
		// Due to display orientation, the column addresses are from 30..131 (+30 offset)
		lcd_send_command(LCD_COL_MSB | (((column + COLUMN_OFFSET) >> 4) & 0x0F)); //MSB
		lcd_send_command(LCD_COL_LSB | ((column + COLUMN_OFFSET) & 0x0F)); // LSB
				
		// Send data
		lcd_send_data(PAGE_DATA[column]);
	}
	
	page++;
	if(page >= NUM_PAGES) {
		page = 0;
	}
}





/**
 * \brief 
 * Gets UP, DOWN, LEFT and RIGHT button input.
 * Checks if the button pushed is a valid movement direction.
 * eg: If the snake if moving to the right, it cannot instantly start going left.
 *     This is an invalid move, so the function ignores that input
 * 
 * \param x_vel int8_t pointer to x velocity variable
 * \param y_vel int8_t pointer to y velocity variable
 * 
 * \return void
 */
static void get_user_input(int8_t* x_vel, int8_t* y_vel) {
	// Get input from user
	switch(x_movement) {
		case -1: // If user inputs left
			// And current movement is up or down
			if(*y_vel > 0 || *y_vel < 0) {
				*x_vel = -1; // Start snake moving to the left
			}
			break;
		case 1: // If user inputs right
			// And current movement is up or down
			if(y_movement > 0 || y_movement < 0) {
				*x_vel = 1; // Start snake moving right
			}
			break;
		default:
			*x_vel = *x_vel; // Else don't change current velocity
			break;
	}
	
	// Reset user input variable
	x_movement = 0;
	
	switch(y_movement) {
		case -1: // If user inputs down
			// And current movement is left or right
			if(x_movement > 0 || x_movement < 0) {
				*y_vel = -1; // Start snake moving down
			}
			break;
		case 1: // If user inputs up
			// And current movement is left or right
			if(x_movement > 0 || x_movement < 0) {
				*y_vel = 1; // Start snake moving up
			}
			break;
		default:
			*y_vel = *y_vel; // Else don't change current velocity
			break;
	}	
	
	// Reset user input variable
	y_movement = 0;
}

//------- FRAM BUFFER SNAKE ROUTINES -------//
/*
 * Variables for the snake can now be stored in the FRAM. This might not
 * be necessary as maximum snake size is 
 * MAX_LENGTH + 1 = 26 bytes for snake positions
 * + 2 bytes for food position
*/

#include "fram.h"

// Draw the snake to the buffer held in FRAM
static void snake_draw_to_fram() {
	uint8_t i;
	uint8_t page, offset, data;
	uint16_t addr;
	
	fram_enable_write();
	
	// For each segment of the snake
	for(i = 1; i < snake_length; i++) {
		page = segments[i][CURY] / NUM_PAGES; // Find which page the segment is in
		offset = segments[i][CURX];			  // Find offset from start of byte
		addr = page*PAGE_WIDTH + offset;      // Address to write in FRAM
		data = 1 << (segments[i][CURY] % 8);  // Data to write at address
		
		fram_write(addr, data);
	}
	
	fram_disable();
}

// Need to create a clear background (clear data)
void draw_score_to_buffer(uint16_t score)
{
	uint8_t i;

	for(i = 0; i < score_text_len; i++) {
		left_offset = (SCREEN_WIDTH - score_text_len)/2; // place text in approx middle of screen
		buffer_set_byte(1, 1, pgm_read_byte(&(Font8x5[(int)score_text[i]][i])), SNAKE_FRAME); // load character bytes into the buffer (1st page down)
	}
	/*
	for(i = 0; i < play_again_text_len; i++) {
		left_offset = (SCREEN_WIDTH - play_again_text_len)/2;
		LCD_Buffer[left_offset][2] = pgm_read_byte(&(Font8x5[(int)play_again_text[i]][i])); // (2nd page down)
	}
	for(i = 0; i < choice_text_len; i++) {
		left_offset = (SCREEN_WIDTH - choice_text_len)/2;
		LCD_Buffer[left_offset][3] = pgm_read_byte(&(Font8x5[(int)choice_text[i]][i])); // (3rd page down)
	}
	}*/
}

buffer_clear(FRAME0);
uint8_t k = 10;
while(1) {
	// testing area
	uint8_t i = 0;
	
	for(i = 0; i < 52; i++) {
		buffer_set_byte_xy(k, i, 0xFF, FRAME0);
		send_buffer_all(FRAME0);
		_delay_ms(100);
	}
	k++;
	
	
	
}