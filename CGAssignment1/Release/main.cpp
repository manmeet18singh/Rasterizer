// main.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
#include <random>
#include <cassert>
#include "RasterSurface.h"
#include "Tiles/TownTiles/tiles_12.h"
#include "Tiles/para_CC0_particlefx-2/fire_01.h"

const unsigned int windowWidth = 500;
const unsigned int windowHeight = 500;
unsigned int windowArray[windowWidth * windowHeight] = {0, };

const unsigned int* spritePointer = tiles_12_pixels;
const unsigned int spriteWidth = tiles_12_width;
const unsigned int spriteHeight = tiles_12_height;

//•	A function to clear the color buffer to a solid color of your choice.
//•	A function to convert 2 dimensional coordinates to a 1 dimensional coordinate.
//•	A function to draw a pixel(fill a certain pixel with a specific color)
//•	A function to BLIT(Block Image Transfer)

#define C2C(c) (((c&65280u)<<0x8u)|((c&4278190080u)>>0x18u)|((c&255u)<<0x18u)|((c&16711680u)>>0x08u))   

void clearScreen(unsigned int color) { 
	unsigned int* pixel = windowArray;
	for (unsigned int y = 0; y < windowHeight; ++y) {
		for (unsigned int x = 0; x < windowWidth; ++x) {
			*pixel++ = color;
		}
	}
}

int coordConvert(int x, int y, int width) {
	return (y * width + x);
}


void drawPixel(int x, int y, int pixelToDraw) {
	windowArray[y * windowWidth + x] = pixelToDraw;
}


void drawSubRectangle(int offsetX, int offsetY, int subRectWidth, int subRectHeight, int windowX, int windowY) {
	const unsigned int* readline = spritePointer;
	for (int y = 0; y < subRectHeight; ++y) {
		for (int x = 0; x < subRectWidth; ++x, ++readline) {
			readline = spritePointer + ((offsetY + y) * tiles_12_width + (offsetX + x));
			drawPixel(windowX + x, windowY + y, C2C(*readline));
		}
	}
}

void drawBG() {
	for (unsigned int y = 0; y < windowHeight; y++) {
		for (unsigned int x = 0; x < windowWidth; x++) {
			//Grass Tiles are 36x36
			if (x % 36 == 0 && y % 36 == 0) {
				drawSubRectangle(286, 126, 36, 36, x, y);
			}
		}
	}
}

void drawRand() {
	int x;
	int y;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			std::random_device device;
			std::mt19937 rng(device());
			std::uniform_int_distribution<std::mt19937::result_type> dist6(1, windowWidth);
			x = dist6(rng);
		}
		std::random_device device;
		std::mt19937 rng(device());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(1, windowHeight);
		y = dist6(rng);

		drawSubRectangle(176,112,16,24,x, y);
	}

}


int main() {


	RS_Initialize("Manmeet Singh", windowWidth, windowHeight);
	drawBG();
	drawRand();

	do {
		//animate

	} while (RS_Update(windowArray, sizeof(windowArray) >> 2));
	RS_Shutdown();
	return 0;
}