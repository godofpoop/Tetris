#pragma once
#include "RenderSystem.h"
enum shapes {

	TShape,
	LShape,
	ZShape,
	IShape,
	JShape,
	OShape,
	SShape
};
class Shape
{
public:
	Shape();
	Shape(shapes s);
	Shape(shapes s,vector2 pos);
	std::vector<Entity *> entities;
	vector2 position;
	void translate(vector2 v);
	bool move;
	int rotation;
	void rotate();
	vector2 velocity;
	bool touch;
	~Shape();
};

