/*
 * interrupts.c
 *
 * Created: 8/10/2014 8:13:49 PM
 *  Author: Samuel
 */ 

#include "interrupts.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "buttons.h"
#include "lcd.h"
#include "lcdbuffer.h"
#include "battery.h"

static void buttons_interrupt_init(void);
static void lcd_backlight_timer_init(void);
static void lcd_update_timer_init(void);

// Initialise button variables
volatile int8_t x_movement = 0;
volatile int8_t y_movement = 0;
volatile int8_t action1 = 0;
volatile int8_t action2 = 0;

void setup_interrupts() {
	buttons_interrupt_init();
	lcd_backlight_timer_init();
	lcd_update_timer_init();
}

/*---------- INTERRUPT SETUP FUNCTIONS ----------*/

/*
 * For buttons, what is the point of the interrupt?
 * If we end up polling them for input anyway, why
 * watch for an interrupt?
 */ 
static void buttons_interrupt_init(void) {
	// Enable interrupt requests to be generated by INT0
	GICR  |= _BV(INT0);
	
	// The rising edge of INT0 will trigger an interrupt
	MCUCR |= _BV(ISC00) | _BV(ISC01);
}

// Timer/Counter0 used for controlling the backlight brightness using PWM
static void lcd_backlight_timer_init(void) {
	LCD_BACKLIGHT_PORT_DIR |= _BV(LCD_BACKLIGHT_PIN);   // Output pin
	TCCR0 |= _BV(WGM01) | _BV(WGM00);					// Fast PWM mode
	TCCR0 |= _BV(COM01) | _BV(COM00);					// Set OC0 on compare match, clear OC0 at BOTTOM
	//TCCR0 |= _BV(CS02) | _BV(CS00);						// 1024 clock prescaling, ~30Hz update
	//TCCR0 |= _BV(CS02);								// 256 clock prescaling,  ~122Hz update (see below)
	TCCR0 |= _BV(CS01) | _BV(CS00);					// 64 clock prescaling, ~500Hz update
	
	TIMSK |= _BV(OCIE0); // Enable interrupt.
	// This interrupt is used for checking the battery voltage
	
	/* 
	Using 1024 clock prescaling, this interrupt will operate at a frequency
		f_clk / (N * 256), where N = prescaler (page78)
		= 30.5Hz
		
		Using 256 prescaling,
		= 122Hz
	*/
	
	// Start backlight brightness at 0% completely OFF
	OCR0 = BACKLIGHT_START_BRIGHTNESS;
	
	// Might need to use phase correct mode, page77 a spike may occur when OCR0 = BOTTOM
	// Or try setting OCR0 = 126, so it is never 0 (also change comparison in button ISR)
}

// Timer/Counter2 used for controlling the refresh rate of the LCD
// 
static void lcd_update_timer_init(void) {
	// Clears timer when counter == OCR2
	TCCR2 |= _BV(WGM21) | _BV(WGM20); // Clear Timer on Compare Match (CTC)
	TCCR2 |= _BV(CS22) | _BV(CS21) | _BV(CS20); // 1024 prescaler
	TIMSK |= _BV(OCIE2); // Compare Match interrupt enable
	
	OCR2 = 255;
	
	/* Using 1024 prescaling:
	f = 30Hz
	OCR2 = 4MHz / (1024*30) - 1
		 = 130
	
	f = 60Hz
	OCR2 = 4MHz / (1024*60) - 1
		 = 65
	CTC = Clear Timer on Compare
	In CTC mode, the formula below gives the relationship between the
	PWM frequency and the counter value
	f_clk / (2 * N * (1+OCRn)), where N = prescaler (page124) */
	//OCR2 = 3906/(1+REFRESH_RATE)
}

/*---------- INTERRUPT SERVICE ROUTINES ----------*/

// LCD update interrupt
// Might need to move the call of LCD_update() out of an interrupt call

ISR(TIMER2_COMP_vect) {
	//send_buffer_page();
	//send_buffer_page_flag = 1;
}

// Button interrupt routine
ISR(INT0_vect) {
	// Input buttons have default state HIGH
	// When pressed they will register LOW
	// Read button states (1 in active_buttons indicates button is pressed)
	// Get button states from the input port
	uint8_t active_buttons = ~BUTTON_INPUT_PORT;
	
	// x_movement += 1  adding one movement bit for holding the button down. might be too much
	// Might need to add some 'debouncing', so that if the user holds the button down long enough to
	// trigger multiple interrupts,
	
	// Set corresponding button variables
	//if(active_buttons & _BV(BUTTON_UP))    y_movement = -1;
	//if(active_buttons & _BV(BUTTON_DOWN))  y_movement = 1;
	//if(active_buttons & _BV(BUTTON_LEFT))  x_movement = -1;
	//if(active_buttons & _BV(BUTTON_RIGHT)) x_movement = 1;
	//if(active_buttons & _BV(BUTTON_A1))    action1 = 1;
	//if(active_buttons & _BV(BUTTON_A2))    action2 = 1;
	
	// Backlight control
	if(active_buttons & _BV(BUTTON_BL_PIN)) {
		// If backlight is OFF, turn it back ON
		if(OCR0 >= BACKLIGHT_MIN_BRIGHTNESS) {
			OCR0 = BACKLIGHT_MAX_BRIGHTNESS;
		} else {
			if(OCR0 == 225) {
				OCR0 = BACKLIGHT_MIN_BRIGHTNESS; // completely OFF
			} else {
				OCR0 += LCD_BACKLIGHT_INCREMENT;
			}
			// Add backlight increment because setting OC0 at OCR0
			// and clearing OC0 at BOTTOM.
			// A larger value for OCR0 will mean less time 'on' (smaller duty cycle).
		}
	}
}

// Overflow interrupt
// Currently (22/9) set at a 30Hz interrupt rate. With battery_check_counter threshold at 30,
// the battery level will be read approx. every 1 second.
ISR(TIMER0_COMP_vect) {
	static volatile uint16_t battery_check_counter = 0;
	
	// Depending on calling frequency, change threshold for level check freq.
	if(battery_check_counter > BATTERY_CHECK_COUNT) {
		check_battery_level();
		battery_check_counter = 0;
	}
	battery_check_counter++;
}