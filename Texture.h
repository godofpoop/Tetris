#pragma once

#include <iostream>
#include <GL\glew.h>
class Texture
{
public:
	Texture();
	Texture(const char* path);
	Texture(int& w, int& h, int& comp, unsigned char* image);
	GLuint texture_id;
	GLuint speculatTexture;
	GLuint bloomMap;
	int reflectivity;
	int shineDamper;

	bool fakeLightning = false;

	~Texture();
};

