#pragma once
#include "GL/glew.h"
#include "maths.h"
#include <vector>
#include "Shader.h"
#include "Texture.h"
#include "GuiSystem.h"

class Shape;
class Entity {
public:
	Entity(vector2 pos, vector4 col) { position = pos; color = col; }
	Entity() { position = vector2(); color = vector4(1, 0, 0, 1); }
	vector2 position;
	vector4 color;
	vector2 velocity;
	~Entity() {}
private:
};
class RenderSystem
{
public:	
	RenderSystem();
	void init();
	void update();
	void addEntity(Entity *e);
	void addEntity(Shape *e);
	void remove(Shape& e);
	void remove(Entity* e);
	void addGui(Gui& g);
	void addNumber(const vector2& p,int& i);
	~RenderSystem();
private:
	GLuint vao;
	float vertices[12] = {-1,1,1,1,-1,-1,
						1,1,1,-1,-1,-1};
	std::vector<Entity*> entities;
	std::vector<Gui*> guis;
	std::vector<int*> numbers;
	std::vector<vector2> pos;
	Shader shader;
	Shader guiShader;
	Shader numberShader;
	Texture *texture;
	Texture* numberTexture;
	void drawGui();
	void drawNumber();
	int number = 0;
};

