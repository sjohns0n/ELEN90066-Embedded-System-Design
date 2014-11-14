/*
 * Prints to console
 * Generates a wavetable for the signals:
 * sin
 * ramp
 * sawtooth (inverse ramp)
 * triangle
 * 
 * All values are positive
 * sin oscillates about 127
 * 
 * **Not tested for any other values than those below**
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void sinusoid(void);
void ramp(void);
void sawtooth(void);
void triangle(void);

#define NUM_SAMPLES 256
#define MAX_VALUE 255 //  = 2^8 - 1, maximum value that can be stored in an 8 bit register
#define ITEMS_PER_LINE 16
//#define PRINT_HEX

int
main(int argc, char **argv) {
	sinusoid();	printf("\n");
	ramp();     printf("\n");
	sawtooth(); printf("\n");
	triangle(); printf("\n");
	
	return 0;
}

void triangle(void) {
	int lineCount;
	double x;
	
	lineCount = 0;
	
	printf("uint8_t triangle[%d] = {\n\t", NUM_SAMPLES);
		for(x = 0; x <= MAX_VALUE; x+=2) {
			#ifdef PRINT_HEX
			printf("0x%02X", (int)x);
			#else
			printf("% 3d", (int)x);
			#endif
			
			lineCount++;
			if(lineCount != NUM_SAMPLES) printf(", ");
			if((lineCount % ITEMS_PER_LINE) == 0) printf("\n\t");
		}
		for(x = MAX_VALUE; x >= 0; x-=2) {
			#ifdef PRINT_HEX
			printf("0x%02X", (int)x);
			#else
			printf("% 3d", (int)x);
			#endif
			
			lineCount++;
			if(lineCount != NUM_SAMPLES) {
				printf(", ");
				if((lineCount % ITEMS_PER_LINE) == 0) printf("\n\t");
			}
		}
		
	printf("\n\r};\n");
}

void sawtooth(void) {
	int lineCount;
	double x;
	
	lineCount = 0;
	
	printf("uint8_t sawtooth[%d] = {\n\t", NUM_SAMPLES);
		for(x = MAX_VALUE; x >= 0; x--) {
			#ifdef PRINT_HEX
			printf("0x%02X", (int)x);
			#else
			printf("% 3d", (int)x);
			#endif
			
			lineCount++;
			if(lineCount != NUM_SAMPLES) {
				printf(", ");
				if((lineCount % ITEMS_PER_LINE) == 0) printf("\n\t");
			}
		}
		
	printf("\n\r};\n");
}

void ramp(void) {
	int lineCount;
	double x;
	
	lineCount = 0;
	
	printf("uint8_t ramp[%d] = {\n\t", NUM_SAMPLES);
	for(x = 0; x <= MAX_VALUE; x++) {
		#ifdef PRINT_HEX
		printf("0x%02X", (int)x);
		#else
		printf("% 3d", (int)x);
		#endif
				
		lineCount++;
		if(lineCount != NUM_SAMPLES) {
			printf(", ");
			if((lineCount % ITEMS_PER_LINE) == 0) printf("\n\t");
		}
	}
	
	printf("\n\r};\n");
}

void sinusoid(void) {
	int lineCount;
	double x;
		
	printf("uint8_t sinus[%d] = {\n\t", NUM_SAMPLES);
	lineCount = 0;
		
	//printf("1/samples = %f\n", (double)(1.0/numSamples));
	//exit(EXIT_FAILURE);
		
	for(x = 0; x < (2.0*M_PI) - (2.0*M_PI/NUM_SAMPLES); x += (2.0*M_PI/NUM_SAMPLES)) {
		#ifdef PRINT_HEX
		printf("0x%02X", (int)(sinus(x)*127+127));
		#else
		printf("% 3.0f", sinus(x)*127+127);
		#endif
		
	
		// Break to new line every ITEMS_PER_LINE items
		lineCount++;
		if(lineCount != NUM_SAMPLES) {
			printf(", ");
			if((lineCount % ITEMS_PER_LINE) == 0) printf("\n\t");
		}
	}
		
	printf("\n\r};\n"); // newline, carriage return, }, newline
	//printf("Linecount = %d\n", lineCount);
}




