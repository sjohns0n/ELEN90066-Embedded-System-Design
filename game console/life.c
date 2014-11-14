/*
 * life.c
 *
 * Created: 8/10/2014 9:38:15 PM
 *  Author: Samuel
 */ 

/*
 * Conway's Game of Life simulator
 * Implementing rules taken from
 * http://en.wikipedia.org/wiki/Conway's_Game_of_Life
 * http://en.wikipedia.org/wiki/Still_life_(cellular_automaton)
 */

#include "life.h"

#include <stdlib.h> // random functions
#include <stdint.h>
#include "fram.h"
#include "Font/font.h"
#include "lcd.h"
#include "battery.h"
#include "lcdbuffer.h"
#include "interrupts.h"
#include "buttons.h"
#include "dialogs.h"
#include "defines.h"

static inline uint8_t is_alive(uint8_t cell_value);
static uint8_t neighbours(uint8_t cell_x, uint8_t cell_y, uint8_t buffer);
static uint8_t get_cell_state(uint8_t column, uint8_t y, uint8_t buffer);
static uint8_t in_bounds(int8_t x, int8_t y);
static void set_cell_state(uint8_t column, uint8_t y, uint8_t state, uint8_t buffer);

// UNUSED
//static uint8_t is_steady_state(void);
//static void life_randomise(uint8_t buffer);

// Title strings
static const char generation_string[] = "Generation: ";
static void draw_generation_number(uint32_t generation, uint8_t buffer);

// Different interesting patterns from the Wikipedia page
// http://en.wikipedia.org/wiki/Conway's_Game_of_Life#Examples_of_patterns
static void draw_glider(uint8_t x, uint8_t y, uint8_t buffer_num);
static void draw_beacon(uint8_t x, uint8_t y, uint8_t buffer_num);
static void draw_lwss(uint8_t x, uint8_t y, uint8_t buffer_num); // lightweight spaceship
static void draw_toad(uint8_t x, uint8_t y, uint8_t buffer_num);
static void draw_square(uint8_t x, uint8_t y, uint8_t buffer_num);
static void draw_r_pentomino(uint8_t x, uint8_t y, uint8_t buffer_num); // unstable for >500 generations
static void draw_spark(uint8_t x, uint8_t y, uint8_t buffer_num);
//static void draw_gosper_gun(uint8_t x, uint8_t y, uint8_t buffer_num); // incomplete pattern

void life() {	
	uint8_t current_cell_state;
	//uint8_t is_steady_state_check = 0;
	
	// For correct life generation, read from current frame, write to next frame
	uint8_t current_frame = FRAME0;
	uint8_t next_frame = FRAME1;
	
	uint32_t generation = 0; // keep track of iterations

	buffer_clear(current_frame);
	buffer_clear(next_frame);
	
	// Draw start patterns
	draw_spark(1, 18, current_frame);
	draw_lwss(1, 30, current_frame);
	draw_beacon(20, 20, current_frame);
	draw_toad(5, 40, current_frame);
	draw_toad(10, 40, current_frame);
	draw_toad(15, 40, current_frame);
	draw_r_pentomino(10, 50, current_frame);
	
	// Array of gliders
	uint8_t i, j;
	for(i = 35; i < 80; i+=4) {
		for(j = 0; j < 50; j+=4) {
			draw_glider(i, j, current_frame);
		}
	}
	
	
	while(1) {
		// Check if the user wants to quit
		if(BUTTON_A2) {
			break;
		}
		
		draw_generation_number(generation, current_frame);
		send_buffer_all(current_frame);
		
		// For each cell, check how many neighbours it has, and
		// use that to find its state in the next frame.
		uint8_t x, y, number_neighbours;
		
		for (x = 0; x < SCREEN_WIDTH; x++) {
			for (y = GEN_STRING_HEIGHT; y < SCREEN_HEIGHT; y++) {
				current_cell_state = get_cell_state(x, y, current_frame);
				number_neighbours = neighbours(x, y, current_frame);
				
				// Decide what state the current cell will have in the next frame
				if(current_cell_state == DEAD) {
					if(number_neighbours == CELL_REPRODUCTION) {
						set_cell_state(x, y, ALIVE, next_frame);
					} else {
						set_cell_state(x, y, DEAD, next_frame);
					}
				} else { // else if state == ALIVE
					// death by under population or overcrowding
					if(number_neighbours < CELL_UNDERPOPULATION || number_neighbours > CELL_OVERPOPULATION) {
						set_cell_state(x, y, DEAD, next_frame);
					} else {
						set_cell_state(x, y, ALIVE, next_frame);
					}
				}
			}
		} // END FOR()
		
		// Update frames for next iteration
		uint8_t temp_frame = current_frame;
		current_frame = next_frame;
		next_frame = temp_frame;
		
		generation++;		

	} // END WHILE()
}

