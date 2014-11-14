/*
* Raycasting.c
*
* tutorial at
* http://www.permadi.com/tutorial/raycast/index.html
*
* Created: 26/09/2014 8:27:24 PM
*  Author: Samuel
*/

/* TODO:
check ray_angle and player_view_angle bounds.
ie: make sure they don't go below 0 or above 359 degrees.
Could add a function add_angle(angle) that automatically checks this

Player input
when checking for wall intersections, make sure to limit checks to within the map size
*/

#include <stdint.h>
#include <math.h> // distPlayerToWall() sqrt() and abs()
#include <avr/pgmspace.h>

// Pre-computed sin, cos and tan lookup tables to increase speed of calculations
#include "trig_tables.h"
#include "map.h"

#include "../lcd.h"
#include "../lcdbuffer.h"
#include "../buttons.h"
#include "../fram.h"

#define FOV 60
#define FOV_2 30 // FOV/2

// d = (screen_width/2) / tan(FOV/2)  rounded down to nearest integer
#define PROJ_SCREEN_DIST 88

// deg = FOV / NUM_COLS
//     = 60 / 102
#define DEG_PER_COL 0.588f

#define GRID_SIZE 64

// projection screen width and height defined in LCD.h
#define PROJ_PLANE_WIDTH SCREEN_WIDTH
#define PROJ_PLANE_HEIGHT SCREEN_HEIGHT

#define PLAYER_START_X 64
#define PLAYER_START_Y 64

#define PLAYER_MOVEMENT_SPEED 5
#define PLAYER_ANGULAR_SPEED 5

inline static uint16_t distance_player_to_wall(uint16_t player_x,uint16_t player_y, uint16_t wall_x, uint16_t wall_y);
static uint8_t player_view_quadrant(uint16_t angle);
static uint8_t is_ray_facing_upwards(uint16_t ray_angle)

