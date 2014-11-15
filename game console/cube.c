/*
 * cube.c
 *
 * Created: 24/10/2014 8:04:13 PM
 *  Author: Samuel
 */ 

/* Using the tutorial on 3D shapes at Khan Academy:
 * https://www.khanacademy.org/computing/computer-programming/programming-games-visualizations/programming-3d-shapes/a/drawing-3d-shapes
 * 
 * Line drawing algorithm from the glcd library for Arduino:
 * http://playground.arduino.cc/Code/GLCDks0108
 * 
 * Downloads from
 * https://code.google.com/p/glcd-arduino/downloads/list
 */

#include "cube.h"

#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "lcdbuffer.h"

#define CUBE_FRAME FRAME0

#define NUM_NODES 8
#define NODE_ELEMENTS 3
#define NUM_EDGES 12
#define EDGE_ELEMENTS 2

#define X 0
#define Y 1
#define Z 2

static void draw_cube(void);
static void swap(uint8_t *a, uint8_t *b);
static void rotate_z(int16_t theta);

#define CUBE_OFFSET 35

// Need to center cube around an origin point
// This can't be zero, as the lcd only takes positive x, y, z values
// Nodes / vertices of the cube (x, y, z)
uint8_t nodes[NUM_NODES][NODE_ELEMENTS] = { {10+CUBE_OFFSET, 10+CUBE_OFFSET, 10+CUBE_OFFSET},
										  {10+CUBE_OFFSET, -10+CUBE_OFFSET, 10+CUBE_OFFSET},
										  {-10+CUBE_OFFSET, -10+CUBE_OFFSET, 10+CUBE_OFFSET},
										  {-10+CUBE_OFFSET, 10+CUBE_OFFSET, 10+CUBE_OFFSET},
										  {10+CUBE_OFFSET, 10+CUBE_OFFSET, -10+CUBE_OFFSET},
										  {10+CUBE_OFFSET, -10+CUBE_OFFSET, -10+CUBE_OFFSET},
										  {-10+CUBE_OFFSET, -10+CUBE_OFFSET, -10+CUBE_OFFSET},
										  {-10+CUBE_OFFSET, 10+CUBE_OFFSET, -10+CUBE_OFFSET}};
											  
// Connections between vertices to form a cube										  
uint8_t edges[NUM_EDGES][EDGE_ELEMENTS]	= { {0, 1},
											{1, 2},
											{2, 3},
											{3, 0},
											{4, 5},
											{5, 6},
											{6, 7},
											{7, 4},
											{4, 0},
											{5, 1},
											{6, 2},
											{7, 3} };


void cube() {
	static int r = 0;
	// Rotate vertices
	// First in one dimension
	if(r) {
	rotate_z(30);	
	r=0;
	} else {
		rotate_z(-30);
		r=1;
	}
	
	draw_cube();
	send_buffer_all(CUBE_FRAME);
}

/* Draw the cube to the buffer */
static void draw_cube() {
	uint8_t i;
	
	// Draw nodes
	for(i = 0; i < NUM_NODES; i++) {
		draw_point(nodes[i][X], nodes[i][Y]);
	}
	
	// Draw edges
	for(i = 0; i < NUM_EDGES; i++) {
		draw_line(nodes[edges[i][0]][X], nodes[edges[i][0]][Y], nodes[edges[i][1]][X], nodes[edges[i][1]][Y]);
	}
}

/* Rotate about the z axis. This means changing the x and y coordinates */
static void rotate_z(int16_t theta) {
	uint8_t x, y, i;
	for(i = 0; i < NUM_NODES; i++) {
		x = nodes[i][X];
		y = nodes[i][Y];
		
		nodes[i][X] = x*cos(theta) - y*sin(theta);
		nodes[i][Y] = y*cos(theta) + x*sin(theta);
	}
}

void draw_point(uint8_t x, uint8_t y) {
	buffer_set_bit(x, y, CUBE_FRAME);
	buffer_set_bit(x+1, y, CUBE_FRAME);
	buffer_set_bit(x, y+1, CUBE_FRAME);
	buffer_set_bit(x+1, y+1, CUBE_FRAME);
}

/* Draw a line between point (x1, y1) and (x2, y2) */
void draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
	// From GLCD Arduino Library, Michael Margolis and Bill Perry
	
	// The drawing algorithm only works reliably for gradients > 1
	uint8_t steep = abs(y1 - y2) > abs(x1 - x2);
	if(steep) {
		swap(&x1, &y1);
		swap(&x2, &y2);
	}
	
	// Draws reliably from left to right
	if(x1 > x2) {
		swap(&x1, &x2);
		swap(&y1, &y2);
	}
	
	uint8_t delta_x = x2 - x1;
	uint8_t delta_y = abs(y2 - y1);
	int8_t error = delta_x / 2;
	
	uint8_t x;
	uint8_t y = y1;
	int8_t y_step;
	
	if(y1 < y2) {
		y_step = 1;
	} else {
		y_step = -1;
	}
	
	for(x = x1; x <= x2; x++) {
		if(steep) {
			buffer_set_bit(y, x, CUBE_FRAME);
		} else {
			buffer_set_bit(x, y, CUBE_FRAME);
		}
		
		error -= delta_y;
		
		if(error < 0) {
			y += y_step;
			error += delta_x;
		}
	}
}

void swap(uint8_t *a, uint8_t *b) {
	uint8_t t = *a;
	*a = *b;
	*b = t;
}

						