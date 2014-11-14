/*
 * Snake.c
 *
 * Created: 18/08/2014 9:38:09 PM
 *  Author: Samuel Johnson
 */ 

#define F_CPU 8000000
#include <util/delay.h>

#include <stdlib.h> // For rand()
#include <avr/pgmspace.h>
#include <stdint.h>

#include "dialogs.h"
#include "defines.h"
#include "lcd.h"
#include "lcdbuffer.h"
#include "buttons.h"
#include "interrupts.h"
#include "battery.h"
#include "snake.h"
#include "Font/font.h"

static void snake_init(void);
static void snake_draw_to_buffer(int8_t x_vel, int8_t y_vel);
static void food_draw_to_buffer(void);
static void food_clear_from_buffer(void);
static void get_user_input(int8_t* x_vel, int8_t* y_vel);
static void draw_score_to_buffer(uint16_t score);
static void snake_update(int8_t x_vel, int8_t y_vel);
static void food_update(void);
static uint8_t snake_self_collision(void);
static uint8_t snake_boundary_collision(void);
static uint8_t snake_is_eating(void);

static uint8_t play_again_menu(void);

static void snake_draw_segment(uint8_t x, uint8_t y, uint8_t buffer);
static void snake_clear_segment(uint8_t x, uint8_t y, uint8_t buffer);
static void snake_draw_head(uint8_t x, uint8_t y, int8_t x_vel, int8_t y_vel, uint8_t buffer);
static void snake_clear_head(uint8_t x, uint8_t y, int8_t x_vel, int8_t y_vel, uint8_t buffer);

// Menu strings
const char score_text[] = "Score: ";
static uint8_t score_text_len = 7;

const char play_again_text[] = "Play again?";
static uint8_t play_again_text_len = 11;

const char choice_text[] = "A1 - Y / A2 - N";
static uint8_t choice_text_len = 15;

/* Could move some of these variables into the main Snake() function.
 * They would no longer be global, so they would have to be passed in to any function
 * using their contents.
 * Would reduce RAM use */
static uint8_t segments[SNAKE_MAX_LENGTH+1][4]; // Whole snake, including segments, head + new head co-ords
static uint8_t snake_length; // number of snake segments

// Food coordinates
static uint8_t food[2];

// Player score
static uint16_t score = 0;

// Velocity variables.
//  -1 left
//   0 no velocity
//   1 right
// Begin game moving to the right
static int8_t x_vel = 1,
			  y_vel = 0;

void snake() {
	/* Initialise snake position, player score and food */	
	buffer_clear(SNAKE_FRAME);
	snake_init(); // Place the snake at the starting position
	food_update(); // Place first piece of food
	snake_draw_to_buffer(x_vel, y_vel);
	food_draw_to_buffer();
	draw_score_to_buffer(score);
	send_buffer_all(SNAKE_FRAME);
	
	// New seed for food position
	// Reading the battery level should be random enough
	// Ideally use something that changes each runtime
	srand(get_battery_level());
	
	_delay_ms(SNAKE_START_DELAY_MS);
	
	uint8_t button_timer = 0;
	
	while(1) {
		if(button_timer) {
			get_user_input(&x_vel, &y_vel);
			
			// Check if the user wants to quit
			if(BUTTON_A2) {
				buffer_clear(SNAKE_FRAME);
				break;
			}
			button_timer = 0;
		}
		
		button_timer++;
				
		// Check if head is over a piece of food
		if(snake_is_eating()) {
			snake_length++;
			// Check length, restrict if necessary
			if(snake_length > SNAKE_MAX_LENGTH) {
				snake_length = SNAKE_MAX_LENGTH;
			}
			
			score += SCORE_INCREMENT;
			
			// Remove old food
			food_clear_from_buffer();
			
			// New food position
			food_update();
		}	

		snake_update(x_vel, y_vel);
		snake_draw_to_buffer(x_vel, y_vel);
		food_draw_to_buffer();
		draw_score_to_buffer(score);
				
		// Check if the snake has collided with itself or the game limits
		if(snake_self_collision() || snake_boundary_collision()) {
			lcd_invert_flash();
			
			if(play_again_menu()) {
				// Clear the screen and 
				// re-enter the main loop
				buffer_clear(SNAKE_FRAME);
				send_buffer_all(SNAKE_FRAME);
				snake_init();
				_delay_ms(SNAKE_RESTART_DELAY_MS);
			} else {
				break;
			}
		}
		
		send_buffer_all(SNAKE_FRAME);
		
		_delay_ms(SNAKE_DIFFICULTY_MS);
		
	}	
}

