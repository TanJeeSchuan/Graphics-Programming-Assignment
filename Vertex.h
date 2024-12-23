#pragma once
#include "Color.h"
#include "Material.h"

class Vertex
{
public:
	float x, y, z;
	Color* color;
	Material* material;

	Vertex(){}

	Vertex(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	//float* to_array() {
	//	return float[3] {x,y,z};
	//}
};

