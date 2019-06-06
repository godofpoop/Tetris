#pragma once
#include "Game.h"
#include "MovementSystem.h"
#include "Shape.h"
#include "SoundSystem.h"
#include "MenuState.h"

class TetrisGame : public Game
{
public:
	TetrisGame();
	void update();
	void init();
	void render();
	static void sound();
	static int score;
	static int level;
	static vector<int> scores;
	static bool soundopt;
	~TetrisGame();
private:
	RenderSystem renderer;
	MovementSystem system;
	SoundSystem soundSystem;
	Shape* active_shape;
	Shape* next;
	Shape* shadow;
	bool gen;
	void generate();
	void update_input();
	void draw_next(shapes s);
	int block;
	double r;
	double g;
	double b;
};

