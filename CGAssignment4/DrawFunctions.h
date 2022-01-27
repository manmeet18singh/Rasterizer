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

void drawPixelDepth(RASTER_WINDOW win, Z_BUFFER buff, VERTEX vertex, float depth) {
	int x = vertex.vert.x;
	int y = vertex.vert.y;
	if (x >= 0 && y >= 0 && x < win.windowWidth && y < win.windowHeight) {
		float zInBuffer = getZBuff(buff, x,y);
		if (depth < zInBuffer) {
			buff.bufferArray[y * buff.bufferWidth + x] = depth;
			win.windowArray[y * win.windowWidth + x] = vertex.clr;
		}
	}
}

void drawPixel(RASTER_WINDOW win, VERTEX vertex) {
	if ((int)vertex.vert.x >= 0 && (int)vertex.vert.y >= 0 && (int)vertex.vert.x < win.windowWidth && (int)vertex.vert.y < win.windowHeight) {
			win.windowArray[(int)vertex.vert.y * win.windowWidth + (int)vertex.vert.x] = vertex.clr;
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
//void drawLine(const RASTER_WINDOW& win, const VEC_4D& a, const VEC_4D& b, const unsigned int& color) {
//	
//	VEC_4D tempCopyA = a;
//	VEC_4D tempCopyB = b;
//
//	//if (VertexShader) {
//	//	VertexShader(tempCopyA);
//	//	VertexShader(tempCopyB);
//	//}
//
//	VEC_4D copyA = ndcConvert(tempCopyA, win);
//	VEC_4D copyB = ndcConvert(tempCopyB, win);
//
//	unsigned int copyColor = color;
//
//	int x1 = (int)copyA.x;
//	int x2 = (int)copyB.x;
//	int y1 = (int)copyA.y;
//	int y2 = (int)copyB.y;
//
//	int changeX = x2 - x1;
//	int changeY = y2 - y1;
//	int xIncrementValue = incrementValue(changeX);
//	int yIncrementValue = incrementValue(changeY);
//
//	changeX = std::abs(changeX);
//	changeY = std::abs(changeY);
//
//	// Check for a horizontal line
//	if (changeY == 0)
//	{
//		for (int currX = x1; currX != (x2 + xIncrementValue); currX += xIncrementValue) {
//
//			if (PixelShader) {
//				//PixelShader(copyColor);
//			}
//
//			drawPixel(win, currX, y1, copyColor);
//		}
//	}
//	// Check for a vertical line
//	else if (changeX == 0)
//	{
//		for (int currY = y1; currY != (y2 + yIncrementValue); currY += yIncrementValue) {
//
//			if (PixelShader) {
//				//PixelShader(copyColor);
//			}
//
//			drawPixel(win, x1, currY, copyColor);
//		}
//	}
//	// Check if line is more horizontal than vertical
//	else if (changeX >= changeY)
//	{
//		int slope = 2 * changeY;
//		int error = -changeX;
//		int errorIncrementValue = -2 * changeX;
//		int currY = y1;
//
//		for (int currX = x1; currX != (x2 + xIncrementValue); currX += xIncrementValue)
//		{
//			if (PixelShader) {
//				//PixelShader(copyColor);
//			}
//
//			drawPixel(win, currX, currY, copyColor);
//			error += slope;
//
//			if (error >= 0)
//			{
//				currY += yIncrementValue;
//				error += errorIncrementValue;
//			}
//		}
//	}
//	// line is more vertical than horizontal
//	else
//	{
//		int slope = 2 * changeX;
//		int error = -changeY;
//		int errorIncrementValue = -2 * changeY;
//		int currX = x1;
//
//		for (int currY = y1; currY != (y2 + yIncrementValue); currY += yIncrementValue)
//		{
//			if (PixelShader) {
//				//PixelShader(copyColor);
//			}
//
//			drawPixel(win, currX, currY, copyColor);
//			error += slope;
//
//			if (error >= 0)
//			{
//				currX += xIncrementValue;
//				error += errorIncrementValue;
//			}
//		}
//	}
//}

//void fillTriangle(const RASTER_WINDOW& win, const Z_BUFFER& buff, const VEC_4D& a, const VEC_4D& b, const VEC_4D& c, const unsigned int& color) {
//	unsigned int copyColor = color;
//	VEC_4D tempCopyA = a;
//	VEC_4D tempCopyB = b;
//	VEC_4D tempCopyC = c;
//
//	//if (VertexShader) {
//	//	VertexShader(tempCopyA);
//	//	VertexShader(tempCopyB);
//	//	VertexShader(tempCopyC);
//	//}
//
//	VEC_4D copyA = ndcConvert(tempCopyA, win);
//	VEC_4D copyB = ndcConvert(tempCopyB, win);
//	VEC_4D copyC = ndcConvert(tempCopyC, win);
//
//	float startX = std::min(copyA.x, std::min(copyB.x, copyC.x ));
//	float startY = std::min(copyA.y, std::min(copyB.y, copyC.y ));
//	float endX = std::max(copyA.x, std::max(copyB.x, copyC.x ));
//	float endY = std::max(copyA.y, std::max(copyB.y, copyC.y));
//
//	for (int y = startY; y < endY; ++y)
//	{
//		for (int x = startX; x < endX; ++x)
//		{
//			//VEC_3D bary = barycentricCoordinates(copyA, copyB, copyC, { x * 1.0f, y * 1.0f, 1.0f });
//			//if (bary.x < 0 || bary.x > 1 || bary.y < 0 || bary.y > 1 || bary.z < 0 || bary.z > 1) {
//				//continue;
//			//}
//
//			//float depth = barycentricInterpolation(bary.x, bary.y, bary.z, copyA.z, copyB.z, copyC.z);
//
//			if (PixelShader) {
//				//PixelShader(copyColor);
//			}
//
//			drawPixelDepth(win, buff, x, y, depth, copyColor);
//		}
//	}
//}

void fillTexTri(const RASTER_WINDOW& win, const Z_BUFFER& buff, const TRIANGLE_DATA& tri) {

	unsigned int copyColor1 = tri.v1.clr;
	unsigned int copyColor2 = tri.v2.clr;
	unsigned int copyColor3 = tri.v3.clr;

	VERTEX copyV1 = tri.v1;
	VERTEX copyV2 = tri.v2;
	VERTEX copyV3 = tri.v3;

	if (VertexShader) {
		VertexShader(copyV1);
		VertexShader(copyV2);
		VertexShader(copyV3);
	}

	////Backface Cull
	if (copyV1.nrm.z > 0.0f || copyV2.nrm.z > 0.0f || copyV3.nrm.z > 0.0f) {
		return;
	}

	VEC_4D ndcV1 = ndcConvert(copyV1.vert, win);
	VEC_4D ndcV2 = ndcConvert(copyV2.vert, win);
	VEC_4D ndcV3 = ndcConvert(copyV3.vert, win);

	float startX = std::min(ndcV1.x, std::min(ndcV2.x, ndcV3.x));
	float startY = std::min(ndcV1.y, std::min(ndcV2.y, ndcV3.y));
	float endX = std::max(ndcV1.x, std::max(ndcV2.x, ndcV3.x));
	float endY = std::max(ndcV1.y, std::max(ndcV2.y, ndcV3.y));

	for (int y = startY; y < endY; ++y)
	{
		for (int x = startX; x < endX; ++x)
		{
			VEC_4D baryCoordinates = barycentricCoordinates(ndcV1, ndcV2, ndcV3, { x * 1.0f, y * 1.0f, 1.0f });

			if (baryCoordinates.x < 0 || baryCoordinates.x > 1 || baryCoordinates.y < 0 || baryCoordinates.y > 1 || baryCoordinates.z < 0 || baryCoordinates.z > 1) {
				continue;
			}

			float u = berp(baryCoordinates.x, baryCoordinates.y, baryCoordinates.z, copyV1.uv.x, copyV2.uv.x, copyV3.uv.x);
			float v = berp(baryCoordinates.x, baryCoordinates.y, baryCoordinates.z, copyV1.uv.y, copyV2.uv.y, copyV3.uv.y);
			unsigned int berpedColor = colorMath_berpColor(baryCoordinates.x, baryCoordinates.y, baryCoordinates.z, copyV1.clr, copyV2.clr, copyV3.clr);

			//VEC_4D vert;
			//VEC_3D uv;
			//VEC_4D nrm;
			//unsigned int clr;
			VERTEX interpolatedVals =
			{
				{ x, y, 0.0f, 0.0f },
				{ u, v, 0.0f },
				{ 0.0f, 0.0f, 0.0f, 0.0f },
				berpedColor
			};

			if (PixelShader) {
				PixelShader(interpolatedVals);
			}

			float depth = berp(baryCoordinates.x, baryCoordinates.y, baryCoordinates.z, ndcV1.z, ndcV2.z, ndcV3.z);
			drawPixelDepth(win, buff, interpolatedVals, depth);
		}
	}
}

void drawStarField(const RASTER_WINDOW& win, const VEC_4D& a, const unsigned int& color) {
	unsigned int copyColor = color;
	VEC_4D copyA = a;

	VERTEX updatedVert1 =
	{
		copyA,
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 0.0f },
		copyColor
	};

	if (VertexShader) {
		VertexShader(updatedVert1);
	}

	VEC_4D ndcCopy = ndcConvert(updatedVert1.vert, win);

	VERTEX updatedVert2 =
	{
		ndcCopy,
		{ 0.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 0.0f },
		copyColor
	};

	if (PixelShader) {
		PixelShader(updatedVert2);
	}

	drawPixel(win, updatedVert2);
}