#include "Shape.h"



Shape::Shape()
{
	touch = false;
}
Shape::Shape(shapes s)
{
	touch = false;
	move = false;
	rotation = 0;
	position = vector2(190, 490);
	if (s == JShape) {
		vector4 color = vector4(0, 0, 1, 1);
		entities.push_back(new Entity(vector2(-20.0,0.0),color));
		entities.push_back(new Entity(vector2(0.0,0.0),color));
		entities.push_back(new Entity(vector2(20.0,0.0),color));
		entities.push_back(new Entity(vector2(-20.0,20.0),color));
	}
	if (s == IShape) {
		vector4 color = vector4(0, 1, 1, 1);
		entities.push_back(new Entity(vector2(-20.0, 0.0), color));
		entities.push_back(new Entity(vector2(0.0, 0.0), color));
		entities.push_back(new Entity(vector2(20.0, 0.0), color));
		entities.push_back(new Entity(vector2(40.0, 0.0), color));
	}
	if (s == OShape) {
		vector4 color = vector4(1, 1, 0, 1);
		entities.push_back(new Entity(vector2(0.0, 0.0), color));
		entities.push_back(new Entity(vector2(20.0, 0.0), color));
		entities.push_back(new Entity(vector2(0.0, 20.0), color));
		entities.push_back(new Entity(vector2(20.0, 20.0), color));
	}
	if (s == LShape) {
		vector4 color = vector4(1, .5, 0, 1);
		entities.push_back(new Entity(vector2(-20.0, 0.0), color));
		entities.push_back(new Entity(vector2(0.0, 0.0), color));
		entities.push_back(new Entity(vector2(20.0, 0.0), color));
		entities.push_back(new Entity(vector2(20.0, 20.0), color));
	}
	if (s == TShape) {
		vector4 color = vector4(1, 0, 1, 1);
		entities.push_back(new Entity(vector2(-20.0, 0.0), color));
		entities.push_back(new Entity(vector2(0.0, 0.0), color));
		entities.push_back(new Entity(vector2(20.0, 0.0), color));
		entities.push_back(new Entity(vector2(0.0, 20.0), color));
	}
	if (s == SShape) {
		vector4 color = vector4(0, 1, 0, 1);
		entities.push_back(new Entity(vector2(-20.0, 0.0), color));
		entities.push_back(new Entity(vector2(0.0, 0.0), color));
		entities.push_back(new Entity(vector2(0.0, 20.0), color));
		entities.push_back(new Entity(vector2(20.0, 20.0), color));
	}
	if (s == ZShape) {
		vector4 color = vector4(1, 0, 0, 1);
		entities.push_back(new Entity(vector2(0.0, 0.0), color));
		entities.push_back(new Entity(vector2(20.0, 0.0), color));
		entities.push_back(new Entity(vector2(-20.0, 20.0), color));
		entities.push_back(new Entity(vector2(0.0, 20.0), color));
	}
	for (int i = 0; i < 4; i++) {
		entities[i]->position.x += 190;
		entities[i]->position.y += 490;
	}
}
void Shape::translate(vector2 v)
{
	velocity.x = v.x;
	velocity.y = v.y;
}
Shape::Shape(shapes s, vector2 pos)
{
	touch = false;
	move = false;
	rotation = 0;
	position = vector2(200, 500);
	if (s == JShape) {
		vector4 color = vector4(0, 0, 1, 1);
		entities.push_back(new Entity(vector2(-20.0, 0.0), color));
		entities.push_back(new Entity(vector2(0.0, 0.0), color));
		entities.push_back(new Entity(vector2(20.0, 0.0), color));
		entities.push_back(new Entity(vector2(-20.0, 20.0), color));
	}
	if (s == IShape) {
		vector4 color = vector4(0, 1, 1, 1);
		entities.push_back(new Entity(vector2(-20.0, 0.0), color));
		entities.push_back(new Entity(vector2(0.0, 0.0), color));
		entities.push_back(new Entity(vector2(20.0, 0.0), color));
		entities.push_back(new Entity(vector2(40.0, 0.0), color));
	}
	if (s == OShape) {
		vector4 color = vector4(1, 1, 0, 1);
		entities.push_back(new Entity(vector2(0.0, 0.0), color));
		entities.push_back(new Entity(vector2(20.0, 0.0), color));
		entities.push_back(new Entity(vector2(0.0, 20.0), color));
		entities.push_back(new Entity(vector2(20.0, 20.0), color));
	}
	if (s == LShape) {
		vector4 color = vector4(1, .5, 0, 1);
		entities.push_back(new Entity(vector2(-20.0, 0.0), color));
		entities.push_back(new Entity(vector2(0.0, 0.0), color));
		entities.push_back(new Entity(vector2(20.0, 0.0), color));
		entities.push_back(new Entity(vector2(20.0, 20.0), color));
	}
	if (s == TShape) {
		vector4 color = vector4(1, 0, 1, 1);
		entities.push_back(new Entity(vector2(-20.0, 0.0), color));
		entities.push_back(new Entity(vector2(0.0, 0.0), color));
		entities.push_back(new Entity(vector2(20.0, 0.0), color));
		entities.push_back(new Entity(vector2(0.0, 20.0), color));
	}
	if (s == SShape) {
		vector4 color = vector4(0, 1, 0, 1);
		entities.push_back(new Entity(vector2(-20.0, 0.0), color));
		entities.push_back(new Entity(vector2(0.0, 0.0), color));
		entities.push_back(new Entity(vector2(0.0, 20.0), color));
		entities.push_back(new Entity(vector2(20.0, 20.0), color));
	}
	if (s == ZShape) {
		vector4 color = vector4(1, 0, 0, 1);
		entities.push_back(new Entity(vector2(0.0, 0.0), color));
		entities.push_back(new Entity(vector2(20.0, 0.0), color));
		entities.push_back(new Entity(vector2(-20.0, 20.0), color));
		entities.push_back(new Entity(vector2(0.0, 20.0), color));
	}
	for (int i = 0; i < 4; i++) {
		entities[i]->position.x += pos.x;
		entities[i]->position.y += pos.y;
	}
}
void Shape::rotate()
{
	for (int i = 0; i < 4; i++) {
		float tmp = entities[i]->position.y - position.y;
		entities[i]->position.y = entities[i]->position.x - position.x;
		entities[i]->position.x = tmp;
		entities[i]->position.x += position.x;
		entities[i]->position.y += position.y;
	}
}
Shape::~Shape()
{
	for (int i = 0; i < entities.size(); i++) {
		if (entities[i] == nullptr) continue;
		delete entities[i];
		entities[i] = nullptr;
	}
}
