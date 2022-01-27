#pragma once
#include "defines.h"

//Implicit Line EQ function provided by prof L.Norri's CGS Setting up a shader framework YouTube Video
float implicitLineEq(VEC_4D a, VEC_4D b, VEC_4D p) {
	return (a.y - b.y) * p.x + (b.x - a.x) * p.y + a.x * b.y - a.y * b.x;
}

//Barycentric function provided by prof L.Norri's CGS Setting up a shader framework YouTube Video
VEC_4D barycentricCoordinates(VEC_4D a, VEC_4D b, VEC_4D c, VEC_4D p) {
	float maxA = implicitLineEq(b, c, a);
	float subA = implicitLineEq(b, c, p);

	float maxB = implicitLineEq(a, c, b);
	float subB = implicitLineEq(a, c, p);

	float maxC = implicitLineEq(b, a, c);
	float subC = implicitLineEq(b, a, p);

	return { subA / maxA, subB / maxB, subC / maxC, 0.0f };
}

float berp(float alpha, float beta, float gamma, float A, float B, float C) {
	return A * alpha + B * beta + C * gamma;
}

VEC_4D ndcConvert(VEC_4D points, RASTER_WINDOW win) {
	return { (points.x + 1) * win.windowWidth / 2 , (1 - points.y) * win.windowHeight / 2, points.z, points.w };
}

float deg2Rad(float theta) {
	const double pi = std::acos(-1);
	return theta * (pi / 180.0f);
}

