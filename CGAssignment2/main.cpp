// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include "RasterSurface.h"
#include "CGMath.h"
#include "Shaders.h"
#include "DrawFunctions.h"
#include "Defines.h"
#include "Cube.h"
#include "XTime.h"
#include "Grid.h"

//Raster Window Stuff
const unsigned int windowWidth = 500;
const unsigned int windowHeight = 500;
unsigned int windowArray[windowWidth * windowHeight] = { 0, };

//for (int i = 0; i < 3; i++)
//{
//	for (int j = 0; j < 3; j++)
//	{
//		std::cout << rotation.mat[i][j] << " \n"[j == 3 - 1];
//	}
//	std::cout << std::endl;
//}

void drawCube(Cube myCube, RASTER_WINDOW win, unsigned int color) {
	auto lines = myCube.getLines();

	for (auto i = lines.linesPair.cbegin(), end = lines.linesPair.cend(); i != end; std::advance(i, 2)) {
		//VertexW = VertexL times World. 
		//VertexV = VertexW times View.
		//VertexP = VertexV times Projection.

		VEC_4D UnEditableP1 = lines.vertexPoint[*i];
		VEC_4D UnEditableP2 = lines.vertexPoint[*std::next(i)];

		PixelShader = PS_Green;
		drawLine(win, UnEditableP1, UnEditableP2, 0xff0000);
	}
}

void drawGrid(Grid myGrid, RASTER_WINDOW win, unsigned int color) {
	auto lines = myGrid.getLines();

	for (auto i = lines.linesPair.cbegin(), end = lines.linesPair.cend(); i != end; std::advance(i, 2)) {
		//VertexW = VertexL times World. 
		//VertexV = VertexW times View.
		//VertexP = VertexV times Projection.

		VEC_4D UnEditableP1 = lines.vertexPoint[*i];
		VEC_4D UnEditableP2 = lines.vertexPoint[*std::next(i)];

		PixelShader = PS_White;
		drawLine(win, UnEditableP1, UnEditableP2, 0xff0000);
	}
}

int main() {
	RASTER_WINDOW myWindow = { windowWidth, windowHeight, windowArray };
	XTime time;
	time.Restart();

	RS_Initialize("Manmeet Singh", windowWidth, windowHeight);

	//Camera 
	SV_CameraMatrix = matMath_4D_MultiplyMatrix(matMath_4D_RotateX(-18), matMath_4D_Translation(0, 0, -1.0));

	//View
	SV_ViewMatrix = matMath_4D_FastInverse(SV_CameraMatrix);
	
	//Projection
	SV_ProjectionMatrix = matMath_4D_ProjectionMatrix(0.1f, 10.0f, 90.0f, myWindow.windowHeight / myWindow.windowWidth);

	//Grid World Identity Matrix
	MATRIX_4X4 GridWorldMatrix = matMath_4D_Identity();
	
	// Cube World Matrix
	MATRIX_4X4 CubeWorldMatrix;


	//Create Cube
	Cube myCube(0.5f);
	Grid myGrid(1.0f);
	float theta;

	do {
		clearScreenWithColor(myWindow, 0x000000);
		time.Signal();

		theta = 50 * time.TotalTime();
		CubeWorldMatrix = matMath_4D_MultiplyMatrix(matMath_4D_RotateY(theta), matMath_4D_Translation(0, 0.25, 0.0));

		VertexShader = VS_ApplyMatrices;
		SV_WorldMatrix = CubeWorldMatrix;
		drawCube(myCube, myWindow, 0x00ff00);

		SV_WorldMatrix = GridWorldMatrix;
		drawGrid(myGrid, myWindow, 0x00ff00);

	} while (RS_Update(windowArray, sizeof(windowArray) >> 2));
	RS_Shutdown();
	return 0;
}