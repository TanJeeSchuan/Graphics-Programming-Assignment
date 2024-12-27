#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <string>

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

class Texture
{
public:
	GLuint texId;
	std::string name;
	BITMAP BMPHeader;
	HBITMAP HBitMap;

	Texture() {};

	Texture(GLuint texId, LPCSTR name, BITMAP BMPHeader, HBITMAP HBitMap) {
		this->texId = texId;
		this->name = name;
		this->BMPHeader = BMPHeader;
		this->HBitMap = HBitMap;
	}
};

