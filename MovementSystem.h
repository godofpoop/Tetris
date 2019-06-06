#pragma once
#include "Shape.h"
#include "SoundSystem.h"

class MovementSystem
{
public:
	MovementSystem();
	void init(SoundSystem& s,RenderSystem& renderSystem);
	void addEntity(Shape* e);
	void update(double delta,Shape* active);
	bool refresh;
	float speed;
	bool translate(Shape* s, vector2 v);
	void rotate(Shape* s);
	void remove();
	~MovementSystem();
private:
	bool translate(Shape* s, vector2 v, vector<Shape*> others);
	std::vector<Shape*> shapes;
	double time;
	vector<Entity*> markedtodie;
	void fall();
	void animation();
	bool contains(Shape* s, vector<Shape*> shapes);
	bool contains(Entity* s, vector<Entity*> shapes);
	void flood(Entity* e,vector<Entity*> &temp);
	Sound* fallSound;
	Sound* clearSound;
	Sound* rotateSound;
	RenderSystem *renderer;
	int animation_cycle;
};

