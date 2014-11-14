/*
 * Touch_Demo.c
 *
 * Created: 22/09/2014 10:20:55 AM
 *  Author: samuelj
 */ 

#include "touch_demo.h"
#include "touchscreen.h"
#include "fram.h"
#include "lcd.h"
#include "buttons.h"

// Example of using the touchscreen to interact with the console
// Draws a line where ever the user touches the screen
void touch_demo() {
	uint8_t x, y; // x and y co-ords of current touch point
	uint16_t addr; // address and data for FRAM
	uint8_t data;
	
	while(1) {
		// Check if the user wants to quit
		if(action2 == 1) {
			action2 = 0;
			break;
		}
		
		// Check if the user wants the clear the screen
		if(action1 == 1) {
			action1 = 0;
			lcd_buffer_clear();
		}
		
		get_touch_coordinates(&x, &y);
		
		// Convert touch points to an address and data in FRAM
		addr = y / NUM_PAGES;	  // first find what page the point lies in
		addr = addr * PAGE_WIDTH; // multiply by page width to find address in FRAM
		addr = addr + x;		  // add x offset into page
		data = y % 8;			  // find offset from start of byte in page for a single bit point
		
		// Draw a point on the screen at the touched coords
		fram_enable_write();
		fram_write(addr, data);
		fram_disable();		
	}	
}