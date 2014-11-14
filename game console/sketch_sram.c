/*
 * Sketch.c
 *
 * Created: 17/08/2014 1:56:52 PM
 *  Author: Samuel
 */ 

#include <stdint.h>
#include "sketch.h"
#include "lcd.h"
#include "interrupts.h"
#include "buttons.h"
#include "fram.h"

void
sketch() {
	uint8_t x, y, offset;
	uint8_t sketch_x, sketch_y;
	
	// Start drawing position in center of screen
	sketch_x = SKETCH_START_X;
	sketch_y = SKETCH_START_Y;
	lcd_buffer_clear(lcd_buffer);
	
	// Main Sketch loop
	while(1) {
		
		// Check if the user wants to quit
		if((~BUTTON_INPUT_PORT & _BV(BUTTON_A2_PIN))) {
			action2 = 0;
			lcd_buffer_clear(lcd_buffer);
			break;
		}
		
		// Check if the user wants to reset the drawing space
		if((~BUTTON_INPUT_PORT & _BV(BUTTON_A1_PIN))) {
			action1 = 0;
			lcd_buffer_clear(lcd_buffer);
			
			// Reset cursor position
			sketch_x = SKETCH_START_X;
			sketch_y = SKETCH_START_Y;
		}
		
		// Get input from button interrupt
		if(~BUTTON_INPUT_PORT & _BV(BUTTON_UP_PIN)) sketch_y -= 1;
		if(~BUTTON_INPUT_PORT & _BV(BUTTON_DOWN_PIN)) sketch_y += 1;
		if(~BUTTON_INPUT_PORT & _BV(BUTTON_LEFT_PIN)) sketch_x -= 1;
		if(~BUTTON_INPUT_PORT & _BV(BUTTON_RIGHT_PIN)) sketch_x += 1;
			
		// Reset movement vectors
		x_movement = 0;
		y_movement = 0;
		
		// Check display limits
		if(sketch_x >= SKETCH_MAX_X) sketch_x = SKETCH_MAX_X;
		if(sketch_x <= SKETCH_MIN_X+1) sketch_x = SKETCH_MIN_X+1;
		if(sketch_y >= SKETCH_MAX_Y) sketch_y = SKETCH_MAX_Y;
		if(sketch_y <= SKETCH_MIN_Y+1) sketch_y = SKETCH_MIN_Y+1;
		
		/* Use this block to allow wrap-around play
		Once the cursor goes past the far right edge of the screen, set its next position
		at left edge. Same for vertical movement; past top edge -> to bottom edge.
		if(sketch_x > SKETCH_MAX_X) sketch_x = SKETCH_MIN_X;
		if(sketch_x < SKETCH_MIN_X) sketch_x = SKETCH_MAX_X;
		if(sketch_y > SKETCH_MAX_Y) sketch_y = SKETCH_MIN_Y;
		if(sketch_y < SKETCH_MIN_Y) sketch_y = SKETCH_MAX_Y;
		*/
		
		// Translate sketch x and y positions into indexes for the buffer
		// sketch_x translates directly to the column
		x = sketch_x;
		
		// sketch_y needs some adapting
		y = sketch_y / 8; // first find what page it lies in
		offset = (sketch_y % 8); // then find offset from start of the page
							     // and place an active bit there
		
		// Update the buffer
		lcd_buffer[x][y] |= _BV(offset);
		lcd_send_buffer(lcd_buffer);
	}
}