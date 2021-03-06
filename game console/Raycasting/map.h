/*
 * map.h
 *
 * Created: 26/09/2014 10:38:31 PM
 *  Author: Samuel
 */ 


#ifndef MAP_H_
#define MAP_H_

// From http://www.permadi.com/java/rayc/Rayc.java
#define MAP_WIDTH 12
#define MAP_HEIGHT 12

uint8_t map[MAP_WIDTH][MAP_HEIGHT] = 
{
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1 },
	{ 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1 },
	{ 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1 },
	{ 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1 },
	{ 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1 },
	{ 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1 },
	{ 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};							



#endif /* MAP_H_ */