/*
 * Snake.h
 *
 * Created: 18/08/2014 9:47:45 PM
 *  Author: Samuel Johnson
 */ 

#ifndef SNAKE_H_
#define SNAKE_H_

#include "lcd.h"

#define SNAKE_DIFFICULTY_MS 60

#define DIGITS_OFFSET 8
#define NUM_SCORE_DIGITS 6

// Only need one buffer for snake()
#define SNAKE_FRAME FRAME0
#define SCORE_TEXT_HEIGHT 7

#define SNAKE_START_DELAY_MS 1000
#define SNAKE_RESTART_DELAY_MS 1000

#define STARTING_LENGTH 4
#define SNAKE_MAX_LENGTH 125 // segments, including the head
// Max length impacts heavily on the RAM usage

#define SNAKE_START_X_VELOCITY 1
#define SNAKE_START_Y_VELOCITY 0

#define SNAKE_COLLIDE_MIN 5

#define SNAKE_WIDTH 3
#define FOOD_WIDTH 3

#define MOVE_UP -1
#define MOVE_DOWN 1
#define MOVE_LEFT -1
#define MOVE_RIGHT 1

#define SNAKE_MAX_X SCREEN_WIDTH
#define SNAKE_MIN_X 0
#define SNAKE_MAX_Y SCREEN_HEIGHT
#define SNAKE_MIN_Y SCORE_TEXT_HEIGHT

#define FOOD_MIN_X FOOD_WIDTH
#define FOOD_MAX_X (SCREEN_WIDTH - 1 - FOOD_WIDTH)
#define FOOD_MIN_Y (SCORE_TEXT_HEIGHT + FOOD_WIDTH)
#define FOOD_MAX_Y (SCREEN_HEIGHT - 1 - FOOD_WIDTH)

// RAND_MAX is defined in stdlib.h as 0x7FFF = 32767
#define FOOD_RAND_DIVISOR_X (RAND_MAX / (SCREEN_WIDTH-1)) // range [0, 101]
#define FOOD_RAND_DIVISOR_Y (RAND_MAX / (SCREEN_HEIGHT-1 - SCORE_TEXT_HEIGHT)) // range [0, 63 - SCORE_TEXT_HEIGHT]

// Start in the center of screen
#define SNAKE_START_X SCREEN_WIDTH/2
#define SNAKE_START_Y SCREEN_HEIGHT/2

/*  Variables stored in the segments array:
	segments[index][0] x
	segments[index][1] y
	segments[index][2] prev_x
	segments[index][3] prev_y
*/
// For indexing segments[][<>]
#define CURX 0
#define CURY 1
#define PREV_X 2
#define PREV_Y 3

#define HEAD 0 // For first 'head' segment in segments[]

#define SCORE_INCREMENT 1234

void snake(void);

#endif /* SNAKE_H_ */