/* Get button input.
 * This functions reads in all button presses, but only changes the 
 * direction of the snake if it is a valid direction.
 * ie: if the snake is moving right, it can not instantly start moving left. */
static void get_user_input(int8_t* x_vel, int8_t* y_vel) {
	if(BUTTON_LEFT) {
		// If user inputs left
		// And current movement is up or down
		if(*y_vel > 0 || *y_vel < 0) {
			*y_vel = 0; // stop vertical movement
			*x_vel = MOVE_LEFT; // Start snake moving to the left
		}
	} else {
		if(BUTTON_RIGHT) {
			// If user inputs right
			// And current movement is up or down
			if(*y_vel > 0 || *y_vel < 0) {
				*y_vel = 0; // stop vertical movement
				*x_vel = MOVE_RIGHT; // Start snake moving right
			}
		}
	}
	
	if(BUTTON_DOWN) {
		// If user inputs down
		// And current movement is left or right
		if(*x_vel > 0 || *x_vel < 0) {
			*x_vel = 0; // stop horizontal movement
			*y_vel = MOVE_DOWN; // Start snake moving down
		}
	} else {
		if(BUTTON_UP) {
			// If user inputs up
			// And current movement is left or right
			if(*x_vel > 0 || *x_vel < 0) {
				*x_vel = 0; // stop horizontal movement
				*y_vel = MOVE_UP; // Start snake moving up
			}
		}
	}
}

// Start snake at center of screen, with tail trailing to the left
static void snake_init() {
	snake_length = STARTING_LENGTH;
	score = 0;
	x_vel = SNAKE_START_X_VELOCITY;
	y_vel = SNAKE_START_Y_VELOCITY;
	
	// Set initial position of head, define positions of next (length-1) segments
	uint8_t i;
	
	// Head starting position
	segments[HEAD][CURX] = SNAKE_START_X; // Previous x position
	segments[HEAD][CURY] = SNAKE_START_Y; // Previous y position
	
	// Set tail trailing to the left
	for(i = 1; i < snake_length; i++) {
		segments[i][CURX] = segments[HEAD][CURX] - (i*SNAKE_WIDTH);
		segments[i][CURY] = segments[HEAD][CURY];
	}
}

/* Update the position of all snake segments */
static void snake_update(int8_t x_vel, int8_t y_vel) {
	/* Each iteration, clear the bit at the last segments old position
	 * (before the update) */
	
	segments[HEAD][PREV_X] = segments[HEAD][CURX];
	segments[HEAD][PREV_Y] = segments[HEAD][CURY];
	snake_clear_head(segments[HEAD][CURX], segments[HEAD][CURY], x_vel, y_vel, SNAKE_FRAME);
	
	// Update head position with velocities
	segments[HEAD][CURX] += x_vel*SNAKE_WIDTH;
	segments[HEAD][CURY] += y_vel*SNAKE_WIDTH;
	
	// Clear end segment from the buffer as the snake will move
	snake_clear_segment(segments[snake_length-1][CURX], segments[snake_length-1][CURY], SNAKE_FRAME);
	
	// Update segment positions
	uint8_t i;
	for(i = 1; i < snake_length; i++) {
		
		// Store previous positions
		segments[i][PREV_X] = segments[i][CURX]; // Prev_x = current_x
		segments[i][PREV_Y] = segments[i][CURY]; // Prev_y = current_y

		// Get new segment position from old position of segment in front
		segments[i][CURX] = segments[i-1][PREV_X];
		segments[i][CURY] = segments[i-1][PREV_Y];
	}
}

// Referencing top left corner of image
static void snake_clear_segment(uint8_t x, uint8_t y, uint8_t buffer) {
	uint8_t i, j;
	
	for(i = 0; i < SNAKE_WIDTH; i++) {
		for(j = 0; j < SNAKE_WIDTH; j++) {
			if(i == 1 && j == 1) continue; // leave center pixel blank for contrast
			buffer_clear_bit(x+i, y+j, buffer);
		}
	}
}

// Referencing top left corner of image
static void snake_draw_segment(uint8_t x, uint8_t y, uint8_t buffer) {
	uint8_t i, j;
	
	for(i = 0; i < SNAKE_WIDTH; i++) {
		for(j = 0; j < SNAKE_WIDTH; j++) {
			if(i == 1 && j == 1) continue; // leave centre pixel blank for contrast
			buffer_set_bit(x+i, y+j, buffer);
		}
	}
}

