#pragma once
#include "State.h"
#include "RenderSystem.h"
#include "Input.h"

enum selected {
	NONE,
	RETURN,
	OPTIONS,
	EXIT
};
class MenuState : public State
{
public:
	MenuState();
	void init(Input& input);
	void render();
	void update();
	bool isActive();
	void push();
	~MenuState();
private:
	RenderSystem renderSystem;
	Input *input;
	selected currentState;
	Gui btnReturn;
	Texture* returnTex;
	Texture* returninTex;

	Gui soundb;

	Gui btnOptions;
	Texture* optionsTex;
	Texture* optionsinTex;
	Texture* optionsOff;

	Gui btnExit;
	Texture* exitTex;
	Texture* exitinTex;
};

