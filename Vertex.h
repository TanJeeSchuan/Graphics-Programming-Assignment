#pragma once
#include "Color.h"
#include "Material.h"

class Vertex
{
public:
	float x, y, z;
	float normX = 0, normY = 0, normZ = 0;
	Color* color;
	Material* material;

	Vertex(){}

	Vertex(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

