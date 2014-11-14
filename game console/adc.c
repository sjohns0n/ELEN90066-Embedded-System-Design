/*
 * ADC.c
 *
 * Created: 17/08/2014 12:43:16 PM
 *  Author: Samuel
 */ 

#include "adc.h"
#include "touchscreen.h"
#include <avr/io.h>
#include <stdint.h>

/* Initialises analog input pins and the ADC control registers
 * Current setup is for  
 * 64 prescaler
 * 3.3V VCC reference */
void adc_init() {		
		DDRA &= ~(TOUCH_PINS_MASK); // All inputs as default
		
		// ADC setup
		ADMUX |= ADMUX_SETUP;
		ADCSRA |= ADCSRA_SETUP;
}

/* Takes one reading from the ADC and returns the 10-bit result. 
	The caller must first choose the desired channel by setting the
	appropriate MUX4:0 bits in the ADMUX register. */
uint16_t adc_read_channel(uint8_t channel) {
		uint16_t ADC_result;
		
		// Change input channel
		ADMUX = ADMUX_SETUP | channel;
		
		// Start conversion
		ADCSRA |= _BV(ADSC);
		
		// Wait for conversion to finish
		while(_BV(ADSC) & ADCSRA);
				
		// Get results (10 bit resolution because we can)
		ADC_result = ADCL | (ADCH<<8);
		
		return ADC_result;
}