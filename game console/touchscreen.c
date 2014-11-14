/*
 * Touchscreen.c
 *
 * Created: 15/09/2014 3:33:33 PM
 *  Author: Samuel
 */ 

#include "touchscreen.h"
#include "adc.h"
#include "lcd.h"
#include <stdint.h>

/**
 * Reads position of touch point on touchscreen
 * 
 * \param x uint8_t pointer to x coordinate variable
 * \param y uint8_t pointer to y coordinate variable
 * 
 * \return void
 */
void get_touch_coordinates(uint8_t *x, uint8_t *y) {
	uint16_t adc_result;
	
	//---- X Coordinate ----//
	// Drive LEFT->RIGHT, read TOP or BOTTOM
	TOUCH_PORT_DIR |= _BV(TOUCH_L) | _BV(TOUCH_R);		// Set LEFT and RIGHT as outputs
	TOUCH_PORT |= _BV(TOUCH_L);  						// Drive LEFT pin, sink into RIGHT pin.
	adc_result = adc_read_channel(TOUCH_T);						// Read TOP value from ADC
	*x = adc_result/X_MAP_VALUE;						// Convert result to pixel value
	TOUCH_PORT &= ~_BV(TOUCH_L);						// Turn off LEFT pin
	TOUCH_PORT_DIR &= ~(_BV(TOUCH_L) | _BV(TOUCH_R));   // Reset LEFT and RIGHT as inputs
	
	//---- Y Coordinate ----//
	// Drive TOP->BOTTOM, read LEFT or RIGHT
	TOUCH_PORT_DIR |= _BV(TOUCH_T) | _BV(TOUCH_B);		// Set TOP and BOTTOM as outputs
	TOUCH_PORT |= _BV(TOUCH_T);  						// Drive TOP pin, sink into BOTTOM pin.
	adc_result = adc_read_channel(TOUCH_L);						// Read LEFT value from ADC
	*y = adc_result/Y_MAP_VALUE;						// Convert result to pixel value
	TOUCH_PORT &= ~_BV(TOUCH_T);						// Turn off TOP pin
	TOUCH_PORT_DIR &= ~(_BV(TOUCH_T) | _BV(TOUCH_B));   // Reset TOP and BOTTOM as inputs
}

/* For demonstrating the use of variable resistors as an input method.
 * This modifies variables x and y according to analog inputs.
 * It applies correct scaling to map the 
 * analog readings [0, 1023] to screen position [0, 101] and [0, 63] */
void get_touch_coordinates_pots(uint8_t *x, uint8_t *y) {
	//---- X Coordinate ----//
	*x = adc_read_channel(TOUCH_B) / X_MAP_VALUE;

	//---- Y Coordinate ----//
	*y = adc_read_channel(TOUCH_R) / Y_MAP_VALUE;
}