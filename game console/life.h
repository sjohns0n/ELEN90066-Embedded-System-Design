/*
 * life.h
 *
 * Created: 8/10/2014 11:03:26 PM
 *  Author: Samuel
 */ 


#ifndef LIFE_H_
#define LIFE_H_

// Cell states
#define ALIVE 1
#define DEAD 0

#define STEADY_STATE_CHECK_COUNT 10

// 1 in RAND_SET_PROB chance of setting the bit
#define RAND_SET_PROB 10

// Neighbor numbers
#define CELL_REPRODUCTION 3
#define CELL_UNDERPOPULATION 2
#define CELL_OVERPOPULATION 3

// text height
#define GEN_STRING_HEIGHT 8
#define GENERATION_STRING_LENGTH 12
#define GENERATION_NUMBER_OF_DIGITS 4

void life(void);

#endif /* LIFE_H_ */