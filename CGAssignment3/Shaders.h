#pragma once
#include "CGMath.h"
#include "Defines.h"
#include "greendragon.h"

//Provided by prof L.Norri's CG Shaders & Triangles powerpoint lecture

void (*VertexShader)(VEC_4D&) = 0;
void (*PixelShader)(unsigned int&) = 0;
void (*TexturePixelShader)(float&, float&, unsigned int&) = 0;

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

#define C2C(c) (((c&65280u)<<0x8u)|((c&4278190080u)>>0x18u)|((c&255u)<<0x18u)|((c&16711680u)>>0x08u));

void PS_Texture(float& u, float& v, unsigned int& makeTexture) {
	unsigned int texelX = u * greendragon_width;
	unsigned int texelY = v * greendragon_height;

	makeTexture = C2C(greendragon_pixels[texelY * greendragon_width + texelX]);
}

//VertexW = VertexL times World 
//VertexV = VertexW times View
//VertexP = VertexV times Projection.

void VS_ApplyMatrices(VEC_4D& point) {
	point = matMath_4D_MultiplyVector(SV_WorldMatrix, point);
	point = matMath_4D_MultiplyVector(SV_ViewMatrix, point);
	point = matMath_4D_MultiplyVector(SV_ProjectionMatrix, point);
	point = matMat_4D_PerspectiveDivide(point);
}