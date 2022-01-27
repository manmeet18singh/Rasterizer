#pragma once
#include <vector>
#include "Defines.h"

class Cube {
public:
	Cube(float size) {
		const float cornerPoint = size / 2.0f;
		VEC_4D v0 = { -cornerPoint, -cornerPoint, cornerPoint, 1 };
		VEC_4D v1 = { cornerPoint, -cornerPoint, cornerPoint, 1 };
		VEC_4D v2 = { -cornerPoint, cornerPoint, cornerPoint, 1 };
		VEC_4D v3 = { cornerPoint, cornerPoint, cornerPoint, 1 };
		VEC_4D v4 = v2;
		VEC_4D v5 = v3;
		VEC_4D v6 = { -cornerPoint, cornerPoint, -cornerPoint, 1 };
		VEC_4D v7 = { cornerPoint, cornerPoint, -cornerPoint, 1 };
		VEC_4D v8 = { cornerPoint, -cornerPoint, -cornerPoint, 1 };
		VEC_4D v9 = { -cornerPoint, -cornerPoint, -cornerPoint, 1 };
		VEC_4D v10 = v7;
		VEC_4D v11 = v6;
		VEC_4D v12 = v1;
		VEC_4D v13 = v0;
		VEC_4D v14 = v8;
		VEC_4D v15 = v9;
		VEC_4D v16 = v9;
		VEC_4D v17 = v0;
		VEC_4D v18 = v6;
		VEC_4D v19 = v2;
		VEC_4D v20 = v1;
		VEC_4D v21 = v8;
		VEC_4D v22 = v3;
		VEC_4D v23 = v7;

		corners.emplace_back(v0);
		corners.emplace_back(v1);
		corners.emplace_back(v2);
		corners.emplace_back(v3);
		corners.emplace_back(v4);
		corners.emplace_back(v5);
		corners.emplace_back(v6);
		corners.emplace_back(v7);
		corners.emplace_back(v8);
		corners.emplace_back(v9);
		corners.emplace_back(v10);
		corners.emplace_back(v11);
		corners.emplace_back(v12);
		corners.emplace_back(v13);
		corners.emplace_back(v14);
		corners.emplace_back(v15);
		corners.emplace_back(v16);
		corners.emplace_back(v17);
		corners.emplace_back(v18);
		corners.emplace_back(v19);
		corners.emplace_back(v20);
		corners.emplace_back(v21);
		corners.emplace_back(v22);
		corners.emplace_back(v23);

		VEC_2D tex0 = { 1.0f, 0.0f };
		VEC_2D tex1 = { 0.0f, 0.0f };
		VEC_2D tex2 = { 1.0f, 1.0f };
		VEC_2D tex3 = { 0.0f, 1.0f };

		VEC_2D tex4 = { 1.0f, 0.0f };
		VEC_2D tex5 = { 0.0f, 0.0f };
		VEC_2D tex6 = { 1.0f, 1.0f };
		VEC_2D tex7 = { 0.0f, 1.0f };

		VEC_2D tex8 = { 1.0f, 0.0f };
		VEC_2D tex9 = { 0.0f, 0.0f };
		VEC_2D tex10 = { 1.0f, 1.0f };
		VEC_2D tex11 = { 0.0f, 1.0f };

		VEC_2D tex12 = { 1.0f, 0.0f };
		VEC_2D tex13 = { 0.0f, 0.0f };
		VEC_2D tex14 = { 1.0f, 1.0f };
		VEC_2D tex15 = { 0.0f, 1.0f };

		VEC_2D tex16 = { 1.0f, 0.0f };
		VEC_2D tex17 = { 0.0f, 0.0f };
		VEC_2D tex18 = { 1.0f, 1.0f };
		VEC_2D tex19 = { 0.0f, 1.0f };

		VEC_2D tex20 = { 1.0f, 0.0f };
		VEC_2D tex21 = { 0.0f, 0.0f };
		VEC_2D tex22 = { 1.0f, 1.0f };
		VEC_2D tex23 = { 0.0f, 1.0f };

		texels.emplace_back(tex0);
		texels.emplace_back(tex1);
		texels.emplace_back(tex2);
		texels.emplace_back(tex3);
		texels.emplace_back(tex4);
		texels.emplace_back(tex5);
		texels.emplace_back(tex6);
		texels.emplace_back(tex7);
		texels.emplace_back(tex8);
		texels.emplace_back(tex9);
		texels.emplace_back(tex10);
		texels.emplace_back(tex11);
		texels.emplace_back(tex12);
		texels.emplace_back(tex13);
		texels.emplace_back(tex14);
		texels.emplace_back(tex15);
		texels.emplace_back(tex16);
		texels.emplace_back(tex17);
		texels.emplace_back(tex18);
		texels.emplace_back(tex19);
		texels.emplace_back(tex20);
		texels.emplace_back(tex21);
		texels.emplace_back(tex22);
		texels.emplace_back(tex23);

	}

	LINE_VERTEX_PAIR getLines() const {
		return {
			corners,{
				 0,1,   1,3,   3,2,   2,0,
				 0,4,   1,5,   3,7,   2,6,
				 4,5,   5,7,  7,6,    6,4 }
		};
	}

	LINE_VERTEX_PAIR getTriangles() const {
		return {
			corners, {
				0,1,2,  2,1,3, //FRONT FACE
				4,5,6,  6,5,7,//BACK FACE
				4,5,0,  0,5,1, //TOP FACE
				6,7,2,  2,7,3,//BOTTOM FACE
				1,5,3,  3,5,7, //RIGHT FACE
				0,4,2,  2,4,6}//LEFT FACE
		};
	}

	TEXTURED_LINE_PAIR getTexTri() const {
		return {
			UV_VERTEX_PAIR { texels, corners }, 
			{
				 0, 2, 1,  1, 2, 3, //FRONT FACE
				12,14,13, 13,14,15, //BOTTOM FACE
				 4, 6, 5,  5, 6, 7, //TOP FACE
				 8,10, 9,  9,10,11, //BACK FACE
				16,18,17, 17,18,19, //LEFT FACE
				20,22,21, 21,22,23 } //RIGHT FACE
		};
	}
private:
	std::vector<VEC_4D> corners;
	std::vector<VEC_2D> texels;
};