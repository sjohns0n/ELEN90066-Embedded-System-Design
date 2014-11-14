/*
* Buttons.c
*
* Created: 17/08/2014 12:58:36 PM
*  Author: Samuel
*/

#include <stdint.h>
#include "buttons.h"

// Configure button input port and pullup resistors
void buttons_init() {
	BUTTON_DIR_PORT &= ~(BUTTON_PINS_MASK); // All input pins except PIND2, which is the button interrupt input
	BUTTON_OUTPUT_PORT |= BUTTON_PINS_MASK; // Enable pullup resistors on all button pins
}