/*
 * interrupts.h
 *
 * Created: 8/10/2014 8:30:51 PM
 *  Author: Samuel
 */ 

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include <stdint.h>

#define BATTERY_CHECK_COUNT 500 // approx once every second
#define BACKLIGHT_MAX_BRIGHTNESS 0
#define BACKLIGHT_MIN_BRIGHTNESS 255
#define LCD_BACKLIGHT_INCREMENT (BACKLIGHT_MIN_BRIGHTNESS/10)

#define BACKLIGHT_START_BRIGHTNESS 200

#define LCD_BACKLIGHT_PORT		PORTB
#define LCD_BACKLIGHT_PORT_DIR  DDRB
#define LCD_BACKLIGHT_PIN		PB3

extern volatile int8_t x_movement;
extern volatile int8_t y_movement;
extern volatile int8_t action1;
extern volatile int8_t action2;

extern volatile uint8_t send_buffer_page_flag;

void setup_interrupts(void);

#endif /* INTERRUPTS_H_ */