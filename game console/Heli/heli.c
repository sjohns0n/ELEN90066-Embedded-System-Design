/*
 * Heli.c
 *
 * Created: 1/10/2014 11:07:53 AM
 *  Author: Samuel
 */
#define F_CPU 8000000
#include <util/delay.h>

#include <stdint.h>
#include "../Buttons.h"
#include "../FRAM.h"
#include "heli_image.h"

#include "../lcdbuffer.h"

#define HELI_START_X 32
#define HELI_START_Y 32

#define HELI_MOVEMENT_SPEED 2
#define GRAVITY 1

static void heli_draw_to_buffer(uint8_t x, uint8_t y);

void heli() {
	uint8_t heli_x = HELI_START_X, 
		    heli_y = HELI_START_Y;
		   
	int8_t y_vel = 0; // vertical velocity of helicopter	
	
	// Approximate elapsed time between frames.
	// A timer should be used to calculate a precise number (if available)
	uint8_t dt = 10;
	
	while(1) {
		// Get user input
		if(BUTTON_A2) {
			break; // quit
		}
		
		if(BUTTON_A1) {
			y_vel -= HELI_MOVEMENT_SPEED;
		}
		
		// Check collisions
		
		// Generate terrain
		// Scroll display
		// Draw to buffer
		heli_draw_to_buffer(heli_x, heli_y);
		
		// Update velocity and position
		y_vel += GRAVITY * dt;
		heli_y -= y_vel * dt;
		
		send_buffer_all(FRAME0);
		_delay_ms(100);
	}
}

static void heli_draw_to_buffer(uint8_t x, uint8_t y) {
	// Draw helicopter image at position (x, y)
	// This references the helicopter position and image from the TOP LEFT corner
	uint8_t image_col = 0;
	
	for(image_col = 0; image_col < HELI_WIDTH; image_col++) {
		buffer_set_byte_xy(x, y, heli_image[image_col], FRAME0);
	}
	
}