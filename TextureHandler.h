#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <map>
#include <string>
#include "Texture.h"
#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

class TextureHandler
{
public:
	std::map<std::string, Texture> textures;

	BITMAP BMP;
	HBITMAP hBMP;

	GLuint loadTexture(LPCSTR textureName, LPCSTR filename)
	{
		GLuint texture = 0;		// texture name

		// initialize texture info
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		GetObject(hBMP, sizeof(BMP), &BMP);

		//// assign texture
		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);


		//textures.insert({textureName, Texture(texture, textureName, BMP, hBMP)});

		DeleteObject(hBMP);

		return texture;
	}
};

