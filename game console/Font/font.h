/*
* Font.h
*
* Created: 22/08/2014 4:42:06 PM
*  Author: Samuel
*/

// Using characters from webpage generator:
// http://www.quinapalus.com/hd44780udg.html

// Multiple different sizes of character sets
// 7x5 could be used
// http://www.piclist.com/techref/datafile/charsets.htm

#ifndef FONT_H_
#define FONT_H_

#include <avr/pgmspace.h>

#define CHARACTER_WIDTH 6
#define NUM_CHARACTERS 256 // total ASCII characters

extern const char PROGMEM Font8x5[NUM_CHARACTERS][CHARACTER_WIDTH];

#endif /* FONT_H_ */