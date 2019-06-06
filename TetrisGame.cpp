#include "TetrisGame.h"
#include <random>
#include "Input.h"
#include "HighScoreIO.h"
#include "MenuState.h"
#include "Randomizer.h"

Shape shape;
Gui background;
Gui scoreGui;
Gui levelGui;
Sound *background_music = nullptr;
int TetrisGame::score = 0;
int TetrisGame::level = 1;
bool TetrisGame::soundopt = true;
vector<int> TetrisGame::scores;
MenuState menuState;

TetrisGame::TetrisGame()
{
}
void TetrisGame::init()
{
	background.position = vector2(200, 300);
	background.scale = vector2(200,300);
	background.texture = new Texture("res/background1.png");

	scoreGui.position = vector2(50, 520);
	scoreGui.scale = vector2(364/10, 73/10);
	scoreGui.texture = new Texture("res/score.png");

	levelGui.position = vector2(50, 400);
	levelGui.scale = vector2(613 / 20, 173 / 20);
	levelGui.texture = new Texture("res/level.png");

	std::srand(std::time(0));
	std::cout << "You are playing tetris.\n";
	renderer.init();
	menuState.init(input);
	//shape = Shape(shapes::IShape,vector4(1,0,0,1));
	gen = true;
	//renderer.addEntity(shape);
	renderer.addNumber(vector2(70,500),score);

	renderer.addGui(scoreGui);
	HighScoreIO::write(0,scores);
	for (int i = 0; i < scores.size(); i++) {
		renderer.addNumber(vector2(370, 300 - i * 20), scores[i]);
	}
	renderer.addNumber(vector2(65, 375), level);
	renderer.addGui(levelGui);
	renderer.addGui(background);
	//system.addEntity(shape);
	//active_shape = &shape;
	block = Randomizer::next();
	soundSystem.init();
	system.init(soundSystem,renderer);
	background_music = new Sound("sounds/tetris.wav",true);
	background_music->play();
	soundSystem.addSound(*background_music);
}
void TetrisGame::sound()
{
	if (soundopt) background_music->play();
	else background_music->stop();
}
void TetrisGame::update()
{
	if (menuState.isActive()) {
		menuState.update();
		return;
	}
	update_input();
	system.update(delta,active_shape);
	generate();	
}

void TetrisGame::render()
{
	if(menuState.isActive()) menuState.render();
	renderer.update();
}
void TetrisGame::generate()
{	
	if (system.refresh) {
		
		if (gen) {
			Shape* s = new Shape((shapes)block);
			if (shadow != nullptr) {
				renderer.remove(*shadow);
				delete shadow;
				shadow = nullptr;
			}
			shadow = new Shape((shapes)block);
			for (Entity* e : shadow->entities) {
				e->color.w = .2;
				e->color.x *= 1.3;
				e->color.y *= 1.3;
				e->color.z *= 1.3;
			}
			block = Randomizer::next();
			r = (rand() % 10)/10.0;
			g = (rand() % 10)/10.0;
			b = (rand() % 10)/10.0;
			draw_next((shapes)block);

			
			renderer.addEntity(s);
			renderer.addEntity(shadow);
			system.addEntity(s);
			active_shape = s;
			gen = false;

		}
		if (active_shape->touch) {
			gen = true;
		}
	}
	while (system.translate(shadow, vector2(0, -20)));
	system.speed = (TetrisGame::level*3)-2;
}
void TetrisGame::update_input()
{
	if (input.isKeyPressed(keys::KEY_RIGHT)) {
		system.translate(active_shape, vector2(20, 0));
		for (int i = 0; i < shadow->entities.size(); i++) {
			if (shadow->entities.size() == active_shape->entities.size()) {
				shadow->entities[i]->position = active_shape->entities[i]->position;
			}
		}
	}
	if (input.isKeyPressed(keys::KEY_LEFT)) {
		system.translate(active_shape, vector2(-20, 0));
		for (int i = 0; i < shadow->entities.size(); i++) {
			if (shadow->entities.size() == active_shape->entities.size()) {
				shadow->entities[i]->position = active_shape->entities[i]->position;
			}
		}
	}
	if (input.isKeyPressed(keys::KEY_UP)) {
		system.rotate(active_shape);
		for (int i = 0; i < shadow->entities.size(); i++) {
			if (shadow->entities.size() == active_shape->entities.size()) {
				shadow->entities[i]->position = active_shape->entities[i]->position;
			}
		}
	}
	if (input.isKeyDown(keys::KEY_DOWN)) {
		system.speed = 10;
	}
	if (input.isKeyPressed(keys::KEY_ESCAPE)) {
		menuState.push();
	}
}
void TetrisGame::draw_next(shapes block)
{
	if (next != nullptr) {
		renderer.remove(*next);

		delete next;
		next = nullptr;
	}
		
	next = new Shape((shapes)block, vector2(350,400));

	renderer.addEntity(next);
}
TetrisGame::~TetrisGame()
{
	delete active_shape;
	delete next;
	delete shadow;
}
