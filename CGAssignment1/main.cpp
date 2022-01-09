// main.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
#include "RasterSurface.h"
#include "Tiles/TownTiles/tiles_12.h"
#include "Tiles/para_CC0_particlefx-2/fire_01.h"

const unsigned int windowWidth = 500;
const unsigned int windowHeight = 500;

unsigned int windowArray[100000] = {0, };

const unsigned int* imgPointer = nullptr;


//•	A function to clear the color buffer to a solid color of your choice.
//•	A function to convert 2 dimensional coordinates to a 1 dimensional coordinate.
//•	A function to draw a pixel(fill a certain pixel with a specific color)
//•	A function to BLIT(Block Image Transfer)
//void clearColor() { }
//
//void coordConvert() {}
//
//void 


int main()
{
    RS_Initialize("Manmeet Singh", windowWidth, windowHeight);
	do {
		//const unsigned int* readline = image_pixels;
		//unsigned int* scanline = screen_array + screen_width * (screen_height - image_height) / 2;
		//scanline += (screen_width - image_width) / 2;
		unsigned int* pixel = windowArray;
		for (unsigned int y = 0; y < windowHeight; ++y) {
			for (unsigned int x = 0; x < windowWidth; ++x) {
				//*scanline++ = C2C(*readline);
				*pixel++ = 0xff4400;

			}
				//scanline += screen_width - image_width;
		}
	} 
	while (RS_Update(windowArray, sizeof(windowArray) >> 2));
    RS_Shutdown();
    return 0;
}