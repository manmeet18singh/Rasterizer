#pragma once
#include "defines.h"
#include "CGMath.h"

void clearScreenWithColor(RASTER_WINDOW win, unsigned int color) {
	for (unsigned int y = 0; y < win.windowHeight; ++y) {
		for (unsigned int x = 0; x < win.windowWidth; ++x) {
			*win.windowArray++ = color;
		}
	}
}

void drawPixel(RASTER_WINDOW win, int x, int y, int pixelToDraw) {
	if (x >= 0 && y >= 0 && x < win.windowWidth && y < win.windowHeight) {
		win.windowArray[y * win.windowWidth + x] = pixelToDraw;
	}
}

//Check for sign and return the increment value needed

int incrementValue(int value) {
	if (value < 0) {
		return -1;
	}
	else if (value > 0) {
		return 1;
	}
	else {
		return 0;
	}
}

 //Bresenham line
void drawLine(const RASTER_WINDOW& win, const VEC_4D& a, const VEC_4D& b, const unsigned int& color) {
	
	VEC_4D tempCopyA = a;
	VEC_4D tempCopyB = b;

	if (VertexShader) {
		VertexShader(tempCopyA);
		VertexShader(tempCopyB);
	}

	VEC_4D copyA = ndcConvert(tempCopyA, win);
	VEC_4D copyB = ndcConvert(tempCopyB, win);

	unsigned int copyColor = color;

	int x1 = (int)copyA.x;
	int x2 = (int)copyB.x;
	int y1 = (int)copyA.y;
	int y2 = (int)copyB.y;

	int changeX = x2 - x1;
	int changeY = y2 - y1;
	int xIncrementValue = incrementValue(changeX);
	int yIncrementValue = incrementValue(changeY);

	changeX = std::abs(changeX);
	changeY = std::abs(changeY);

	// Check for a horizontal line
	if (changeY == 0)
	{
		for (int currX = x1; currX != (x2 + xIncrementValue); currX += xIncrementValue) {

			if (PixelShader) {
				PixelShader(copyColor);
			}

			drawPixel(win, currX, y1, copyColor);
		}
	}
	// Check for a vertical line
	else if (changeX == 0)
	{
		for (int currY = y1; currY != (y2 + yIncrementValue); currY += yIncrementValue) {

			if (PixelShader) {
				PixelShader(copyColor);
			}

			drawPixel(win, x1, currY, copyColor);
		}
	}
	// Check if line is more horizontal than vertical
	else if (changeX >= changeY)
	{
		int slope = 2 * changeY;
		int error = -changeX;
		int errorIncrementValue = -2 * changeX;
		int currY = y1;

		for (int currX = x1; currX != (x2 + xIncrementValue); currX += xIncrementValue)
		{
			if (PixelShader) {
				PixelShader(copyColor);
			}

			drawPixel(win, currX, currY, copyColor);
			error += slope;

			if (error >= 0)
			{
				currY += yIncrementValue;
				error += errorIncrementValue;
			}
		}
	}
	// line is more vertical than horizontal
	else
	{
		int slope = 2 * changeX;
		int error = -changeY;
		int errorIncrementValue = -2 * changeY;
		int currX = x1;

		for (int currY = y1; currY != (y2 + yIncrementValue); currY += yIncrementValue)
		{
			if (PixelShader) {
				PixelShader(copyColor);
			}

			drawPixel(win, currX, currY, copyColor);
			error += slope;

			if (error >= 0)
			{
				currX += xIncrementValue;
				error += errorIncrementValue;
			}
		}
	}
}



//Provided by prof L.Norri's CGS Setting up a shader framework YouTube Video
//void fillTriangle(VERTEX_2D a, VERTEX_2D b, VERTEX_2D c) {
//	for (int y = 0; y < 
//}
