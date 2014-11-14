/*
 * battery.h
 *
 * Created: 9/10/2014 4:01:34 PM
 *  Author: Samuel
 */ 

#ifndef BATTERY_H_
#define BATTERY_H_

#include <avr/io.h>
#include <stdint.h>

// Voltage -> ADC reading value with 3.3V ref.
// 1.5V -> 466
// 1.1V -> 342
#define BATT_LOW_PORT			   PORTC
#define BATT_LOW_DIR_PORT		   DDRC
#define BATT_LOW_LED_PIN 	 	   PC1
#define BATT_LOW_VOLTAGE_THRESHOLD 342

// Pin battery voltage is connected to
#define BATTERY_SENSE_PIN PA0

void battery_init(void);
void check_battery_level(void);
uint16_t get_battery_level(void);

#endif /* BATTERY_H_ */