// Draw  the number of generations that have been simulated
static void  draw_generation_number(uint32_t generation, uint8_t buffer) {	
	draw_string(0, PAGE_0, generation_string, GENERATION_STRING_LENGTH, buffer);
	draw_number((GENERATION_STRING_LENGTH-1)*CHARACTER_WIDTH, 0, generation, GENERATION_NUMBER_OF_DIGITS, buffer);
}

/**
 * Returns how many active neighbours the cell at
 * position (cell_x, cell_y) has
 * 
 * \param cell_x: x position of cell
 * \param cell_y: y position of cell
 * 
 * \return uint8_t number of neighbours
 */
static uint8_t neighbours(uint8_t cell_x, uint8_t cell_y, uint8_t buffer)
{
	uint8_t num_neighbours = 0; // number of neighbours
	int8_t x, y;
	
	for(x = cell_x-1; x <= cell_x+1; x++) {
		for(y = cell_y-1; y <= cell_y+1; y++) {
			if(x == cell_x && y == cell_y) continue; // don't include the central cell
			if(in_bounds(x, y) && get_cell_state(x, y, buffer) == ALIVE)	 {
				num_neighbours++;
			}
		}
	}	
	
	return num_neighbours;
}

/* Returns TRUE if the given coordinate is a valid coordinate
 * on the game board */
static uint8_t in_bounds(int8_t x, int8_t y) {
	return ((x >= 0 && x < SCREEN_WIDTH) && (y >= 0 && y < SCREEN_HEIGHT));
}

/* Sets the cell value at (x, y) to 'state' in the buffer stored in FRAM. */
static void set_cell_state(uint8_t x, uint8_t y, uint8_t state, uint8_t buffer) {
	if(state == ALIVE) {
		buffer_set_bit(x, y, buffer);	
	} else {
		buffer_clear_bit(x, y, buffer);
	}
}

/* Returns the state of the cell at position (x, y) */
static uint8_t get_cell_state(uint8_t x, uint8_t y, uint8_t buffer) {
	if(is_alive(buffer_get_bit(x, y, buffer))) {
		return ALIVE;
	} else {
		return DEAD;
	}
}

/* Returns TRUE if the cell is alive, otherwise FALSE */
static uint8_t is_alive(uint8_t cell_value) {
	if(cell_value == ALIVE) { 
		return TRUE;
	} else {
		return FALSE;
	}
}

//----- PATTERNS -----//

// Period 2 oscillator
static void draw_beacon(uint8_t x, uint8_t y, uint8_t buffer_num) {
	draw_square(x, y, buffer_num);
	draw_square(x + 2, y + 2, buffer_num);
}

// Period 2 oscillator
static void draw_toad(uint8_t x, uint8_t y, uint8_t buffer_num) {
	buffer_set_bit(x + 1, y, buffer_num);
	buffer_set_bit(x + 2, y, buffer_num);
	buffer_set_bit(x + 3, y, buffer_num);
	
	buffer_set_bit(x, y + 1, buffer_num);
	buffer_set_bit(x + 1, y + 1, buffer_num);
	buffer_set_bit(x + 2, y + 1, buffer_num);
}

// Lightweight spaceship (moves left to right)
static void draw_lwss(uint8_t x, uint8_t y, uint8_t buffer_num) {
	buffer_set_bit(x, y, buffer_num);
	buffer_set_bit(x + 3, y, buffer_num);
	buffer_set_bit(x + 4, y + 1, buffer_num);
	buffer_set_bit(x, y + 2, buffer_num);
	buffer_set_bit(x + 4, y + 2, buffer_num);
	buffer_set_bit(x + 1, y + 3, buffer_num);
	buffer_set_bit(x + 2, y + 3, buffer_num);
	buffer_set_bit(x + 3, y + 3, buffer_num);
	buffer_set_bit(x + 4, y + 3, buffer_num);
}

