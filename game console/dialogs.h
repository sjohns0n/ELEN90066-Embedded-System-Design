/*
 * dialogs.h
 *
 * Created: 19/10/2014 2:54:53 PM
 *  Author: Samuel
 */ 

#ifndef DIALOGS_H_
#define DIALOGS_H_

#include <stdint.h>
#include "lcdbuffer.h"

#define MENU_BUFFER FRAME0
#define ASCII_CHAR_OFFSET 48

#define SKETCH_GAME_SELECT 0
#define SNAKE_GAME_SELECT 1
#define LIFE_GAME_SELECT 2

#define NUM_MENU_ITEMS 3
#define TEXT_MAX_LENGTH 17

// Allow space on the left of the strings for a selection dot
#define MENU_STRINGS_COLUMN 20
#define MENU_START_PAGE 1

#define BUTTON_TIMER_COUNT 4

uint8_t game_menu(void);
void draw_string(uint8_t column, uint8_t page, const char* text, uint8_t text_length, uint8_t buffer);
void draw_number(uint8_t column, uint8_t page, uint32_t number, uint8_t num_digits, uint8_t buffer);

#endif /* DIALOGS_H_ */