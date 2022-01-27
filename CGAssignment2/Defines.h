#pragma once
#include <vector>
struct RASTER_WINDOW
{
	const unsigned int windowWidth;
	const unsigned int windowHeight;
	unsigned int* windowArray;
};

#pragma region Vector Structs
//Vector Structs provided by prof L.Norri's YouTube Video
struct VEC_2D {
	float x, y;
};

struct VEC_3D {
	float x, y, z;
};

struct VEC_4D {
	float x, y, z, w;
};

struct VERTEX_2D
{
	VEC_2D pos;
	unsigned color;
};
#pragma endregion

#pragma region Matrix Structs
struct MATRIX_2X2 {
	//[row][col]
	float mat[2][2];
};

struct MATRIX_3X3 {
	//[row][col]
	float mat[3][3];
};

struct MATRIX_4X4 {
	//[row][col]
	float mat[4][4];
};
#pragma endregion

#pragma region Cube Structs
struct LINE_VERTEX_PAIR
{
	std::vector<VEC_4D> vertexPoint;
	std::vector<size_t> linesPair;
};
#pragma endregion


