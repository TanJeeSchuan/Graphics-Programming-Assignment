#pragma once
//#include <gl/GL.h>
#include <vector>
#include <map>
#include <string>

/* LightParameter */
#define GL_AMBIENT                        0x1200
#define GL_DIFFUSE                        0x1201
#define GL_SPECULAR                       0x1202
#define GL_POSITION                       0x1203
#define GL_SPOT_DIRECTION                 0x1204
#define GL_SPOT_EXPONENT                  0x1205
#define GL_SPOT_CUTOFF                    0x1206
#define GL_CONSTANT_ATTENUATION           0x1207
#define GL_LINEAR_ATTENUATION             0x1208
#define GL_QUADRATIC_ATTENUATION          0x1209

#define GL_EMISSION                       0x1600
#define GL_SHININESS                      0x1601
#define GL_AMBIENT_AND_DIFFUSE            0x1602
#define GL_COLOR_INDEXES                  0x1603

class Material
{
public:
	std::string name;
	std::map<int, std::vector<float>> properties;

	Material()
	{
		properties.insert({ GL_AMBIENT	, {0.0f, 0.0f, 0.0f, 1.0f} });
		properties.insert({ GL_DIFFUSE	, {0.0f, 0.0f, 0.0f, 1.0f} });
		properties.insert({ GL_SPECULAR , {0.0f, 0.0f, 0.0f, 1.0f} });
		properties.insert({ GL_EMISSION , {0.0f, 0.0f, 0.0f, 1.0f} });
		properties.insert({ GL_SHININESS, {50.0f	 } });
	}

	void setAmbientColour(float r, float g, float b)
	{
		int key = GL_AMBIENT;
		properties[key][0] = r;
		properties[key][1] = g;
		properties[key][2] = b;
	}

	void setDiffuseColour(float r, float g, float b)
	{
		int key = GL_DIFFUSE;
		properties[key][0] = r;
		properties[key][1] = g;
		properties[key][2] = b;
	}

	void setSpecularColour(float r, float g, float b)
	{
		int key = GL_SPECULAR;
		properties[key][0] = r;
		properties[key][1] = g;
		properties[key][2] = b;
	}

	void setEmissionColour(float r, float g, float b) {
		int key = GL_EMISSION;
		properties[key][0] = r;
		properties[key][1] = g;
		properties[key][2] = b;
	}

	void setShininess(float exp)
	{
		int key = GL_SHININESS;
		properties[key][0] = exp;
	}
};

