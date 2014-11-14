/*
 * Buttons.h
 *
 * Created: 17/08/2014 12:58:43 PM
 *  Author: Samuel
 */ 

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include <avr/io.h>

// Button ports
#define BUTTON_DIR_PORT    DDRD
#define BUTTON_OUTPUT_PORT PORTD
#define BUTTON_INPUT_PORT  PIND

// Button input pins
#define BUTTON_UP_PIN   PD7
#define BUTTON_LEFT_PIN  PD6
#define BUTTON_DOWN_PIN  PD5
#define BUTTON_RIGHT_PIN PD4
#define BUTTON_A1_PIN    PD3
#define BUTTON_A2_PIN    PD1
#define BUTTON_BL_PIN    PD0

// Mask for button pins
#define BUTTON_PINS_MASK (_BV(BUTTON_UP_PIN) |    \
							_BV(BUTTON_LEFT_PIN) |  \
							_BV(BUTTON_DOWN_PIN) |  \
							_BV(BUTTON_RIGHT_PIN) | \
							_BV(BUTTON_A1_PIN) |    \
							_BV(BUTTON_A2_PIN) |    \
							_BV(BUTTON_BL_PIN))

// Button input macros
#define BUTTON_UP (~BUTTON_INPUT_PORT & _BV(BUTTON_UP_PIN))
#define BUTTON_LEFT (~BUTTON_INPUT_PORT & _BV(BUTTON_LEFT_PIN))
#define BUTTON_DOWN (~BUTTON_INPUT_PORT & _BV(BUTTON_DOWN_PIN))
#define BUTTON_RIGHT (~BUTTON_INPUT_PORT & _BV(BUTTON_RIGHT_PIN))
#define BUTTON_A1 (~BUTTON_INPUT_PORT & _BV(BUTTON_A1_PIN))
#define BUTTON_A2 (~BUTTON_INPUT_PORT & _BV(BUTTON_A2_PIN))
#define BUTTON_BL (~BUTTON_INPUT_PORT & _BV(BUTTON_BL_PIN))

void buttons_init(void);

#endif /* BUTTONS_H_ */