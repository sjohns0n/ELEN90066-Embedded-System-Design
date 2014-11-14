/*
 * Sketch.h
 *
 * Created: 17/08/2014 1:57:50 PM
 *  Author: Samuel
 */ 

#ifndef SKETCH_H_
#define SKETCH_H_

#include "lcd.h"
#include "lcdbuffer.h"
#include <stdint.h>

#define SKETCH_FRAME FRAME1

#define SKETCH_UPDATE_DELAY_MS 8

#define SKETCH_START_X  SCREEN_WIDTH/2  // SCREEN_WIDTH defined in LCD.h
#define SKETCH_START_Y  SCREEN_HEIGHT/2 // SCREEN_HEIGHT defined in LCD.h
#define SKETCH_MIN_X    0
#define SKETCH_MAX_X    (SCREEN_WIDTH-1)
#define SKETCH_MIN_Y    0
#define SKETCH_MAX_Y    (SCREEN_HEIGHT-1)

void sketch(void);

extern volatile uint8_t send_buffer_page_flag;

#endif /* SKETCH_H_ */