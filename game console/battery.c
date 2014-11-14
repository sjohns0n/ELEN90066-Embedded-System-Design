/*
 * battery.c
 *
 * Created: 9/10/2014 4:00:20 PM
 *  Author: Samuel
 */ 

#include "battery.h"
#include "adc.h"

static void set_low_batt_led(void);
static void clear_low_batt_led(void);

/* Initialise the button input pins and the 
 * battery low LED output pin */
void battery_init() {
	// Setup output port for batt_low LED
	BATT_LOW_DIR_PORT |= _BV(BATT_LOW_LED_PIN);
	BATT_LOW_PORT |= _BV(BATT_LOW_LED_PIN);
}

// Returns the 10-bit analog reading of the battery level
uint16_t get_battery_level() {
	return adc_read_channel(BATTERY_SENSE_PIN);
}

/* Reads the battery level and alerts the user with an LED if it is
   below a set threshold. */
void check_battery_level() {
	// Get battery reading
	uint16_t battery_level = adc_read_channel(BATTERY_SENSE_PIN);
	
	// Check if battery level is lower than threshold
	if(battery_level < BATT_LOW_VOLTAGE_THRESHOLD) {
		// If it is, alert the user
		set_low_batt_led();
	} else {
		clear_low_batt_led();
	}
}

/* Low battery led ON */
static void set_low_batt_led() {
	BATT_LOW_PORT &= ~_BV(BATT_LOW_LED_PIN);
}

/* Low battery led OFF */
static void clear_low_batt_led() {
	BATT_LOW_PORT |= _BV(BATT_LOW_LED_PIN);
}