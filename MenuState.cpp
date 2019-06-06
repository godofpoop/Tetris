#include "MenuState.h"
#include "TetrisGame.h"


MenuState::MenuState()
{
}
void MenuState::init(Input& in)
{
	input = &in;
	renderSystem.init();
	currentState = NONE;
	//return key
	returnTex = new Texture("res/return.png");
	returninTex = new Texture("res/return0.png");
	btnReturn.position = vector2(200, 450);
	btnReturn.texture = returnTex;
	btnReturn.scale = vector2(72, 15);
	btnReturn.depth = 1;
	renderSystem.addGui(btnReturn);
	//options key
	optionsTex = new Texture("res/sound.png");
	optionsinTex = new Texture("res/soundinv.png");
	optionsOff = new Texture("res/soundoff.png");
	btnOptions.position = vector2(200, 400);
	btnOptions.texture = optionsTex;
	btnOptions.scale = vector2(80, 15);
	btnOptions.depth = 1;

	soundb.texture = optionsinTex;
	soundb.position = vector2(200, 400);
	soundb.scale = vector2(80, 15);
	soundb.depth = .5;

	renderSystem.addGui(soundb);
	renderSystem.addGui(btnOptions);
	//exit key
	exitTex = new Texture("res/exit.png");
	exitinTex = new Texture("res/exit_inv.png");
	btnExit.position = vector2(200, 350);
	btnExit.texture = optionsTex;
	btnExit.scale = vector2(38, 15);
	btnExit.depth = 1;

	renderSystem.addGui(btnExit);
}
void MenuState::render()
{
	renderSystem.update();
}
void MenuState::update()
{
	if (input->isKeyPressed(keys::KEY_ESCAPE)) {
		currentState = NONE;
	}
	if (input->isKeyPressed(keys::KEY_ENTER)) {
		if (currentState == RETURN) currentState = NONE;
		if (currentState == EXIT) exit(0);
		if (currentState == OPTIONS) {
			TetrisGame::soundopt = !TetrisGame::soundopt;
			TetrisGame::sound();
			if (TetrisGame::soundopt) btnOptions.texture = optionsTex;
			else btnOptions.texture = optionsOff;
		}
	}
	if (input->isKeyPressed(keys::KEY_DOWN)) {
		if (currentState == EXIT) {
			currentState = RETURN;
		}
		else {
			currentState = (selected)(currentState + 1);
		}
		
	}
	if (input->isKeyPressed(keys::KEY_UP)) {
		if (currentState == RETURN) {
			currentState = EXIT;
		}
		else {
			currentState = (selected)(currentState - 1);
		}
		
	}
	switch (currentState) {
	case(NONE):
		break;
	case(RETURN):
		btnReturn.texture = returninTex;
		soundb.texture = btnOptions.texture;
		btnExit.texture = exitTex;
		break;
	case(OPTIONS):
		btnReturn.texture = returnTex;
		soundb.texture = optionsinTex;
		btnExit.texture = exitTex;
		break;
	case(EXIT):
		btnReturn.texture = returnTex;
		soundb.texture = btnOptions.texture;
		btnExit.texture = exitinTex;
		break;
	}
	
}
void MenuState::push()
{
	currentState = RETURN;
}
bool MenuState::isActive()
{
	return currentState != NONE;
}
MenuState::~MenuState()
{
}
