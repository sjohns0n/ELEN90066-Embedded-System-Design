/*
 * Dialogs.c
 *
 * Created: 23/08/2014 7:32:46 PM
 *  Author: Samuel
 */ 

#include "dialogs.h"

#include "lcdbuffer.h"
#include "Font/font.h"
#include "buttons.h"
#include <avr/pgmspace.h>
#include <stdint.h>
#include <string.h>

// Draw tools for menu select function
static void clear_square(uint8_t x, uint8_t y, uint8_t buffer_num);
static void draw_square(uint8_t x, uint8_t y, uint8_t buffer_num);
static void draw4x4_square(uint8_t x, uint8_t y, uint8_t buffer_num);
static void clear4x4_square(uint8_t x, uint8_t y, uint8_t buffer_num);

/* Menu strings */
static const char sketch_game_string[] = "Sketch";
static const char snake_game_string[] = "Snake";
static const char life_game_string[] = "Game of Life";

/* Draw a strictly alphabetical string at position (column, page) to the frame buffer.
 * This function is currently limited to writing to pages only.\
 * Support for unique y values was not necessary for the function
 * of the project. */
void draw_string(uint8_t column, uint8_t page, const char* text, uint8_t text_length, uint8_t buffer) {
	uint8_t i, j;
	
	// For each character in the string
	for(i = 0; i < text_length; i++) {
		// For the width of each character
		for(j = 0; j < CHARACTER_WIDTH; j++) {
			// Write the character byte pattern to the buffer.
			buffer_set_byte((i*CHARACTER_WIDTH) + j + column, page, pgm_read_byte(&(Font8x5[(int)text[i]][j])), buffer);
		}
	}
}

/* Draws a strictly numeric string at position (column, page) to the frame buffer.
 * Currently only supports page height y poisitions. */
void draw_number(uint8_t column, uint8_t page, uint32_t number, uint8_t num_digits, uint8_t buffer) {
	uint8_t i, j;
	uint8_t digit;
	
	// For each digits in the number
	for(i = num_digits; i > 0; i--) {
		// Get the specific digit and find its index in the font array
		digit = number%10 + ASCII_CHAR_OFFSET;
		number /= 10;
		
		// Write character bytes to the buffer
		for(j = 0; j < CHARACTER_WIDTH; j++) {
			buffer_set_byte((i*CHARACTER_WIDTH) + j + column, page, pgm_read_byte(&(Font8x5[digit][j])), buffer);
		}
	}	
}	

/* Display a menu showing available games, allowing the user to select what to play */
uint8_t game_menu() {
	int8_t menu_item = SKETCH_GAME_SELECT;
	int8_t prev_menu_item = menu_item;
		
	uint8_t sketch_string_length = strlen(sketch_game_string);
	uint8_t snake_string_length = strlen(snake_game_string);
	uint8_t life_string_length = strlen(life_game_string);
	
	// Draw game list
	buffer_clear(MENU_BUFFER);
	draw_string(MENU_STRINGS_COLUMN, MENU_START_PAGE, sketch_game_string, sketch_string_length, MENU_BUFFER);
	draw_string(MENU_STRINGS_COLUMN, MENU_START_PAGE+1, snake_game_string, snake_string_length, MENU_BUFFER);
	draw_string(MENU_STRINGS_COLUMN, MENU_START_PAGE+2, life_game_string, life_string_length, MENU_BUFFER);
	draw4x4_square(MENU_STRINGS_COLUMN/2, (menu_item + 1) * PAGE_HEIGHT, MENU_BUFFER); // Start selection at sketch
	send_buffer_all(MENU_BUFFER);
		
	// Get input from the user
	uint8_t button_timer = 0;
	while(1) {
		if(button_timer > BUTTON_TIMER_COUNT) {
			// Input for moving up and down menu
			if(BUTTON_UP) menu_item--;
			if(BUTTON_DOWN) menu_item++;
			// Input for selected current game
			if(BUTTON_A1) break;
			button_timer = 0;
		}
		button_timer++;
		
		if(menu_item >= NUM_MENU_ITEMS) menu_item = 0;
		if(menu_item < 0) menu_item = NUM_MENU_ITEMS - 1;

		// Remove the previous square
		// Only need to clear if the menu selection has moved
		if(!(prev_menu_item == menu_item)) {
			clear4x4_square(MENU_STRINGS_COLUMN/2, (prev_menu_item + 1) * PAGE_HEIGHT, MENU_BUFFER);
			
			// Draw dot next to current menu item
			// Center of dot at game_strings_column/2
			draw4x4_square(MENU_STRINGS_COLUMN/2, (menu_item + 1) * PAGE_HEIGHT, MENU_BUFFER);
		}
		
		send_buffer_all(MENU_BUFFER);
		prev_menu_item = menu_item;
	}
	
	return menu_item;
}

/*----- MENU SELECT FUNCTIONS -----*/

static void draw4x4_square(uint8_t x, uint8_t y, uint8_t buffer_num) {
	draw_square(x, y+1, buffer_num);
	draw_square(x + 2, y+1, buffer_num);
	draw_square(x, y + 3, buffer_num);
	draw_square(x + 2, y + 3, buffer_num);
}

static void draw_square(uint8_t x, uint8_t y, uint8_t buffer_num) {
	buffer_set_bit(x, y, buffer_num);
	buffer_set_bit(x + 1, y, buffer_num);
	buffer_set_bit(x, y + 1, buffer_num);
	buffer_set_bit(x + 1, y + 1, buffer_num);
}

static void clear_square(uint8_t x, uint8_t y, uint8_t buffer_num) {
	buffer_clear_bit(x, y, buffer_num);
	buffer_clear_bit(x + 1, y, buffer_num);
	buffer_clear_bit(x, y + 1, buffer_num);
	buffer_clear_bit(x + 1, y + 1, buffer_num);
}

static void clear4x4_square(uint8_t x, uint8_t y, uint8_t buffer_num) {
	clear_square(x, y+1, buffer_num);
	clear_square(x + 2, y+1, buffer_num);
	clear_square(x, y + 3, buffer_num);
	clear_square(x + 2, y + 3, buffer_num);
}