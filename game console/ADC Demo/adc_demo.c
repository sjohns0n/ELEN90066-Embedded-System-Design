/*
 * ADC_demo.c
 *
 * Created: 8/09/2014 9:07:01 PM
 *  Author: Samuel
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

void adc_init(void);
void pwm_timer_init(void);

volatile uint16_t ADC_result;

int main() {
	
	adc_init();
	pwm_timer_init();
	
	// MAIN LOOP
	while(1) {
		// Get result
		// 8 bit
		//ADC_result = ADCH;
		
		// 10-bit ADCL must be read first (p220)
		ADC_result = ADCL;
		ADC_result |= ADCH << 8;
		
		// Do something with the result
		// eg: control brightness of backlight using PWM (pin PB3)
		OCR0 = ADC_result / 4;		
		
	} // MAIN LOOP
	
}

void pwm_timer_init() {
	TCCR0 |= _BV(WGM01) | _BV(WGM00); // Fast PWM
	TCCR0 |= _BV(COM01) | _BV(COM00); // Clear on Compare Match
									  // A higher value in OCR0 = longer ON time
	TCCR0 |= _BV(CS02);	// 256 Clock prescaler		
						// This gives a PWM frequency of ~122Hz
	OCR0 = 0; // Initialise compare register at zero						
}

// Initialise the Analog to Digital Converter
void adc_init() {
	// Internal 2.56V Vref
	//ADMUX |= _BV(REFS1) | _BV(REFS0);
	
	// AVCC, internal Vref turned off
	ADMUX |= _BV(REFS0);
	
	// Enable left adjust for 8 bit values
	//ADMUX |= _BV(ADLAR);
	
	// Input channel, default channel ADC0
	
	// Enable the ADC
	ADCSRA |= _BV(ADEN);
	
	// Enable Auto-triggering. This will allow the ADC 
	// to constantly provide conversion results
	ADCSRA |= _BV(ADATE);
	
	// Enable interrupt for ADC Conversion Complete
	//ADCSRA |= _BV(ADIE);
	
	// Clock prescaler for ADC
	ADCSRA |= _BV(ADPS0); // 2 
	//ADCSRA |= _BV(ADPS2); // 16 
	//ADCSRA |= _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0); // 128 
	
}

// Interrupt routine for ADC Conversion Complete flag
ISR(ADC_vect) {
	// Get result
	// 8 bit
	//ADC_result = ADCH;
	
	// 10-bit ADCL must be read first (p220)
	ADC_result = ADCL;
	ADC_result |= ADCH << 8;
}