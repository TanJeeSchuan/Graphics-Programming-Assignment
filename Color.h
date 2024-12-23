#pragma once
class Color
{
public:
	float r, b, g;

	Color(){
		r = 0;
		g = 0;
		b = 0;
	}
	Color(float r, float g, float b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}
};

