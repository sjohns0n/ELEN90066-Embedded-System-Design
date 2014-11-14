/*
 * Sound.c
 *
 * Created: 8/09/2014 8:12:20 PM
 *  Author: Samuel
 */ 

/*
 *	See mega168 sound test for the idea for producing sound using PWM
 *	
 *	In main.c an 8-bit timer is used.
 *	Need a fast PWM signal to create a smooth audio output, so an 8-bit timer 
 *	is preferable.
 */	

#include "Sound.h"
#include "wavetable.h"

uint8_t ex() {
	return sinus[10];
}