void rays() {
	uint16_t player_x = PLAYER_START_X,
			 player_y = PLAYER_START_Y;
	
	uint16_t player_view_angle = 0; // 0 -- 359 degrees
	
	uint16_t intercept_x, intercept_y;
	uint16_t grid_x, grid_y;
	uint16_t horiz_wall_distance, vert_wall_distance;
	
	// MAIN LOOP
	while(1) {
		// If both actions buttons are pushed, exit rays().
		if(action1 && action2) {
			break;
		}
		
		// Rotate to the right
		if(x_movement > 0) {
			player_view_angle += PLAYER_ANGULAR_SPEED;
		// Rotate to the left	
		} else if(x_movement < 0) {
			player_view_angle -= PLAYER_ANGULAR_SPEED;
		}
		x_movement = 0; // reset movement input
		
		// This switch() statement adds ~4k of program mem usage.
		// So do the if(), else if() blocks commented out below. Not sure why they cost so much space.
		if(y_movement != 0) {
			switch(player_view_quadrant(player_view_angle)) {
				case 1:
				case 4:
				player_x += PLAYER_MOVEMENT_SPEED * pgm_read_byte(&fcos[(int)(player_view_angle*2)]);
				break;
				
				case 2:
				case 3:
				player_x -= PLAYER_MOVEMENT_SPEED * pgm_read_byte(&fcos[(int)(player_view_angle*2)]);
				break;
			}
			
			player_y += y_movement * PLAYER_MOVEMENT_SPEED * pgm_read_byte(&fsin[(int)(player_view_angle*2)]);
		}
		/*
		uint8_t x_mult = 1, y_mult = 1;
		if(y_movement > 0) {
			y_movement = 0;
			if(player_view_angle <= 90) { // Quadrant 1
				x_mult = 1;
				y_mult = 1;
			} else if(player_view_angle > 90 && player_view_angle <= 180) { // Quadrant 2
				x_mult = -1;
				y_mult = 1;
			} else if(player_view_angle > 180 && player_view_angle <= 270) { // Quadrant 3
				x_mult = -1;
				y_mult = -1;
			} else { // Quadrant 4
				x_mult = 1;
				y_mult = -1;
			}
			playerX += x_mult * PLAYER_MOVEMENT_SPEED * pgm_read_byte(&fcos[(int)(player_view_angle*2)]);
			playerY += y_mult * PLAYER_MOVEMENT_SPEED * pgm_read_byte(&fsin[(int)(player_view_angle*2)]);
		}
		*/

		/*
		if(y_movement > 0) {
			y_movement = 0;
			// Check what quadrant the player is looking into
			if(player_view_angle <= 90) { // Quadrant 1
				playerX += PLAYER_MOVEMENT_SPEED * pgm_read_byte(&fcos[(int)(player_view_angle*2)]);
				playerY += PLAYER_MOVEMENT_SPEED * pgm_read_byte(&fsin[(int)(player_view_angle*2)]);
				} else if(player_view_angle > 90 && player_view_angle <= 180) { // Quadrant 2
				playerX -= PLAYER_MOVEMENT_SPEED * pgm_read_byte(&fcos[(int)(player_view_angle*2)]);
				playerY += PLAYER_MOVEMENT_SPEED * pgm_read_byte(&fsin[(int)(player_view_angle*2)]);
				} else if(player_view_angle > 180 && player_view_angle <= 270) { // Quadrant 3
				playerX -= PLAYER_MOVEMENT_SPEED * pgm_read_byte(&fcos[(int)(player_view_angle*2)]);
				playerY -= PLAYER_MOVEMENT_SPEED * pgm_read_byte(&fsin[(int)(player_view_angle*2)]);
				} else { // Quadrant 4
				playerX += PLAYER_MOVEMENT_SPEED * pgm_read_byte(&fcos[(int)(player_view_angle*2)]);
				playerY -= PLAYER_MOVEMENT_SPEED * pgm_read_byte(&fsin[(int)(player_view_angle*2)]);
			}
		}
*/
		// Start first ray at left column on projection screen
		float ray_angle = player_view_angle + FOV_2;
		if(ray_angle >= 360) {
			ray_angle = ray_angle - 360;
		}

		/* ----- START RAYTRACING ----- */

		// For each projections screen column, increment the ray angle by DEG_PER_COL
		uint8_t projection_column;		
		for(projection_column = 0; projection_column < PROJ_PLANE_WIDTH; projection_column++) {
			
			// cast a ray outwards
			// trace this ray until it hits a wall
			
			//----------- HORIZONTAL INTERSECTIONS -----------//
			// find first point of intersection with grid
			// if the ray is facing upwards
			if(is_ray_facing_upwards(ray_angle)) {
				// Check for walls in the above cell
				intercept_y = (player_y/GRID_SIZE) * GRID_SIZE - 1;
			} else {
				// Check for walls in the below cell
				intercept_y = (player_y/GRID_SIZE) * GRID_SIZE + GRID_SIZE;
			}
			
			intercept_x = player_x + (player_y - intercept_y) / pgm_read_byte(&ftan[(int)(ray_angle*2)]);
			
			uint8_t dx, dy;
			while(1) { // Loop until break on hit
				// find what grid point the intercept is on
				grid_x = intercept_x / GRID_SIZE;
				grid_y = intercept_y / GRID_SIZE;

				// Check if the ray has gone past the edges of the map
				if(grid_x >= MAP_WIDTH) {
					intercept_x = MAP_WIDTH*GRID_SIZE;
					break;
				}

				if(grid_y > MAP_HEIGHT) {
					intercept_y = MAP_HEIGHT*GRID_SIZE;
					break;
				}
				
				// Check this grid position for any walls
				if(map[grid_x][grid_y] == 1) {
					break; // Wall has been hit, can stop checking horizontals
				} else {
					// If no hit, continue tracing the ray outwards
				}
				
				// No hit, so we go to the next intersection point.
				dy = GRID_SIZE;
				dx = dy / pgm_read_byte(&ftan[(int)(ray_angle*2)]);
				
				// Next intersection point
				intercept_x += dx;
				intercept_y += dy;
			}
			
			// Find distance to wall
			horiz_wall_distance = distance_player_to_wall(player_x, player_y, intercept_x, intercept_y);
			
			//----------- VERTICAL INTERSECTIONS -----------//
			// find first point of intersection with grid
			// if the ray is facing right
			if(is_ray_facing_right(ray_angle)) {
				// Check for walls in the right cell
				intercept_x = (player_x/GRID_SIZE) * GRID_SIZE + GRID_SIZE;
			} else {
				// Check for walls in the left cell
				intercept_x = (player_x/GRID_SIZE) * GRID_SIZE - 1;
			}
			
			intercept_y = player_y + (intercept_x - player_x) * pgm_read_byte(&ftan[(int)(ray_angle*2)]);
			
			while(1) { // Loop until break on hit
				// find what grid point the intercept is on
				grid_x = intercept_x / GRID_SIZE;
				grid_y = intercept_y / GRID_SIZE;
				
				// Check this grid position for any walls
				if(map[grid_x][grid_y] == 1) {
					break; // Wall has been hit, can stop checking horizontals
				} else {
					// If no hit, continue tracing the ray outwards
				}
				
				// No hit, so we go to the next intersection point.
				dx = GRID_SIZE;
				dy = GRID_SIZE * pgm_read_byte(&ftan[(int)(ray_angle*2)]);
				
				// Next intersection point
				intercept_x += dx;
				intercept_y += dy;
			}
			
			// Compare distances to both intersections and choose the closest one.			
			vert_wall_distance = distance_player_to_wall(player_x, player_y, intercept_x, intercept_y);
			
			uint16_t wall_distance;
			if(vert_wall_distance >= horiz_wall_distance) {
				wall_distance = vert_wall_distance;
			} else {
				wall_distance = horiz_wall_distance;
			}
			
			// Eliminate 'fishbowl' effect
			// See http://www.permadi.com/tutorial/raycast/rayc8.html for more info
			wall_distance *= pgm_read_byte(&fcos[(int)(ray_angle*2)]);
			
			// Find projected wall height to draw to the buffer
			// Using a precomputed value: actual wall height * distance to projection plane
			//							  = 64 * 88
			//							  = 5632
			uint16_t proj_wall_height = 5632 / wall_distance;
			// Limit to size of display
			if(proj_wall_height > SCREEN_HEIGHT) proj_wall_height = SCREEN_HEIGHT;
			
			// Draw to the buffer
			uint64_t wall = (1 << (proj_wall_height-1)) - 1;
			uint8_t mask = 0xFF;
			uint16_t addr;
			int8_t page;
			uint8_t data;
			
			fram_enable_write();
			
			// Starting from center of projection screen, write masked bits to page bytes.
			for(page = NUM_PAGES/2; page >= 0; page--) {
				addr = page + projection_column;
				data = (wall >> (page*8)) & mask;
				fram_write(addr, data);
			}
			
			for(page = NUM_PAGES/2; page < NUM_PAGES; page++) {
				addr = page + projection_column;
				data = (wall >> (page*8)) & mask;
				fram_write(addr, data);
			}
			
			fram_disable();	
			
			ray_angle -= DEG_PER_COL; // Go to next column angle
			if(ray_angle < 0) {
				ray_angle = 360 + ray_angle;
			}
		}
	}
}