#pragma region Vector Math
VEC_4D vecMath_4D_AddVector(VEC_4D v1, VEC_4D v2) {
	return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

VEC_4D vecMath_4D_SubVector(VEC_4D v1, VEC_4D v2) {
	return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

VEC_4D vecMath_4D_MultNumber(VEC_4D v, float num) {
	return { v.x * num, v.y * num, v.z * num };
}

float vecMath_4D_Length(VEC_4D v1) {
	return std::sqrtf((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));
}

VEC_4D vecMath_4D_CrossProduct(VEC_4D v1, VEC_4D v2) {
	return { (v1.y * (v2.z - v1.z) * v2.y) , (v1.z * (v2.x - v1.x) * v2.z), (v1.x * (v2.y - v1.y) * v2.x) };
}

VEC_4D vecMath_4D_Normalize(VEC_4D v1) {
	float len = vecMath_4D_Length(v1);
	return { v1.x / len, v1.y / len, v1.z / len };
}

float vecMath_4D_DotProduct(VEC_4D v1, VEC_4D v2) {
	VEC_4D a = vecMath_4D_Normalize(v1);
	VEC_4D b = vecMath_4D_Normalize(v2);

	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}


VEC_4D vecMath_4D_FaceNormal(VEC_4D v1, VEC_4D v2, VEC_4D v3) {
	VEC_4D a = vecMath_4D_SubVector(v1, v2);
	VEC_4D b = vecMath_4D_SubVector(v1, v3);

	return vecMath_4D_Normalize(vecMath_4D_CrossProduct(a, b));
}

#pragma endregion

#pragma region Color Math
unsigned int colorMath_SaturateInt(unsigned int value, int max) {
	if (value > max) {
		return max;
	}
	if (value < 0) {
		return 0;
	}
	return value;
}

float colorMath_SaturateFloat(float val, float max) {
	if (val > max) {
		return 1;
	}
	if (val < 0) {
		return 0;
	}

	return val;
}

unsigned int colorMath_berpColor(float alpha, float beta, float gamma, unsigned int A, unsigned int B, unsigned int C) {
	unsigned int  a1 = ((A & 0xff000000) >> 24);
	unsigned int  r1 = ((A & 0x00ff0000) >> 16);
	unsigned int  g1 = ((A & 0x0000ff00) >> 8);
	unsigned int  b1 = (A & 0x000000ff);

	unsigned int  a2 = ((B & 0xff000000) >> 24);
	unsigned int  r2 = ((B & 0x00ff0000) >> 16);
	unsigned int  g2 = ((B & 0x0000ff00) >> 8);
	unsigned int  b2 = (B & 0x000000ff);

	unsigned int  a3 = ((C & 0xff000000) >> 24);
	unsigned int  r3 = ((C & 0x00ff0000) >> 16);
	unsigned int  g3 = ((C & 0x0000ff00) >> 8);
	unsigned int  b3 = (C & 0x000000ff);

	unsigned int val0 = (unsigned int) (a1 * alpha + a2 * beta + a3 * gamma);
	unsigned int val1 = (unsigned int) (r1 * alpha + r2 * beta + r3 * gamma);
	unsigned int val2 = (unsigned int) (g1 * alpha + g2 * beta + g3 * gamma);
	unsigned int val3 = (unsigned int) (b1 * alpha + b2 * beta + b3 * gamma);

	auto a = (val0 << 24 | val1 << 16 | val2 << 8 | val3);

	return (val0 << 24 | val1 << 16 | val2 << 8 | val3);
}

unsigned int colorMath_CombineColors(unsigned int c1, unsigned int c2) {
	unsigned int  a1 = ((c1 & 0xff000000) >> 24);
	unsigned int  r1 = ((c1 & 0x00ff0000) >> 16);
	unsigned int  g1 = ((c1 & 0x0000ff00) >> 8);
	unsigned int  b1 = (c1 & 0x000000ff);

	unsigned int  a2 = ((c2 & 0xff000000) >> 24);
	unsigned int  r2 = ((c2 & 0x00ff0000) >> 16);
	unsigned int  g2 = ((c2 & 0x0000ff00) >> 8);
	unsigned int  b2 = (c2 & 0x000000ff);

	unsigned int val0 = colorMath_SaturateInt((a1 + a2), 255);
	unsigned int val1 = colorMath_SaturateInt((r1 + r2), 255);
	unsigned int val2 = colorMath_SaturateInt((g1 + g2), 255);
	unsigned int val3 = colorMath_SaturateInt((b1 + b2), 255);

	return (val0 << 24 | val1 << 16 | val2 << 8 | val3);
}
 
unsigned int colorMath_ModulateColors(unsigned int lightColor, unsigned int surfaceColor) {

	float a1 = ((lightColor & 0xff000000) >> 24) / 255.0f;
	float r1 = ((lightColor & 0x00ff0000) >> 16) / 255.0f;
	float g1 = ((lightColor & 0x0000ff00) >> 8) / 255.0f;
	float b1 = (lightColor & 0x000000ff) / 255.0f;

	float a2 = ((surfaceColor & 0xff000000) >> 24) / 255.0f;
	float r2 = ((surfaceColor & 0x00ff0000) >> 16) / 255.0f;
	float g2 = ((surfaceColor & 0x0000ff00) >> 8) / 255.0f;
	float b2 = (surfaceColor & 0x000000ff) / 255.0f;

	unsigned int val0 = colorMath_SaturateFloat((a1 * a2), 1) * 255.0f;
	unsigned int val1 = colorMath_SaturateFloat((r1 * r2), 1) * 255.0f;
	unsigned int val2 = colorMath_SaturateFloat((g1 * g2), 1) * 255.0f;
	unsigned int val3 = colorMath_SaturateFloat((b1 * b2), 1) * 255.0f;

	return (val0 << 24 | val1 << 16 | val2 << 8 | val3);
}

unsigned int colorMath_Interpolate(unsigned int c1, unsigned int c2, float ratio) {
	//lerp formula : (B - A) * R + A
	unsigned int a1 = ((c1 & 0xff000000) >> 24);
	unsigned int r1 = ((c1 & 0x00ff0000) >> 16);
	unsigned int g1 = ((c1 & 0x0000ff00) >> 8);
	unsigned int b1 = c1 & 0x000000ff;

	unsigned int a2 = ((c2 & 0xff000000) >> 24);
	unsigned int r2 = ((c2 & 0x00ff0000) >> 16);
	unsigned int g2 = ((c2 & 0x0000ff00) >> 8);
	unsigned int b2 = c2 & 0x000000ff;

	unsigned int val0 = ((a2 - a1) * ratio + a1);
	unsigned int val1 = ((r2 - r1) * ratio + r1);
	unsigned int val2 = ((g2 - g1) * ratio + g1);
	unsigned int val3 = ((b2 - b1) * ratio + b1);

	return (val0 << 24 | val1 << 16 | val2 << 8 | val3);
}
#pragma endregion


#pragma region 3D MATRIX MATH
////Multiply 3D Vector by 3D Matrix
//VEC_3D matMath_3D_MultiplyVector(MATRIX_3X3 matrix, VEC_3D vector) {
//	VEC_3D vOut;
//	vOut.x = (matrix.mat[0][0] * vector.x) + (matrix.mat[1][0] * vector.y) + (matrix.mat[2][0] * vector.z);
//	vOut.y = (matrix.mat[0][1] * vector.x) + (matrix.mat[1][1] * vector.y) + (matrix.mat[2][1] * vector.z);
//	vOut.z = (matrix.mat[0][2] * vector.x) + (matrix.mat[1][2] * vector.y) + (matrix.mat[2][2] * vector.z);
//	return vOut;
//}
//
//// Multiply 3D Matrix by 3D Matrix
//MATRIX_3X3 matMath_3D_MultiplyMatrix(MATRIX_3X3 mLeft, MATRIX_3X3 mRight) {
//	MATRIX_3X3 mOut;
//	for (int rLeft = 0; rLeft < 3; rLeft++) {
//		for (int cRight = 0; cRight < 3; cRight++) {
//			mOut.mat[rLeft][cRight] = 0;
//			for (int i = 0; i < 3; i++) {
//				mOut.mat[rLeft][cRight] += mLeft.mat[rLeft][i] * mRight.mat[i][cRight];
//			}
//		}
//	}
//	return mOut;
//}
//
////3D Scale Matrix
//MATRIX_3X3 matMath_3D_Scale(float scale) {
//	return { scale, 0,     0,
//			 0,     scale, 0, 
//			 0,     0,     scale};
//}
//
////3D Identity Matrix
//MATRIX_3X3 matMath_3D_Identity() {
//	return matMath_3D_Scale(1);
//}
//
////3D Flip Y
//MATRIX_3X3 matMath_3D_FlipY() {
//	return { 1,  0,  0,
//			 0, -1,  0,
//			 0,  0,  1};
//}
//
////3D Rotation Matrix for Z
//MATRIX_3X3 matMath_3D_RotateZ(float theta) {
//	theta = deg2Rad(theta);
//
//	return { std::cos(theta),  std::sin(theta), 0,
//			 -std::sin(theta), std::cos(theta), 0,
//			 0,				   0,				1};
//}
//
////3D Rotation Matrix for Y
//MATRIX_3X3 matMath_3D_RotateY(float theta) {
//	theta = deg2Rad(theta);
//
//	return { std::cos(theta),  0,		-std::sin(theta),
//			 0,				   1,		0,
//			 std::sin(theta),  0,		std::cos(theta) };
//}
//
////3D Rotation Matrix for X
//MATRIX_3X3 matMath_3D_RotateX(float theta) {
//	theta = deg2Rad(theta);
//
//	return { 1,  0,				   0,
//			 0,  std::cos(theta),  std::sin(theta),
//			 0, -std::sin(theta),  std::cos(theta) };
//}
//
//MATRIX_3X3 matMath_3D_Translation(float x, float y) {
//	return { 1,  0,  x,
//			 0,  1,  y,
//			 0,  0,  1 };
//}
#pragma endregion

#pragma region 4D MATRIX MATH
VEC_4D matMath_4D_MultiplyVector(MATRIX_4X4 matrix, VEC_4D vector) {
	VEC_4D vOut;
	vOut.x = (matrix.mat[0][0] * vector.x) + (matrix.mat[1][0] * vector.y) + (matrix.mat[2][0] * vector.z) + (matrix.mat[3][0] * vector.w);
	vOut.y = (matrix.mat[0][1] * vector.x) + (matrix.mat[1][1] * vector.y) + (matrix.mat[2][1] * vector.z) + (matrix.mat[3][1] * vector.w);
	vOut.z = (matrix.mat[0][2] * vector.x) + (matrix.mat[1][2] * vector.y) + (matrix.mat[2][2] * vector.z) + (matrix.mat[3][2] * vector.w);
	vOut.w = (matrix.mat[0][3] * vector.x) + (matrix.mat[1][3] * vector.y) + (matrix.mat[2][3] * vector.z) + (matrix.mat[3][3] * vector.w);
	return vOut;
}


MATRIX_4X4 matMath_4D_MultiplyMatrix(MATRIX_4X4 mLeft, MATRIX_4X4 mRight) {
	MATRIX_4X4 mOut;
	for (int rLeft = 0; rLeft < 4; rLeft++) {
		for (int cRight = 0; cRight < 4; cRight++) {
			mOut.mat[rLeft][cRight] = 0;
			for (int i = 0; i < 4; i++) {
				mOut.mat[rLeft][cRight] += mLeft.mat[rLeft][i] * mRight.mat[i][cRight];
			}
		}
	}
	return mOut;
}

//4D Scale Matrix
MATRIX_4X4 matMath_4D_Scale(float scale) {
	return { scale, 0,     0,	  0,
			 0,     scale, 0,	  0,
			 0,     0,     scale, 0,
			 0,     0,	   0,	  1 };
}

//4D Identity Matrix
MATRIX_4X4 matMath_4D_Identity() {
	return matMath_4D_Scale(1);
}

//4D Rotation Matrix for Z
MATRIX_4X4 matMath_4D_RotateZ(float theta) {
	theta = deg2Rad(theta);
	return { std::cos(theta),  -std::sin(theta), 0,	0,
			 std::sin(theta),	std::cos(theta), 0,	0,
			 0,				    0,				 1,	0,
			 0,					0,				 0, 1 };
}

//4D Rotation Matrix for Y
MATRIX_4X4 matMath_4D_RotateY(float theta) {
	theta = deg2Rad(theta);
	return { std::cos(theta),   0,		-std::sin(theta),	0,
			 0,					1,		0,					0,
			 std::sin(theta),   0,		std::cos(theta),	0,
			0,					0,		0,					1 };
}

//4D Rotation Matrix for X
MATRIX_4X4 matMath_4D_RotateX(float theta) {
	theta = deg2Rad(theta);
	return { 1,  0,				   0,					0,
			 0,  std::cos(theta),  std::sin(theta),		0,
			 0, -std::sin(theta),  std::cos(theta),		0,
			 0, 0,				   0,					1 };
}

//4D Translation Matrix
MATRIX_4X4 matMath_4D_Translation(float x, float y, float z) {
	return { 1,  0,  0, 0,
			 0,  1,  0, 0,
			 0,  0,  1, 0,
			 x,  y,  z, 1 };
}

MATRIX_4X4 matMath_4D_ProjectionMatrix(float zNear, float zFar, float Fov, float AspectRatio) {
	float yScale = 1.0f / std::tanf(deg2Rad(0.5 * Fov));
	float xScale = yScale * AspectRatio;

	return { xScale, 0,		 0,								   0,
			 0,		 yScale, 0,								   0,
			 0,		 0,		 zFar / (zFar - zNear),				   1,
			 0,		 0,		 -(zFar * zNear) / (zFar - zNear), 0
	};
}

VEC_4D matMat_4D_PerspectiveDivide(VEC_4D vector) {
	VEC_4D vOut = vector;

	if (vOut.w != 0) {
		vOut.x /= vOut.w;
		vOut.y /= vOut.w;
		vOut.z /= vOut.w;
		vOut.w = vOut.w;

		return vOut;
	}
}

MATRIX_4X4 matMath_4D_FastInverse(MATRIX_4X4 matrix) {
	MATRIX_4X4 mOut;
	VEC_4D posVec = { matrix.mat[3][0], matrix.mat[3][1] , matrix.mat[3][2] , matrix.mat[3][3] };

	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			for (int i = 0; i < 3; i++) {
				mOut.mat[row][col] = matrix.mat[col][row];
			}
			if (col == 3) {
				mOut.mat[row][col] = matrix.mat[row][col];
			}
		}
	}

	VEC_4D lastRow = matMath_4D_MultiplyVector(mOut, posVec);

	mOut.mat[3][0] = -lastRow.x;
	mOut.mat[3][1] = -lastRow.y;
	mOut.mat[3][2] = -lastRow.z;

	return mOut;
}


#pragma endregion
