/*Embedded System Design
 *Project sound test using an Atmega168
 *
 *Samuel Johnson
 *Friday  5/9/2014
 *
 *Using an 8-bit timer to create a PWM wave with varying duty cycle
 *A PORTB pin is manually set on compare match with OC1A, and
 *						cleared on overflow
 *The duty cycle of the PWM signal is from a sinusoid wavetable in wavetable.h
 *Frequency is found from the frequency of the wave and freq of the pin set interrupt routine
 *
 *An RC low pass filter provides a smoother output (at cost of attenuation)
 *R = 1k, C = 1u
 */

#include "wavetable.h"

#define F_CPU 16000000 // 16MHz crystal

#define OUTPUT PB1

#define SAMPLES 256
#define INDEX_INC 92
volatile uint8_t sin_index = 0; 
volatile uint8_t index_increment = 0;
volatile uint8_t amp_index = 0;
volatile uint8_t amplitude = 1;


#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>

//void interruptInit16bit(void);
void interruptInit8bit(void);
void adcInit(void);

int main() {
	interruptInit8bit();
	adcInit();
	
	sei();
	
	DDRB |= _BV(PB0) | _BV(OUTPUT);
	PORTB = 0;
	
	//OCR1AH = 0;
	//OCR1AL = 0xFF;
	// 
	OCR0A = 127;
	
	uint16_t Fwave;
	uint16_t Fint = 8333; // frequency of interrupt routine that updates index
	
	//index_increment = 123;
	
	while(1) {
		
		// Get frequency from ADC reading
		Fwave = ADCH; // range 0 - 1023*4
		
		// step through three frequencies
		// 1kHz
		//Fwave = 1000;
		index_increment = (1.0*Fwave/Fint)*SAMPLES;
		//
		//_delay_ms(500);
		//
		//// 2kHz
		//Fwave = 2000;
		//index_increment = (1.0*Fwave/Fint)*SAMPLES;
		//
		//_delay_ms(500);
		//
		//// 4kHz
		//Fwave = 4000;
		//index_increment = (1.0*Fwave/Fint)*SAMPLES;
		//
		//_delay_ms(500);
		
		
		//PORTB = 1;
		//_delay_ms(1000);
		//PORTB = 0;
		//_delay_ms(1000);
		
	}
	
		
	return 0;
}

void adcInit() {
	//ADMUX |= _BV(REFS0); // AVCC reference with cap at AREF pin
	ADMUX |= _BV(ADLAR); // left adjust result (only 8 bits needed)
	
	ADCSRA |= _BV(ADEN); // enable ADC
	ADCSRA |= _BV(ADATE); // auto trigger
	ADCSRA |= _BV(ADSC); // write one to start first converion
	ADCSRA |= _BV(ADPS2) | _BV(ADPS1); // 64 prescaler
}

void interruptInit8bit() {
	// OC0A disconnected
	
	// Fast PWM mode
	TCCR0A |= _BV(WGM01) | _BV(WGM00);
	
	// 8 prescaler Fint = 8333
	TCCR0B |= _BV(CS01);
	
	// No prescaling Fint = 62500
	//TCCR0B |= _BV(CS00);
	
	// output compare match A enable
	TIMSK0 |= _BV(OCIE0A);
	TIMSK0 |= _BV(OCIE0B); // B enable
	TIMSK0 |= _BV(TOV0); // overflow int enable
}

ISR(TIMER0_COMPA_vect) {
	PORTB |= _BV(OUTPUT);
}

ISR(TIMER0_COMPB_vect) {
	// Used to increment index
	sin_index = sin_index + index_increment;
}

ISR(TIMER0_OVF_vect) {
	PORTB &= ~_BV(OUTPUT);
	amplitude = pgm_read_byte(&ramp[amp_index]);
	OCR0A = (amplitude * pgm_read_byte(&sawtooth[sin_index]))%256;
}




/*
void interruptInit16bit() {
	// Fast PWM 10-bit
	//TCCR1A |= _BV(WGM11) | _BV(WGM10);
	//TCCR1B |= _BV(WGM12);
	
	// Fast PWM 8-bit
	TCCR1A |= _BV(WGM12) | _BV(WGM10);
	
	// Normal mode
	// No bits set
	
	// 1024 clock prescaler
	//TCCR1B |= _BV(CS12) | _BV(CS10);
	
	// 64 prescaler
	//TCCR1B |= _BV(CS11) | _BV(CS10);
	
	// 8 Prescaler
	TCCR1B |= _BV(CS11);
	
	// No prescaler
	//TCCR1B |= _BV(CS10);
		
	// Output compare A match enabled
	TIMSK1 |= _BV(OCIE1A);
	
	// Timer overflow interrupt enabled
	TIMSK1 |= _BV(TOIE1);
	
}

ISR(TIMER1_COMPA_vect) {
	// Set output pin
	PORTB |= _BV(OUTPUT);
}

ISR(TIMER1_OVF_vect) {
	// Clear pin
	PORTB &= ~_BV(OUTPUT);
}*/