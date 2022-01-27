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
#include "StoneHenge.h"
#include "StarField.h"

#pragma region Raster Window
const unsigned int windowWidth = 800;
const unsigned int windowHeight = 600;
unsigned int windowArray[windowWidth * windowHeight] = { 0, };
#pragma endregion

#pragma region Z Buffer
const unsigned int bufferWidth = windowWidth;
const unsigned int bufferHeight = windowHeight;
float bufferArray[bufferWidth * bufferHeight] = { 0, };
#pragma endregion

#pragma region Wireframe Cube
//void wireframeCube(Cube myCube, RASTER_WINDOW win, unsigned int color) {
//	auto lines = myCube.getLines();
//	for (auto i = lines.linesPair.cbegin(), end = lines.linesPair.cend(); i != end; std::advance(i, 2)) {
//
//		VEC_4D UnEditableP1 = lines.vertexPoint[*i];
//		VEC_4D UnEditableP2 = lines.vertexPoint[*std::next(i)];
//		PixelShader = PS_Green;
//		drawLine(win, UnEditableP1, UnEditableP2, 0x0000ff);
//	}
//}
#pragma endregion

#pragma region Colored Cube
//void coloredCube(Cube myCube, RASTER_WINDOW win, Z_BUFFER buff, unsigned int color) {
//	auto triangles = myCube.getTriangles();
//
//	unsigned int colors[12] = {
//	0xff0000,
//	0xff0000,
//	0x00ff00,
//	0x00ff00,
//	0x0000ff,
//	0x0000ff,
//	0xff00ff,
//	0xff00ff,
//	0xffff00,
//	0xffff00,
//	0x00ffff,
//	0x00ffff
//	};
//
//	for (auto i = triangles.linesPair.cbegin(), end = triangles.linesPair.cend(); i != end; std::advance(i, 3)) {
//
//		VEC_4D UnEditableP1 = triangles.vertexPoint[*i];
//		VEC_4D UnEditableP2 = triangles.vertexPoint[*std::next(i)];
//		VEC_4D UnEditableP3 = triangles.vertexPoint[*std::next(i, 2)];
//		//PixelShader = PS_Green;
//		fillTriangle(win, buff, UnEditableP1, UnEditableP2, UnEditableP3, colors[std::distance(triangles.linesPair.cbegin(),i) / 3]);
//
//	}
//}
#pragma endregion

#pragma region Textured Cube
//void texturedCube(Cube myCube, RASTER_WINDOW win, Z_BUFFER buff, unsigned int color) {
//	auto triangles = myCube.getTexTri();
//
//	for (auto i = triangles.linesPair.cbegin(), end = triangles.linesPair.cend(); i != end; std::advance(i, 3)) {
//
//		VEC_4D UnEditableP1 = triangles.uvVertPair.vertexPoint[*i];
//		VEC_4D UnEditableP2 = triangles.uvVertPair.vertexPoint[*std::next(i)];
//		VEC_4D UnEditableP3 = triangles.uvVertPair.vertexPoint[*std::next(i, 2)];
//
//		VEC_2D UnEditableP1UV = triangles.uvVertPair.uvPoint[*i];
//		VEC_2D UnEditableP2UV = triangles.uvVertPair.uvPoint[*std::next(i)];
//		VEC_2D UnEditableP3UV = triangles.uvVertPair.uvPoint[*std::next(i, 2)];
//
//		TexturePixelShader = PS_Texture;
//		fillTexTri(win, buff, UnEditableP1, UnEditableP2, UnEditableP3, UnEditableP1UV, UnEditableP2UV, UnEditableP3UV, 0xffffff);
//
//	}
//}
#pragma endregion

