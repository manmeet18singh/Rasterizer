#pragma once
#include "CGMath.h"
#include "Defines.h"
#include "StoneHenge_Texture.h"

//Provided by prof L.Norri's CG Shaders & Triangles powerpoint lecture

void (*VertexShader)(VERTEX&) = 0;
void (*PixelShader)(VERTEX&) = 0;

MATRIX_4X4 SV_CameraMatrix;
MATRIX_4X4 SV_ViewMatrix;
MATRIX_4X4 SV_ProjectionMatrix;
MATRIX_4X4 SV_WorldMatrix;

LIGHTS SV_DirectionalLight;
LIGHTS SV_PointLight;

float SV_AmbientLight;
float SV_PLRadius;

void PS_White(VERTEX& vertex) {
	vertex.clr = 0xFFFFFFFF;
}

void PS_Green(VERTEX& vertex) { 
	auto t = vertex.clr;
	t = 0x0000FF00;
	vertex.clr = 0x0000FF00;
}

#define C2C(c) (((c&65280u)<<0x8u)|((c&4278190080u)>>0x18u)|((c&255u)<<0x18u)|((c&16711680u)>>0x08u));

void PS_Texture(VERTEX& vertex) {
	unsigned int texelX = vertex.uv.x * StoneHenge_width;
	unsigned int texelY = vertex.uv.y * StoneHenge_height;

	unsigned int surfaceColor = C2C(StoneHenge_pixels[texelY * StoneHenge_width + texelX]);
	//vertex.clr = C2C(StoneHenge_pixels[texelY * StoneHenge_width + texelX]);

	vertex.clr = colorMath_ModulateColors(vertex.clr, surfaceColor);

//#pragma region Point Light
//		LIGHTDIR = NORMALIZE(LIGHTPOS – SURFACEPOS)
//		LIGHTRATIO = CLAMP(DOT(LIGHTDIR, SURFACENORMAL))
//		RESULT = LIGHTRATIO * LIGHTCOLOR * SURFACECOLOR
//
//#pragma endregion


	//makeTexture;
}

//VertexW = VertexL times World 
//VertexV = VertexW times View
//VertexP = VertexV times Projection.
void VS_ApplyMatrices(VERTEX& vertex) {
	//vertex.vert = matMath_4D_MultiplyVector(SV_WorldMatrix, vertex.vert);
	vertex.vert = matMath_4D_MultiplyVector(SV_ViewMatrix, vertex.vert);
	vertex.vert = matMath_4D_MultiplyVector(SV_ProjectionMatrix, vertex.vert);
	vertex.vert = matMat_4D_PerspectiveDivide(vertex.vert);
}

void VS_Lighting(VERTEX& vertex) {
	vertex.vert = matMath_4D_MultiplyVector(SV_WorldMatrix, vertex.vert);
	vertex.nrm = matMath_4D_MultiplyVector(SV_WorldMatrix, vertex.nrm);

	float dirLightRatio = colorMath_SaturateFloat(vecMath_4D_DotProduct(vecMath_4D_MultNumber(SV_DirectionalLight.pos, -1.0f), vertex.nrm) + SV_AmbientLight, 1);
	unsigned int dirColor = colorMath_Interpolate(0xFF000000, SV_DirectionalLight.color, dirLightRatio);

	VEC_4D pointLightDir = vecMath_4D_Normalize(vecMath_4D_SubVector(SV_PointLight.pos, vertex.vert));
	float ptLightRatio = colorMath_SaturateFloat(vecMath_4D_DotProduct(pointLightDir, vertex.nrm), 1);
	float attenuation = 1.0f - colorMath_SaturateFloat(vecMath_4D_Length(pointLightDir) / SV_PLRadius, 1);
	ptLightRatio *= attenuation;
	unsigned int ptColor = colorMath_Interpolate(0xFF000000, SV_PointLight.color, ptLightRatio);

	vertex.clr = colorMath_CombineColors(dirColor, ptColor);

	VS_ApplyMatrices(vertex);
}