inline static uint16_t distance_player_to_wall(uint16_t player_x,uint16_t player_y, uint16_t wall_x, uint16_t wall_y) {
	uint16_t dx = fabs(wall_x - player_x);
	uint16_t dy = fabs(wall_y - player_y); 
	return (sqrt(dx*dx + dy*dy));
}

/*
// Method using trig lookup tables
inline static uint16_t distPlayerToWall(uint16_t ray_angle, uint16_t player_y, uint16_t wall_y) {
	uint16_t dy = abs(player_y - wall_y);
	return (dy / pgm_read_byte(&fsin[(int)(ray_angle*2)]));
}
*/

static uint8_t player_view_quadrant(uint16_t angle) {
	if(angle <= 90) { // Quadrant 1
		return 1;
	} else if(angle > 90 && angle <= 180) { // Quadrant 2
		return 2;
	} else if(angle > 180 && angle <= 270) { // Quadrant 3
		return 3;
	} else { // Quadrant 4
		return 4;
	}
}

static uint8_t is_ray_facing_upwards(uint16_t ray_angle) {
	if(ray_angle >= 0 && ray_angle <= 180) {
		return 1;
	} else {
		return 0;
	}
}

static uint8_t is_ray_facing_right(uint16_t ray_angle) {
	if(ray_angle >= 270 && ray_angle <= 90) {
		return 1;
	} else {
		return 0;
	}
}