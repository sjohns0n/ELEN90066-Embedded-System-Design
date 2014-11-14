/*
 * Sketch.c
 *
 * Created: 17/08/2014 1:56:52 PM
 *  Author: Samuel
 */ 

#define F_CPU 8000000
#include <util/delay.h>

#include <stdint.h>
#include "sketch.h"
#include "fram.h"
#include "lcd.h"
#include "lcdbuffer.h"
#include "buttons.h"
#include "interrupts.h"
#include "touchscreen.h"
#include "dialogs.h"
#include "defines.h"

void
sketch() {
	// Start drawing position in center of screen
	uint8_t sketch_x = SKETCH_START_X;
	uint8_t sketch_y = SKETCH_START_Y;
	
	uint8_t button_timer = 0;
	uint8_t potentiometer_input = FALSE;
	
	// Main Sketch loop
	while(1) {
		// Check if the user wants to quit
		if(BUTTON_A2) {
			buffer_clear(SKETCH_FRAME);
			break;
		}
		
		// Check if the user wants to reset the drawing space
		if(BUTTON_A1) {
			buffer_clear(SKETCH_FRAME);
			
			// Reset cursor position
			sketch_x = SKETCH_START_X;
			sketch_y = SKETCH_START_Y;
		}
		
		// Switch input mode
		if(BUTTON_UP && BUTTON_A1) {
			if(potentiometer_input) {
				potentiometer_input = FALSE;
				draw_string(0, 0, "B", 1, SKETCH_FRAME);
				_delay_ms(200);
			} else {
				potentiometer_input = TRUE;
				draw_string(0, 0, "P", 1, SKETCH_FRAME);
				_delay_ms(200);
			}
		}
		
		// Get user input
		if(potentiometer_input) {
			get_touch_coordinates_pots(&sketch_x, &sketch_y);
		} else {
			if(button_timer > BUTTON_TIMER_COUNT) {				
				// Get input from button interrupt
				if(BUTTON_UP) sketch_y -= 1;
				if(BUTTON_DOWN) sketch_y += 1;
				if(BUTTON_LEFT) sketch_x -= 1;
				if(BUTTON_RIGHT) sketch_x += 1;
				
				button_timer = 0;
			}			
			button_timer++;
		}
		
		// Check display limits
		if(sketch_x >= SKETCH_MAX_X) sketch_x = SKETCH_MAX_X;
		if(sketch_x <= SKETCH_MIN_X+1) sketch_x = SKETCH_MIN_X+1;
		if(sketch_y >= SKETCH_MAX_Y) sketch_y = SKETCH_MAX_Y;
		if(sketch_y <= SKETCH_MIN_Y+1) sketch_y = SKETCH_MIN_Y+1;
		
		/* Use this block to allow wrap-around play
		Once the cursor goes past the far right edge of the screen, set its next position
		at left edge. Same for vertical movement; past top edge -> to bottom edge.
		if(sketch_x > SKETCH_MAX_X) sketch_x = SKETCH_MIN_X;
		if(sketch_x <= SKETCH_MIN_X) sketch_x = SKETCH_MAX_X;
		if(sketch_y > SKETCH_MAX_Y) sketch_y = SKETCH_MIN_Y;
		if(sketch_y <= SKETCH_MIN_Y) sketch_y = SKETCH_MAX_Y;
		*/
		
		// Set modified bit in FRAM LCD buffer
		buffer_set_bit(sketch_x, sketch_y, SKETCH_FRAME);
		_delay_ms(SKETCH_UPDATE_DELAY_MS);
		
		// DEBUG
		//draw_number(50, 0, sketch_x, 3, SKETCH_FRAME);
		//draw_number(50, 1, sketch_y, 3, SKETCH_FRAME);
		
		send_buffer_page(SKETCH_FRAME);
	} // End Main Sketch loop
}