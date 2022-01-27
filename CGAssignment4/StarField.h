#pragma once
#include <vector>
#include "Defines.h"
#include <iostream>

class StarField {
public:
	StarField(float size) {
		
		for (int i = 0; i < size; i++)
		{
			float x = -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - (-1.0f))));
			float y = -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - (-1.0f))));
			float z = -1.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.0f - (-1.0f))));

			VEC_4D rand = {x * 50,y * 50,z * 50,1.0f};
			pos.emplace_back(rand);
		}
	}

	std::vector<VEC_4D> getPos() const {
		return pos;
	}

private:
	std::vector<VEC_4D> pos;
};