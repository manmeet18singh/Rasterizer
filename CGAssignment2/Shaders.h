#pragma once
#include "CGMath.h"
#include "Defines.h"
//Provided by prof L.Norri's CG Shaders & Triangles powerpoint lecture

void (*VertexShader)(VEC_4D&) = 0;
void (*PixelShader)(unsigned int&) = 0;

MATRIX_4X4 SV_CameraMatrix;
MATRIX_4X4 SV_ViewMatrix;

MATRIX_4X4 SV_RotationMatrix;
MATRIX_4X4 SV_ProjectionMatrix;

MATRIX_4X4 SV_WorldMatrix;


void PS_White(unsigned int& makeWhite) {
	makeWhite = 0xFFFFFF;
}

void PS_Green(unsigned int& makeGreen) {
	makeGreen = 0x00FF00;
}

void VS_ApplyMatrices(VEC_4D& point) {
	point = matMath_4D_MultiplyVector(SV_WorldMatrix, point);
	point = matMath_4D_MultiplyVector(SV_ViewMatrix, point);
	point = matMath_4D_MultiplyVector(SV_ProjectionMatrix, point);
	point = matMat_4D_PerspectiveDivide(point);
}