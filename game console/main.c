/*
 * Game_Console.c
 *
 * Created: 17/08/2014 11:14:51 AM
 *  Author: Samuel
 */ 

/*
 * This project uses font written by Philippe Lucidame.
 * It can be found at http://www.piclist.com/techref/datafile/charset/8x6.htm
 * Accessed 22/08/2014
 */ 

#define F_CPU 8000000
#include <util/delay.h>

volatile uint8_t send_buffer_page_flag = 0;

#include "lcd.h"
#include "lcdbuffer.h"
#include "spi.h"
#include "buttons.h"
#include "battery.h"
#include "defines.h"
#include "interrupts.h"
#include "fram.h"
#include "adc.h"
#include "dialogs.h"
#include "sketch.h"
#include "life.h"
#include "snake.h"

#include <avr/interrupt.h>

const char menu_select_error_str[] = "Select Error!";
const uint8_t menu_select_error_str_length = 13;

int main(void) {
	
	// Peripheral setup
	adc_init();
	spi_init();	
	lcd_init();
	lcd_screen_clear();
	fram_init();
	
	buttons_init();
	battery_init();
	
	setup_interrupts();
	sei();
	
    while(1) {
		// Game selection menu
		uint8_t game_selection = game_menu();
		switch(game_selection) {
			case SKETCH_GAME_SELECT:
				sketch();
				break;			
			case SNAKE_GAME_SELECT:
				snake();
				break;			
			case LIFE_GAME_SELECT:
				life();
				break;			
			default:
				draw_string(COLUMN_10, PAGE_3, menu_select_error_str, menu_select_error_str_length, FRAME0);
				break;
		}
    }	
}