void loadModel(RASTER_WINDOW win, Z_BUFFER buff) {

	for (int i = 0; i < 2532; i += 3) {

		int v1 = StoneHenge_indicies[i];
		int v2 = StoneHenge_indicies[i + 1];
		int v3 = StoneHenge_indicies[i + 2];

		VERTEX shVertex1 = {
			//VERTS
			{ StoneHenge_data[v1].pos[0] * 0.1f, StoneHenge_data[v1].pos[1] * 0.1f, StoneHenge_data[v1].pos[2] * 0.1f, 1.0f },
			//UVWs
			{ StoneHenge_data[v1].uvw[0], StoneHenge_data[v1].uvw[1], StoneHenge_data[v1].uvw[2] },
			//NORMS
			{ StoneHenge_data[v1].nrm[0], StoneHenge_data[v1].nrm[1], StoneHenge_data[v1].nrm[2], 0 },
			//COLORs
			0xFFC0C0F0
		};

		VERTEX shVertex2 = {
			//VERTS
			{ StoneHenge_data[v2].pos[0] * 0.1f, StoneHenge_data[v2].pos[1] * 0.1f, StoneHenge_data[v2].pos[2] * 0.1f, 1.0f },
			//UVWs
			{ StoneHenge_data[v2].uvw[0], StoneHenge_data[v2].uvw[1], StoneHenge_data[v2].uvw[2] },
			//NORMS
			{ StoneHenge_data[v2].nrm[0], StoneHenge_data[v2].nrm[1], StoneHenge_data[v2].nrm[2], 0 },
			//COLORs
			0xFFC0C0F0
		};

		VERTEX shVertex3 = {
			//VERTS
			{ StoneHenge_data[v3].pos[0] * 0.1f, StoneHenge_data[v3].pos[1] * 0.1f, StoneHenge_data[v3].pos[2] * 0.1f, 1.0f },
			//UVWs
			{ StoneHenge_data[v3].uvw[0], StoneHenge_data[v3].uvw[1], StoneHenge_data[v3].uvw[2] },
			//NORMS
			{ StoneHenge_data[v3].nrm[0], StoneHenge_data[v3].nrm[1], StoneHenge_data[v3].nrm[2], 0 },
			//COLORs
			0xFFC0C0F0
		};


		TRIANGLE_DATA shModelData = {shVertex1, shVertex2, shVertex3 };

		PixelShader = PS_Texture;
		fillTexTri(win, buff, shModelData);
	}
}

//void drawGrid(Grid myGrid, RASTER_WINDOW win, unsigned int color) {
//	auto lines = myGrid.getLines();
//
//	for (auto i = lines.linesPair.cbegin(), end = lines.linesPair.cend(); i != end; std::advance(i, 2)) {
//
//		VEC_4D UnEditableP1 = lines.vertexPoint[*i];
//		VEC_4D UnEditableP2 = lines.vertexPoint[*std::next(i)];
//
//		PixelShader = PS_White;
//		drawLine(win, UnEditableP1, UnEditableP2, 0xff0000);
//	}
//}

void drawField(StarField myField, RASTER_WINDOW win, Z_BUFFER buff) {
	auto points = myField.getPos();

	for (int i = 0; i < points.size(); i++) {

		VEC_4D UnEditableP1 = points[i];
		PixelShader = PS_White;
		drawStarField(win, UnEditableP1, 0xffffffff);
	}
}

int main() {
	RASTER_WINDOW myWindow = { windowWidth, windowHeight, windowArray };
	Z_BUFFER zBuff = { bufferWidth, bufferHeight, bufferArray };

	XTime time;
	time.Restart();

	RS_Initialize("Manmeet Singh", windowWidth, windowHeight);

	//Shader Variables
	SV_CameraMatrix = matMath_4D_MultiplyMatrix(matMath_4D_RotateX(10.0f), matMath_4D_Translation(0.0f, 0.0f, -1.0f));
	SV_ViewMatrix = matMath_4D_FastInverse(SV_CameraMatrix);
	SV_ProjectionMatrix = matMath_4D_ProjectionMatrix(0.1f, 10.0f, 90.0f, ((float)myWindow.windowHeight / (float)myWindow.windowWidth));
	SV_DirectionalLight = { { -0.577f, -0.577f, 0.577f, 0.0f }, 0xFFC0C0F0 };
	SV_PointLight = { { -1.0f, 0.5f, 1.0f, 0.0f }, 0xFFC0C0F0 };
	SV_AmbientLight = 0.1f;

	MATRIX_4X4 WorldMatrix;

	float theta = 0.0f;

	StarField myField(3000);

	do {
		time.Signal();
		clearScreenWithColor(myWindow, 0x030f36);
		clearZBuff(zBuff);
		VertexShader = VS_Lighting;
	
		theta = 10.0f * time.TotalTime();
		WorldMatrix = matMath_4D_MultiplyMatrix(matMath_4D_RotateY(-theta), matMath_4D_Translation(0.0f, -1.0f, 2.0f));
		SV_WorldMatrix = WorldMatrix;
		SV_PLRadius = 2.5f + (2.5f * std::sin(time.TotalTime()));

		drawField(myField, myWindow, zBuff);
		loadModel(myWindow, zBuff);
	} while (RS_Update(windowArray, sizeof(windowArray) >> 2));
	RS_Shutdown();
	return 0;
}