#pragma once
#include <vector>
#include "Defines.h"

class Cube {
public:
	Cube(float size) {
		const float cornerPoint = size / 2.0f;
		VEC_4D zero = { -cornerPoint, -cornerPoint, -cornerPoint, 1 };
		VEC_4D one = { cornerPoint, -cornerPoint, -cornerPoint, 1 };
		VEC_4D two = { -cornerPoint, cornerPoint, -cornerPoint, 1 };
		VEC_4D three = { cornerPoint, cornerPoint, -cornerPoint, 1 };
		VEC_4D four = { -cornerPoint, -cornerPoint, cornerPoint, 1 };
		VEC_4D five = { cornerPoint, -cornerPoint, cornerPoint, 1 };
		VEC_4D six = { -cornerPoint, cornerPoint, cornerPoint, 1 };
		VEC_4D seven = { cornerPoint, cornerPoint, cornerPoint, 1 };

		corners.emplace_back(zero);
		corners.emplace_back(one); 
		corners.emplace_back(two); 
		corners.emplace_back(three);  
		corners.emplace_back(four);  
		corners.emplace_back(five);   
		corners.emplace_back(six);   
		corners.emplace_back(seven);    
	}

	LINE_VERTEX_PAIR getLines() const {
		return { 
			corners,{
				 0,1,   1,3,   3,2,   2,0,
				 0,4,   1,5,   3,7,   2,6,
				 4,5,   5,7,  7,6,    6,4 } 
		};
	}
private:
	std::vector<VEC_4D> corners;
};