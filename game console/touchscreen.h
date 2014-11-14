/*
 * Touchscreen.h
 *
 * Created: 15/09/2014 3:38:03 PM
 *  Author: Samuel
 */ 

#ifndef TOUCHSCREEN_H_
#define TOUCHSCREEN_H_

#include <stdint.h>
#include <avr/io.h>
#include "adc.h"

#define TOUCH_PORT	   PORTA
#define TOUCH_PORT_DIR DDRA

#define TOUCH_B PA4
#define TOUCH_L PA5
#define TOUCH_T PA6
#define TOUCH_R PA7

#define TOUCH_PINS_MASK ( _BV(TOUCH_B) | \
						  _BV(TOUCH_L) | \
						  _BV(TOUCH_T) | \
						  _BV(TOUCH_R) )
						  
// Values for mapping the 10-bit ADC value (0 - 1023) to an
// x (0 - 101) and
// y (0 - 63)
// co-ordinate on the LCD
#define X_MAP_VALUE (ADC_MAX/(SCREEN_WIDTH-1))
#define Y_MAP_VALUE (ADC_MAX/(SCREEN_HEIGHT-1))						  

void get_touch_coordinates(uint8_t *x, uint8_t *y);
void get_touch_coordinates_pots(uint8_t *x, uint8_t *y);

#endif /* TOUCHSCREEN_H_ */