/* Could use function pointers for the function pairs
 * draw_segment, clear_segment
 * draw_head, clear_head
 * pass in buffer_set_bit() or buffer_clear_bit() functions to
 * either draw or clear the segment/head */
static void snake_draw_head(uint8_t x, uint8_t y, int8_t x_vel, int8_t y_vel, uint8_t buffer) {
	// Common pixel is in the center
	buffer_set_bit(x+1, y+1, buffer);
	
	if(x_vel != 0) {
		switch(x_vel) {
			case MOVE_LEFT:
			buffer_set_bit(x+2, y, buffer);
			buffer_set_bit(x+2, y+1, buffer);
			buffer_set_bit(x+2, y+2, buffer);
			break;
			case MOVE_RIGHT:
			buffer_set_bit(x, y, buffer);
			buffer_set_bit(x, y+1, buffer);
			buffer_set_bit(x, y+2, buffer);
			break;
		}
		return;
	}
	
	switch(y_vel) {
		case MOVE_UP:
			buffer_set_bit(x, y+2, buffer);
			buffer_set_bit(x+1, y+2, buffer);
			buffer_set_bit(x+2, y+2, buffer);
			break;
		case MOVE_DOWN:
			buffer_set_bit(x, y, buffer);
			buffer_set_bit(x+1, y, buffer);
			buffer_set_bit(x+2, y, buffer);
			break;	
	}	
}

static void snake_clear_head(uint8_t x, uint8_t y, int8_t x_vel, int8_t y_vel, uint8_t buffer) {
	// Common pixel is in the center
	buffer_clear_bit(x+1, y+1, buffer);
	
	if(x_vel != 0) {
		switch(x_vel) {
			case MOVE_LEFT:
			buffer_clear_bit(x+2, y, buffer);
			buffer_clear_bit(x+2, y+1, buffer);
			buffer_clear_bit(x+2, y+2, buffer);
			break;
			case MOVE_RIGHT:
			buffer_clear_bit(x, y, buffer);
			buffer_clear_bit(x, y+1, buffer);
			buffer_clear_bit(x, y+2, buffer);
			break;
		}
		return;
	}
	
	switch(y_vel) {
		case MOVE_UP:
		buffer_clear_bit(x, y+2, buffer);
		buffer_clear_bit(x+1, y+2, buffer);
		buffer_clear_bit(x+2, y+2, buffer);
		break;
		case MOVE_DOWN:
		buffer_clear_bit(x, y, buffer);
		buffer_clear_bit(x+1, y, buffer);
		buffer_clear_bit(x+2, y, buffer);
		break;
	}
}

/* Returns TRUE if the snake has collided with the game walls */
static uint8_t snake_boundary_collision() {
	if(segments[HEAD][CURX] + SNAKE_WIDTH >= SNAKE_MAX_X) return TRUE;
	if(segments[HEAD][CURX] <= SNAKE_MIN_X) return TRUE;
	if(segments[HEAD][CURY] + SNAKE_WIDTH >= SNAKE_MAX_Y) return TRUE;
	if(segments[HEAD][CURY] <= SNAKE_MIN_Y) return TRUE;
	return FALSE;
}

// Check if the head collides with any of its own segments
static uint8_t snake_self_collision() {	
	// Head can't collide with 1st, 2nd segment or 3rd segment
	// can only overlap minimum of fourth segment
	uint8_t i;

	for(i = SNAKE_COLLIDE_MIN; i <= snake_length; i++) {
		if(segments[HEAD][CURX] == segments[i][CURX] &&
		   segments[HEAD][CURY] == segments[i][CURY]) {
			return TRUE;
		}
	}
	return FALSE;
}

/* Update the position of the food using random numbers */
static void food_update() {
	// rand() generates an integer in the range [0, RAND_MAX], where
	// RAND_MAX is defined in stdlib.h as 0x7FFF = 32767
	
	food[CURX] = rand()/FOOD_RAND_DIVISOR_X + FOOD_WIDTH;
	food[CURY] = rand()/FOOD_RAND_DIVISOR_Y + SCORE_TEXT_HEIGHT - FOOD_WIDTH;
	
	// Check display limits just in case
	if(food[CURX] < FOOD_MIN_X) food[CURX] = FOOD_MIN_X + FOOD_WIDTH;
	if(food[CURY] < FOOD_MIN_Y) food[CURY] = FOOD_MIN_Y + FOOD_WIDTH;
	if(food[CURX] >= FOOD_MAX_X) food[CURX] = FOOD_MAX_X - FOOD_WIDTH;
	if(food[CURY] >= FOOD_MAX_Y) food[CURY] = FOOD_MAX_Y - FOOD_WIDTH;
}

