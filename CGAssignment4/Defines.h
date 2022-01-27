#pragma once
#include <vector>
struct RASTER_WINDOW
{
	const unsigned int windowWidth;
	const unsigned int windowHeight;
	unsigned int* windowArray;
};

struct Z_BUFFER
{
	const unsigned int bufferWidth;
	const unsigned int bufferHeight;
	float* bufferArray;
};

#pragma region Vector Structs
//Vector Structs provided by prof L.Norri's YouTube Video
struct VEC_2D {
	float u, v;
};

struct VEC_3D {
	float x, y, z;
};

struct VEC_4D {
	float x, y, z, w;
};

struct LIGHTS {
	VEC_4D pos;
	unsigned int color;
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

struct UV_VERTEX_PAIR {
	std::vector<VEC_2D> uvPoint;
	std::vector<VEC_4D> vertexPoint;
};

struct LINE_VERTEX_PAIR {
	std::vector<VEC_4D> vertexPoint;
	std::vector<size_t> linesPair;
};

struct TEXTURED_LINE_PAIR {
	UV_VERTEX_PAIR uvVertPair;
	std::vector<size_t> linesPair;
};
#pragma endregion

#pragma region Model Structs
struct VERTEX {
	VEC_4D vert;
	VEC_3D uv;
	VEC_4D nrm;
	unsigned int clr;
};

struct TRIANGLE_DATA {
	VERTEX v1, v2, v3;
};
#pragma endregion

