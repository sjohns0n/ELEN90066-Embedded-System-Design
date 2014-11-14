/*
 * ADC.h
 *
 * Created: 17/08/2014 12:43:23 PM
 *  Author: Samuel
 */ 

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

// AVCC Reference voltage(3.3V)
#define ADMUX_SETUP ( _BV(REFS0))

// 64 clock prescaler
#define ADCSRA_SETUP ( _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1))

#define ADC_MAX 1023

void adc_init(void);
uint16_t adc_read_channel(uint8_t channel);

#endif /* ADC_H_ */