// Site below used to create the is_eating() function
// http://stackoverflow.com/questions/306316/determine-if-two-rectangles-overlap-each-other
// Check if the head of the snake is over a piece of food 
static uint8_t snake_is_eating() {
	/* Check if centers of the head block and the food block
	 * are within two pixels of each other. This implies that some
	 * portion of them are overlapping, constituting 'eating'. */
	if( segments[HEAD][CURX] < (food[CURX] + FOOD_WIDTH) &&
	   (segments[HEAD][CURX] + SNAKE_WIDTH) >= food[CURX] &&
	    segments[HEAD][CURY] < (food[CURY] + FOOD_WIDTH) &&
	   (segments[HEAD][CURY] + SNAKE_WIDTH) >= food[CURY] ) {
		return TRUE;	
		}
				
	return FALSE;	
}

// Reference top left corner of food
static void food_draw_to_buffer() {
	buffer_set_bit(food[CURX] + 1, food[CURY], SNAKE_FRAME);
	buffer_set_bit(food[CURX] + 1, food[CURY] + 1, SNAKE_FRAME);
	buffer_set_bit(food[CURX] + 1, food[CURY] + 2, SNAKE_FRAME);
	buffer_set_bit(food[CURX], food[CURY] + 1, SNAKE_FRAME);
	buffer_set_bit(food[CURX] + 2, food[CURY] + 1, SNAKE_FRAME);
}

static void food_clear_from_buffer() {
	buffer_clear_bit(food[CURX] + 1, food[CURY], SNAKE_FRAME);
	buffer_clear_bit(food[CURX] + 1, food[CURY] + 1, SNAKE_FRAME);
	buffer_clear_bit(food[CURX] + 1, food[CURY] + 2, SNAKE_FRAME);
	buffer_clear_bit(food[CURX], food[CURY] + 1, SNAKE_FRAME);
	buffer_clear_bit(food[CURX] + 2, food[CURY] + 1, SNAKE_FRAME);
}

// Draws the snake in the LCD buffer stored in FRAM
void snake_draw_to_buffer(int8_t x_vel, int8_t y_vel) {
	uint8_t i;

	// Draw head separately
	snake_draw_head(segments[HEAD][CURX], segments[HEAD][CURY], x_vel, y_vel, SNAKE_FRAME);

	// For each segment of the snake
	for(i = 1; i < snake_length; i++) {
		snake_draw_segment(segments[i][CURX], segments[i][CURY], SNAKE_FRAME);
	}
}

static void draw_score_to_buffer(uint16_t score) {
	uint8_t score_col = (SCREEN_WIDTH/2) - ((score_text_len + NUM_SCORE_DIGITS)*CHARACTER_WIDTH)/2;
	draw_string(score_col, PAGE_0, score_text, score_text_len, SNAKE_FRAME);
	draw_number(DIGITS_OFFSET*CHARACTER_WIDTH, PAGE_0, score, NUM_SCORE_DIGITS, SNAKE_FRAME);
}

/*
 Display a box containing
 'Score: <PlayerScore>'
 'Play again? A1-Y / A2-N'
 Define string for "Score: ",
 Define string for "Play again?",
 Define string for "A1-Y / A2-N",
*/
uint8_t play_again_menu(void) {	
	/* Prompt to play again */
	uint8_t prompt_col = (SCREEN_WIDTH/2) - (play_again_text_len*CHARACTER_WIDTH)/2;
	uint8_t select_col = (SCREEN_WIDTH/2) - (choice_text_len*CHARACTER_WIDTH)/2;
	draw_string(prompt_col, PAGE_2, play_again_text, play_again_text_len, SNAKE_FRAME); // play again prompt
	draw_string(select_col, PAGE_4, choice_text, choice_text_len, SNAKE_FRAME);
	send_buffer_all(SNAKE_FRAME);
	
	while(1) {
		// Get user input
		if(BUTTON_A1) {
			return TRUE;
		}
		
		if(BUTTON_A2) {
			return FALSE;
		}
	}
}