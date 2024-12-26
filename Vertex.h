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

	float* vertexData() {
		float arr[3] = { x,y,z };
		return arr;
	}

	float* normalData() {
		float arr[3] = { normX,normY,normZ };
		return arr;
	}

	Vertex operator+(Vertex const& vert) {
		Vertex result;
		result.x = x + vert.x;
		result.y = y + vert.y;
		result.z = z + vert.z;
		return result;
	}

	Vertex operator-(Vertex const& vert) {
		Vertex result;
		result.x = x - vert.x;
		result.y = y - vert.y;
		result.z = z - vert.z;
		return result;
	}

	Vertex operator-() {
		Vertex result;
		result.x = -x;
		result.y = -y;
		result.z = -z;
		return result;
	}
};

