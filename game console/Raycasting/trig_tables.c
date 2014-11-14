/*
 * trig_tables.c
 *
 * Created: 26/09/2014 9:43:34 PM
 *  Author: Samuel
 */ 

/*
Creates loopup tables for sin, cos and tan. These can be stored in program memory
to save on RAM.

For ease of use the Raycasting file, the index for each table is the player_view_angle, which
is an angle in degrees from 0 to 359
So 360 elements per table

sin, cos and tan take and return arguments in radians, so precompute the tables to take and return degree arguments.


*/

int progmem = 1; // 1 for storing in PROGMEM

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define NUM_TRIG_ELEMENTS 720 // 360 degrees

#define ELEMENTS_PER_LINE 8
#define DECIMALS 4

#define DIVIDE_DEGREES 360

#define sin_name "fsin"
#define cos_name "fcos"
#define tan_name "ftan"

int
main(int argc, char **argv) {
	int i;
	
	printf("\n");
	printf("#define NUM_TRIG_ELEMENTS %d", NUM_TRIG_ELEMENTS);
	printf("\n\n");
	
	// SIN
	if(progmem) printf("PROGMEM ");
	printf("const float %s[NUM_TRIG_ELEMENTS] = {\n", sin_name);
	for(i = 0; i < NUM_TRIG_ELEMENTS; i++) {
		printf(" % 0.*lf", DECIMALS, sin(i*M_PI/DIVIDE_DEGREES));
		if(!(i == NUM_TRIG_ELEMENTS)) {
			printf(",");
		}
		if((i+1)%ELEMENTS_PER_LINE == 0) {
			printf("\n");
		}
	}	
	printf("};");
	
	printf("\n\n");
	
	// COS
	if(progmem) printf("PROGMEM ");
	printf("const float %s[NUM_TRIG_ELEMENTS] = {\n", cos_name);
		for(i = 0; i < NUM_TRIG_ELEMENTS; i++) {
			printf(" % 0.*lf", DECIMALS, cos(i*M_PI/DIVIDE_DEGREES));
			if(!(i == NUM_TRIG_ELEMENTS)) {
				printf(",");
			}
			if((i+1)%ELEMENTS_PER_LINE == 0) {
				printf("\n");
			}
		}
	printf("};");
	
	printf("\n\n");
	
	/*
	tan(x) returns tan of x, measured in radians
	*/
	
	double tan_val;
	// TAN
	if(progmem) printf("PROGMEM ");
	printf("const float %s[NUM_TRIG_ELEMENTS] = {\n", tan_name);
		for(i = 0; i < NUM_TRIG_ELEMENTS; i++) {
			tan_val = tan(i*M_PI/DIVIDE_DEGREES);
			if(tan_val > 999999) { // asymptotes
				tan_val = 1e6;
				printf(" %8.0lf", tan_val);
			} else {
				printf(" %8.*lf", DECIMALS, tan_val);
			}
			if(!(i == NUM_TRIG_ELEMENTS-1)) {
				printf(",");
			}
			
			if((i+1)%ELEMENTS_PER_LINE == 0) {
				printf("\n");
			}
			
		}
	printf("};");

	return 0;
}