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

#pragma region Raster Window
const unsigned int windowWidth = 800;
const unsigned int windowHeight = 600;
unsigned int windowArray[windowWidth * windowHeight] = { 0, };
#pragma endregion

//for (int i = 0; i < 3; i++)
//{
//	for (int j = 0; j < 3; j++)
//	{
//		std::cout << rotation.mat[i][j] << " \n"[j == 3 - 1];
//	}
//	std::cout << std::endl;
//}

#pragma region Z Buffer
const unsigned int bufferWidth = windowWidth;
const unsigned int bufferHeight = windowHeight;
float bufferArray[bufferWidth * bufferHeight] = { 0, };
#pragma endregion

void wireframeCube(Cube myCube, RASTER_WINDOW win, unsigned int color) {
	auto lines = myCube.getLines();
	for (auto i = lines.linesPair.cbegin(), end = lines.linesPair.cend(); i != end; std::advance(i, 2)) {

		VEC_4D UnEditableP1 = lines.vertexPoint[*i];
		VEC_4D UnEditableP2 = lines.vertexPoint[*std::next(i)];
		PixelShader = PS_Green;
		drawLine(win, UnEditableP1, UnEditableP2, 0x0000ff);
	}
}

void coloredCube(Cube myCube, RASTER_WINDOW win, Z_BUFFER buff, unsigned int color) {
	auto triangles = myCube.getTriangles();

	unsigned int colors[12] = {
	0xff0000,
	0xff0000,
	0x00ff00,
	0x00ff00,
	0x0000ff,
	0x0000ff,
	0xff00ff,
	0xff00ff,
	0xffff00,
	0xffff00,
	0x00ffff,
	0x00ffff
	};

	for (auto i = triangles.linesPair.cbegin(), end = triangles.linesPair.cend(); i != end; std::advance(i, 3)) {

		VEC_4D UnEditableP1 = triangles.vertexPoint[*i];
		VEC_4D UnEditableP2 = triangles.vertexPoint[*std::next(i)];
		VEC_4D UnEditableP3 = triangles.vertexPoint[*std::next(i, 2)];
		//PixelShader = PS_Green;
		fillTriangle(win, buff, UnEditableP1, UnEditableP2, UnEditableP3, colors[std::distance(triangles.linesPair.cbegin(),i) / 3]);

	}
}

void texturedCube(Cube myCube, RASTER_WINDOW win, Z_BUFFER buff, unsigned int color) {
	auto triangles = myCube.getTexTri();

	for (auto i = triangles.linesPair.cbegin(), end = triangles.linesPair.cend(); i != end; std::advance(i, 3)) {

		VEC_4D UnEditableP1 = triangles.uvVertPair.vertexPoint[*i];
		VEC_4D UnEditableP2 = triangles.uvVertPair.vertexPoint[*std::next(i)];
		VEC_4D UnEditableP3 = triangles.uvVertPair.vertexPoint[*std::next(i, 2)];

		VEC_2D UnEditableP1UV = triangles.uvVertPair.uvPoint[*i];
		VEC_2D UnEditableP2UV = triangles.uvVertPair.uvPoint[*std::next(i)];
		VEC_2D UnEditableP3UV = triangles.uvVertPair.uvPoint[*std::next(i, 2)];

		TexturePixelShader = PS_Texture;
		fillTexTri(win, buff, UnEditableP1, UnEditableP2, UnEditableP3, UnEditableP1UV,UnEditableP2UV,UnEditableP3UV, 0xffffff);

	}
}

void drawGrid(Grid myGrid, RASTER_WINDOW win, unsigned int color) {
	auto lines = myGrid.getLines();

	for (auto i = lines.linesPair.cbegin(), end = lines.linesPair.cend(); i != end; std::advance(i, 2)) {

		VEC_4D UnEditableP1 = lines.vertexPoint[*i];
		VEC_4D UnEditableP2 = lines.vertexPoint[*std::next(i)];

		PixelShader = PS_White;
		drawLine(win, UnEditableP1, UnEditableP2, 0xff0000);
	}
}

int main() {
	RASTER_WINDOW myWindow = { windowWidth, windowHeight, windowArray };
	Z_BUFFER zBuff = { bufferWidth, bufferHeight, bufferArray};

	XTime time;
	time.Restart();

	RS_Initialize("Manmeet Singh", windowWidth, windowHeight);

	//Camera 
	SV_CameraMatrix = matMath_4D_MultiplyMatrix(matMath_4D_RotateX(-18.0f), matMath_4D_Translation(0.0f, 0.0f, -1.0f));

	//View
	SV_ViewMatrix = matMath_4D_FastInverse(SV_CameraMatrix);
	
	//Projection
	SV_ProjectionMatrix = matMath_4D_ProjectionMatrix(0.1f, 10.0f, 90.0f, ((float)myWindow.windowHeight / (float)myWindow.windowWidth));

	//Create Cube
	Cube myCube(1.0f);
	Grid myGrid(1.0f);
	float theta = 0.0f;

	//Grid World Identity Matrix
	MATRIX_4X4 GridWorldMatrix = matMath_4D_Identity();
	
	// Cube World Matrix
	MATRIX_4X4 CubeWorldMatrix;

	do {
		clearScreenWithColor(myWindow, 0x000000);
		clearZBuff(zBuff);

		time.Signal();

		theta = 50.0f * time.TotalTime();

		SV_WorldMatrix = GridWorldMatrix;
		drawGrid(myGrid, myWindow, 0x00ff00);

		CubeWorldMatrix = matMath_4D_MultiplyMatrix(matMath_4D_RotateY(-theta), matMath_4D_Translation(0.0f, 0.25f, 1.0f));

		SV_WorldMatrix = CubeWorldMatrix;
		texturedCube(myCube, myWindow, zBuff, 0x00ff00);

		VertexShader = VS_ApplyMatrices;
	} while (RS_Update(windowArray, sizeof(windowArray) >> 2));
	RS_Shutdown();
	return 0;
}