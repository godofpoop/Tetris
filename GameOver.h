#pragma once
#include "State.h"
#include "RenderSystem.h"
#include "Input.h"
class GameOver : public State
{
public:
	GameOver();
	void init(Input& input);
	void render();
	void update();
	~GameOver();
private:
	RenderSystem renderSystem;
	Input* input;
};