// Simple spaceship (moves down to the right)
static void draw_glider(uint8_t x, uint8_t y, uint8_t buffer_num) {
	buffer_set_bit(x + 2, y, buffer_num);
	buffer_set_bit(x + 2, y + 1, buffer_num);
	buffer_set_bit(x + 2, y + 2, buffer_num);
	buffer_set_bit(x + 1, y + 2, buffer_num);
	buffer_set_bit(x, y + 1, buffer_num);
}

// Draw still life sqaure
static void draw_square(uint8_t x, uint8_t y, uint8_t buffer_num) {
	buffer_set_bit(x, y, buffer_num);
	buffer_set_bit(x + 1, y, buffer_num);
	buffer_set_bit(x, y + 1, buffer_num);
	buffer_set_bit(x + 1, y + 1, buffer_num);	
}

// Unstable group of cells
static void draw_r_pentomino(uint8_t x, uint8_t y, uint8_t buffer_num) {
	buffer_set_bit(x + 1, y, buffer_num);
	buffer_set_bit(x + 2, y, buffer_num);
	buffer_set_bit(x, y + 1, buffer_num);
	buffer_set_bit(x + 1, y + 1, buffer_num);
	buffer_set_bit(x + 1, y + 2, buffer_num);
}

/*
// Incomplete
static void draw_gosper_gun(uint8_t x, uint8_t y, uint8_t buffer_num) {
	draw_square(x, y + 4, buffer_num);
	
	draw_square(x + 34, y + 2, buffer_num);	
}
}*/

// Period 5 oscillator
static void draw_spark(uint8_t x, uint8_t y, uint8_t buffer_num) {
	buffer_set_bit(x+3, y, buffer_num);
	buffer_set_bit(x+4, y, buffer_num);
	buffer_set_bit(x+1, y+1, buffer_num);
	buffer_set_bit(x+6, y+1, buffer_num);
	buffer_set_bit(x+1, y+2, buffer_num);
	buffer_set_bit(x+6, y+2, buffer_num);
	buffer_set_bit(x+1, y+3, buffer_num);
	buffer_set_bit(x+6, y+3, buffer_num);
	buffer_set_bit(x+2, y+4, buffer_num);
	buffer_set_bit(x+5, y+4, buffer_num);
	buffer_set_bit(x, y+5, buffer_num);
	buffer_set_bit(x+2, y+5, buffer_num);
	buffer_set_bit(x+5, y+5, buffer_num);
	buffer_set_bit(x+7, y+5, buffer_num);
	buffer_set_bit(x, y+6, buffer_num);
	buffer_set_bit(x+1, y+6, buffer_num);
	buffer_set_bit(x+6, y+6, buffer_num);
	buffer_set_bit(x+7, y+6, buffer_num);	
}

/*
// UNUSED
// Check if the game board has reached steady state
static uint8_t is_steady_state() {
	// need to store at least one buffer iteration to compare against <--
	// could just wait for the user to reset the field.
	uint8_t x, y;
	
	// store an iteration of the game board
	for(x = 0; x < SCREEN_WIDTH; x++) {
		for(y = 0; y < SCREEN_HEIGHT; y++) {
			if(get_cell_state(x, y, FRAME0) != get_cell_state(x, y, FRAME1)) { // check state of cell in each frame
				return FALSE;
			}
		}
	}
	return TRUE;
}
*/


/* Initialises the game frame with random bits */
/*
static void life_randomise(uint8_t buffer) {
	uint8_t x, y, state;
	
	// New seed for random numbers
	srand(get_battery_level());

	for(x = 0; x < SCREEN_WIDTH; x++) {
		for(y = 0; y < SCREEN_HEIGHT; y++) {
			state = (rand() < RAND_MAX/RAND_SET_PROB) ? ALIVE : DEAD; // 1 in RAND_SET_PROB chance of setting the bit
			set_cell_state(x, y, state, buffer);
		}
	}
}
*/