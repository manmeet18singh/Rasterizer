#pragma once
#include "defines.h"
#include "CGMath.h"

void clearScreenWithColor(RASTER_WINDOW win, unsigned int color) {
	const int size = win.windowHeight * win.windowWidth;

	for (unsigned int i = 0; i < size; ++i) {
		win.windowArray[i] = color;
	}
}

void clearZBuff(Z_BUFFER buff) {
	const int size =  buff.bufferWidth * buff.bufferHeight ;

	for (int i = 0; i < size; ++i) {
		buff.bufferArray[i] = 1.0f;
	}
}

float getZBuff(Z_BUFFER buff, int x, int y) {
	if (x >= 0 && y >= 0 && x < buff.bufferWidth && y < buff.bufferHeight) {
		return buff.bufferArray[y * buff.bufferWidth + x];
	}
}

void drawPixelDepth(RASTER_WINDOW win, Z_BUFFER buff, int x, int y, float depth, unsigned int color) {
	if (x >= 0 && y >= 0 && x < win.windowWidth && y < win.windowHeight) {
		float zInBuffer = getZBuff(buff, x,y);
		if (depth < zInBuffer) {
			buff.bufferArray[y * buff.bufferWidth + x] = depth;
			win.windowArray[y * win.windowWidth + x] = color;
		}
	}
}

void drawPixel(RASTER_WINDOW win, int x, int y, unsigned int color) {
	if (x >= 0 && y >= 0 && x < win.windowWidth && y < win.windowHeight) {
			win.windowArray[y * win.windowWidth + x] = color;
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

void fillTriangle(const RASTER_WINDOW& win, const Z_BUFFER& buff, const VEC_4D& a, const VEC_4D& b, const VEC_4D& c, const unsigned int& color) {
	unsigned int copyColor = color;
	VEC_4D tempCopyA = a;
	VEC_4D tempCopyB = b;
	VEC_4D tempCopyC = c;

	if (VertexShader) {
		VertexShader(tempCopyA);
		VertexShader(tempCopyB);
		VertexShader(tempCopyC);
	}

	VEC_4D copyA = ndcConvert(tempCopyA, win);
	VEC_4D copyB = ndcConvert(tempCopyB, win);
	VEC_4D copyC = ndcConvert(tempCopyC, win);

	float startX = std::min(copyA.x, std::min(copyB.x, copyC.x ));
	float startY = std::min(copyA.y, std::min(copyB.y, copyC.y ));
	float endX = std::max(copyA.x, std::max(copyB.x, copyC.x ));
	float endY = std::max(copyA.y, std::max(copyB.y, copyC.y));

	for (int y = startY; y < endY; ++y)
	{
		for (int x = startX; x < endX; ++x)
		{
			VEC_3D bary = barycentricCoordinates(copyA, copyB, copyC, { x * 1.0f, y * 1.0f, 1.0f });
			if (bary.x < 0 || bary.x > 1 || bary.y < 0 || bary.y > 1 || bary.z < 0 || bary.z > 1) {
				continue;
			}

			float depth = barycentricInterpolation(bary.x, bary.y, bary.z, copyA.z, copyB.z, copyC.z);

			if (PixelShader) {
				PixelShader(copyColor);
			}

			drawPixelDepth(win, buff, x, y, depth, copyColor);
		}
	}
}

void fillTexTri(const RASTER_WINDOW& win, const Z_BUFFER& buff, const VEC_4D& a, const VEC_4D& b, const VEC_4D& c, const VEC_2D& aUV, const VEC_2D& bUV, const VEC_2D& cUV, const unsigned int& texel) {
	unsigned int copyColor = texel;

	VEC_4D tempCopyA = a;
	VEC_4D tempCopyB = b;
	VEC_4D tempCopyC = c;

	if (VertexShader) {
		VertexShader(tempCopyA);
		VertexShader(tempCopyB);
		VertexShader(tempCopyC);
	}

	VEC_2D copyAuv = aUV;
	VEC_2D copyBuv = bUV;
	VEC_2D copyCuv = cUV;

	VEC_4D copyA = ndcConvert(tempCopyA, win);
	VEC_4D copyB = ndcConvert(tempCopyB, win);
	VEC_4D copyC = ndcConvert(tempCopyC, win);

	float startX = std::min(copyA.x, std::min(copyB.x, copyC.x));
	float startY = std::min(copyA.y, std::min(copyB.y, copyC.y));
	float endX = std::max(copyA.x, std::max(copyB.x, copyC.x));
	float endY = std::max(copyA.y, std::max(copyB.y, copyC.y));

	for (int y = startY; y < endY; ++y)
	{
		for (int x = startX; x < endX; ++x)
		{
			VEC_3D bary = barycentricCoordinates(copyA, copyB, copyC, { x * 1.0f, y * 1.0f, 1.0f });
			if (bary.x < 0 || bary.x > 1 || bary.y < 0 || bary.y > 1 || bary.z < 0 || bary.z > 1) {
				continue;
			}

			if (TexturePixelShader) {
				float u = barycentricInterpolation(bary.x, bary.y, bary.z, copyAuv.u, copyBuv.u, copyCuv.u);
				float v = barycentricInterpolation(bary.x, bary.y, bary.z, copyAuv.v, copyBuv.v, copyCuv.v);
				TexturePixelShader(u,v,copyColor);
			}

			float depth = barycentricInterpolation(bary.x, bary.y, bary.z, copyA.z, copyB.z, copyC.z);
			drawPixelDepth(win, buff, x, y, depth, copyColor);
		}
	}
}