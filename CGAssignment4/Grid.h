#pragma once
#include <vector>
#include "Defines.h"

class Grid {
public:
	Grid(float size) {
		const float cornerPoint = size / 2.22f;

		VEC_4D vertex1;
		VEC_4D vertex2;

		float row = 0;
		while (row < 1) {
			vertex1 = { -cornerPoint, cornerPoint, -cornerPoint + row, 1 };
			vertex2 = { cornerPoint, cornerPoint, -cornerPoint + row, 1 };
			corners.emplace_back(vertex1);
			corners.emplace_back(vertex2);
			row += .1;
		}

		float col = 0;
		while (col < 1) {
			vertex1 = { -cornerPoint + col, cornerPoint, -cornerPoint, 1 };
			vertex2 = { -cornerPoint + col, cornerPoint, cornerPoint, 1 };
			corners.emplace_back(vertex1);
			corners.emplace_back(vertex2);
			col += .1;
		}
	}

	LINE_VERTEX_PAIR getLines() const {
		return {
			corners,{
				 0,1,   2,3,   4,5,   6,7,   8,9,
				 10,11, 12,13, 14,15, 16,17, 18,19,
				 20,21, 22,23, 24,25, 26,27, 28,29,
				 30,31, 32,33, 34,35, 36,37, 38,39}
		};
	}
private:
	std::vector<VEC_4D> corners;
};